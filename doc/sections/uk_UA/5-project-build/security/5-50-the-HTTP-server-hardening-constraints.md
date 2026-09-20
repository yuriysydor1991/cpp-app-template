## Обмеження захисту (hardening) HTTP-сервера

Сервер Boost.Beast шаблону самостійно відмовляє завеликому, заповільному та занадто численному запиту, отож вмикати для цього нічого не потрібно. Кожне обмеження є змінною кешу CMake модуля [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake), яку шаблон [src/project-global-decls.h.in](/src/project-global-decls.h.in) перетворює на сталу часу компіляції простору імен `project_decls`:

| Змінна CMake | Типове значення | Що обмежує |
| --- | --- | --- |
| `PROJECT_HTTP_MAX_REQUEST_BODY_BYTES` | `8388608` (8 МіБ) | розмір тіла, яке може нести один запит |
| `PROJECT_HTTP_MAX_REQUEST_HEADER_BYTES` | `8192` (8 КіБ) | розмір усіх заголовків запиту, разом із рядком запиту |
| `PROJECT_HTTP_REQUEST_TIMEOUT_SECONDS` | `30` | час, який може тривати читання цілого запиту |
| `PROJECT_HTTP_RESPONSE_TIMEOUT_SECONDS` | `30` | час, який може тривати запис цілої відповіді |
| `PROJECT_HTTP_MAX_CONNECTIONS` | `128` | кількість одночасно обслуговуваних з'єднань |
| `PROJECT_HTTP_LISTEN_BACKLOG` | `128` | кількість встановлених з'єднань, що очікують на прийняття |

Побудова, яка стискає кожне з них, виглядає так:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
  -DPROJECT_HTTP_MAX_REQUEST_BODY_BYTES=5242880 \
  -DPROJECT_HTTP_MAX_REQUEST_HEADER_BYTES=4096 \
  -DPROJECT_HTTP_REQUEST_TIMEOUT_SECONDS=10 \
  -DPROJECT_HTTP_RESPONSE_TIMEOUT_SECONDS=10 \
  -DPROJECT_HTTP_MAX_CONNECTIONS=64 \
  -DPROJECT_HTTP_LISTEN_BACKLOG=64
```

### Обмеження розміру запиту

[RequestReader](/src/beasthttp/rhandlers/RequestReader.cpp) читає через [http::request_parser](https://www.boost.org/doc/libs/latest/libs/beast/doc/html/beast/ref/boost__beast__http__request_parser.html), чиї `header_limit` та `body_limit` беруться з контексту сеансу. Запит, який переростає будь-яке з них, відхиляється розбирачем на тому самому байті, що перетинає межу - нічого більшого ніколи не буферизується - а з'єднання закривається без відповіді:

```
ERR RequestReader.cpp:71 : Fail to read the request: body limit exceeded
ERR RequestReader.cpp:71 : Fail to read the request: header limit exceeded
```

Типові значення Boost.Beast становлять 1 МіБ для тіла та 8 КіБ для заголовків, отож саме значення тіла шаблон піднімає: застосунок, який не приймає жодного вивантаження, може знизити його до кількох кілобайтів.

### Час очікування

Читання та запис виконуються асинхронними викликами через [beast::tcp_stream](https://www.boost.org/doc/libs/latest/libs/beast/doc/html/beast/ref/boost__beast__basic_stream.html), якому заздалегідь встановлено `expires_after`, бо блокувальні виклики Boost.Asio не зважають на жоден час очікування і залишили б потік у нескінченному очікуванні. Кожен сеанс керує власним `io_context`, отож таймер одного сеансу обслуговується потоком саме цього сеансу і жодним іншим.

Тому клієнт, який надсилає свій запит побайтово або не завершує його ніколи, утримує потік лише протягом часу очікування запиту:

```
ERR RequestReader.cpp:71 : Fail to read the request: The socket was closed due to a timeout
```

Час очікування відповіді покриває протилежний випадок клієнта, який просить відповідь і припиняє її читати.

### Обмеження з'єднань

Прийняте з'єднання понад `PROJECT_HTTP_MAX_CONNECTIONS` закривається одразу, отож натовп клієнтів не нарощує ані кількості потоків, ані пам'яті сервера без межі:

```
WRN HttpController.cpp:56 : Dropping the accepted connection: already serving the allowed 128 ones
```

Значення `PROJECT_HTTP_LISTEN_BACKLOG` передається викликові `listen` приймача і обмежує чергу, яку ОС наповнює з'єднаннями, що вже встановлені, але ще не прийняті.

### Поля заголовків відповіді

[ResponseBuilder](/src/beasthttp/rhandlers/ResponseBuilder.cpp) встановлює поля заголовків, які не залишають браузерові жодної власної свободи щодо відповіданої сторінки:

| Поле | Значення | Що виконує |
| --- | --- | --- |
| `X-Content-Type-Options` | `nosniff` | оголошений тип вмісту є тим, що використовується, без вгадування за вмістом |
| `X-Frame-Options` | `DENY` | сторінка не вбудовується у жоден кадр іншої, отож її ніхто не перехоплює клацанням (clickjacking) |
| `Referrer-Policy` | `no-referrer` | перехід за посиланням не несе адреси сторінки, з якої його зроблено |
| `Content-Security-Policy` | `default-src 'none'; frame-ancestors 'none'; base-uri 'none'; form-action 'none'` | сторінка не завантажує нічого, що саме й робить типова сторінка шаблону |

Політику останнього видає метод `get_content_security_policy`, який слід перевизначити, щойно сторінка почне завантажувати власний сценарій, стиль чи зображення. Поле `Strict-Transport-Security` навмисно не встановлює жоден із них: шаблон обслуговує звичайний HTTP, а поле враховується лише через з'єднання TLS.

### Налаштування окремого сеансу

Кожне обмеження окремого сеансу є полем примірника [HTTPSessionContext](/src/beasthttp/rhandlers/HTTPSessionContext.h), який створює метод `HttpController::create_http_session_context`, отож перевизначення цього методу є місцем для їх подальшого зниження:

```cpp
class LimitedController : public beasthttp::HttpController
{
 protected:
  virtual std::shared_ptr<rhandlers::HTTPSessionContext>
  create_http_session_context() override
  {
    auto sctx = HttpController::create_http_session_context();

    sctx->maxBodyBytes = 4096U;
    sctx->maxHeaderBytes = 1024U;
    sctx->requestTimeout = std::chrono::seconds{5};

    return sctx;
  }
};
```

Обмеження з'єднань належать усьому серверові, а не окремому сеансові, отож містяться у примірнику `HttpContext` і знижуються натомість у конструкторі його нащадка.

### Перевірка результату

Коли сервер запущено на своїй типовій адресі, `curl` показує, що роблять обмеження. Відповідь із наведеними вище полями заголовків:

```bash
curl -D - -o /dev/null http://127.0.0.1:8080/
```

Тіло запиту понад дозволений розмір, якому відмовлено взагалі без відповіді (повідомлення `curl: (52) Empty reply from server`):

```bash
head -c 9000000 /dev/zero | tr '\0' 'a' > /tmp/oversized.data
curl -H "Expect:" --data-binary @/tmp/oversized.data http://127.0.0.1:8080/
```

Заголовок понад дозволений розмір, якому відмовлено так само:

```bash
curl -H "X-Big: $(head -c 9000 /dev/zero | tr '\0' 'b')" http://127.0.0.1:8080/
```

Компонентний тест [CTEST_beasthttp](/src/beasthttp/tests/component/CTEST_beasthttp.cpp) перевіряє кожне з них із контролером, обмеження якого знижено до тестового розміру.
