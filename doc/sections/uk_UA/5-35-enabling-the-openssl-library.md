## Вмикання інтеграції OpenSSL

Для того щоб увімкнути бібліотеку [OpenSSL](https://www.openssl.org/) (TLS/SSL з'єднання, криптографічні примітиви: SHA, AES, HMAC, RSA, EVP API) для проекту через системну встановлену версію пакету, необхідно встановити значення `ON` для CMake змінної `ENABLE_OPENSSL`:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_OPENSSL=ON
```

OpenSSL використовує Perl-скрипт `Configure` як систему збірки і **несумісний** з CMake FetchContent, тому системний пакет необхідно встановити до виклику cmake:

| Платформа | Команда встановлення |
|---|---|
| Debian / Ubuntu | `sudo apt install libssl-dev` |
| Fedora / RHEL | `sudo dnf install openssl-devel` |
| Arch Linux | `sudo pacman -S openssl` |
| macOS (Homebrew) | `brew install openssl` |

Дивись модуль `cmake/enablers/template-project-openssl-enabler.cmake` щодо CMake імпортованих цілей:
- `OpenSSL::SSL` — TLS/SSL/DTLS сокети та підтримка рукостискання
- `OpenSSL::Crypto` — автономні криптографічні примітиви (SHA, AES, RSA, HMAC, EVP API тощо)

Обидві цілі прилінковуються до `${PROJECT_BINARY_NAME}` при `ENABLE_OPENSSL=ON`.

### Обчислення хешу SHA-256 (приклад для копіювання)

Після `ENABLE_OPENSSL=ON` підключи `<openssl/evp.h>` і використовуй EVP digest API (рекомендовано замість застарілої функції `SHA256()`):

```cpp
#include <openssl/evp.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// Повертає сирі 32 байти SHA-256 дайджесту вхідного буфера.
std::vector<uint8_t> sha256(const std::vector<uint8_t>& data)
{
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx)
        throw std::runtime_error("EVP_MD_CTX_new failed");

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(ctx, data.data(), data.size()) != 1) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("EVP_DigestInit_ex / EVP_DigestUpdate failed");
    }

    std::vector<uint8_t> hash(static_cast<std::size_t>(EVP_MD_size(EVP_sha256())));
    unsigned int len = 0;
    if (EVP_DigestFinal_ex(ctx, hash.data(), &len) != 1) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("EVP_DigestFinal_ex failed");
    }
    EVP_MD_CTX_free(ctx);
    hash.resize(len);
    return hash;
}
```

### Контрольні суми у різних алгоритмах дайджесту (приклад для копіювання)

Контрольна сума — це той самий дайджест, відрендерений як друкований шістнадцятковий рядок у нижньому регістрі (той самий рядок, який виводить утиліта `sha256sum`). EVP API не залежить від алгоритму: щоб змінити алгоритм, передай інший `EVP_MD*` — довжина виводу підлаштовується автоматично. Наведена функція повертає шістнадцяткову контрольну суму для будь-якого дайджесту, який постачає OpenSSL:

```cpp
#include <openssl/evp.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

// Повертає шістнадцяткову (нижній регістр) контрольну суму `data`, обчислену
// заданим алгоритмом дайджесту, напр. checksum_hex(EVP_sha256(), bytes).
std::string checksum_hex(const EVP_MD* algo, const std::vector<uint8_t>& data)
{
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx)
        throw std::runtime_error("EVP_MD_CTX_new failed");

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int len = 0;

    if (EVP_DigestInit_ex(ctx, algo, nullptr) != 1 ||
        EVP_DigestUpdate(ctx, data.data(), data.size()) != 1 ||
        EVP_DigestFinal_ex(ctx, digest, &len) != 1) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("EVP digest computation failed");
    }
    EVP_MD_CTX_free(ctx);

    static const char hex[] = "0123456789abcdef";
    std::string out;
    out.reserve(static_cast<std::size_t>(len) * 2);
    for (unsigned int i = 0; i < len; ++i) {
        out.push_back(hex[digest[i] >> 4]);
        out.push_back(hex[digest[i] & 0x0F]);
    }
    return out;
}
```

Викликай її з потрібним алгоритмом — для `{'a', 'b', 'c'}` SHA-256 контрольна сума дорівнює відомому тестовому вектору NIST:

```cpp
const std::vector<uint8_t> data{'a', 'b', 'c'};

checksum_hex(EVP_sha256(), data);
// "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
checksum_hex(EVP_sha512(), data);
checksum_hex(EVP_sha3_256(), data);
```

OpenSSL надає по одному аксесору `EVP_*()` на кожен алгоритм; найпоширеніші дайджести для контрольних сум:

| Алгоритм | Аксесор | Розмір дайджесту |
|---|---|---|
| SHA-1 | `EVP_sha1()` | 20 байтів / 40 hex символів |
| SHA-224 | `EVP_sha224()` | 28 байтів / 56 hex символів |
| SHA-256 | `EVP_sha256()` | 32 байти / 64 hex символів |
| SHA-384 | `EVP_sha384()` | 48 байтів / 96 hex символів |
| SHA-512 | `EVP_sha512()` | 64 байти / 128 hex символів |
| SHA3-256 | `EVP_sha3_256()` | 32 байти / 64 hex символів |
| SHA3-512 | `EVP_sha3_512()` | 64 байти / 128 hex символів |
| BLAKE2b-512 | `EVP_blake2b512()` | 64 байти / 128 hex символів |
| MD5 (застарілий — некриптографічний) | `EVP_md5()` | 16 байтів / 32 hex символів |

Щоб обрати алгоритм за іменем під час виконання, отримай його через `EVP_get_digestbyname("sha256")` (повертає `nullptr` для невідомого імені).

### Код автентифікації HMAC-SHA256 (приклад для копіювання)

```cpp
#include <openssl/evp.h>
#include <openssl/hmac.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// Повертає 32-байтний HMAC-SHA256 для `data`, автентифікований ключем `key`.
std::vector<uint8_t> hmac_sha256(const std::vector<uint8_t>& key,
                                  const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> result(EVP_MAX_MD_SIZE);
    unsigned int len = 0;

    if (!HMAC(EVP_sha256(),
              key.data(),  static_cast<int>(key.size()),
              data.data(), data.size(),
              result.data(), &len))
        throw std::runtime_error("HMAC failed");

    result.resize(len);
    return result;
}
```

### Генерація криптографічних випадкових чисел (приклад для копіювання)

Для ключів, одноразових чисел (nonce), векторів ініціалізації (IV), солей чи токенів використовуй CSPRNG OpenSSL через `RAND_bytes` — ніколи не `std::rand` чи `std::mt19937`, які не є криптографічно стійкими. У OpenSSL 1.1.1+ / 3.x генератор автоматично засіюється з джерела ентропії ОС і є потокобезпечним; `RAND_bytes` повертає `1` в разі успіху, і це **обов'язково** треба перевіряти:

```cpp
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// Повертає `n` криптографічно стійких випадкових байтів із CSPRNG OpenSSL.
std::vector<uint8_t> random_bytes(std::size_t n)
{
    std::vector<uint8_t> buf(n);
    if (RAND_bytes(buf.data(), static_cast<int>(n)) != 1)
        throw std::runtime_error("RAND_bytes failed (CSPRNG could not be seeded)");
    return buf;
}
```

Для секретного матеріалу, який ніколи не повинен бути розкритий (приватні ключі, довготривалі секрети), надавай перевагу `RAND_priv_bytes` — він бере дані з окремого приватного DRBG і має таку саму сигнатуру: `RAND_priv_bytes(buf.data(), static_cast<int>(n))`.

Щоб отримати рівномірно розподілене ціле число в діапазоні, візьми сирі байти і відкинь несправедливий «хвіст» — простий `value % bound` зсував би результат у бік менших значень (зміщення за модулем):

```cpp
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>

// Повертає рівномірно розподілене значення в [0, bound) без зміщення за модулем.
uint64_t random_uint64_below(uint64_t bound)
{
    if (bound == 0)
        throw std::invalid_argument("bound must be non-zero");

    // Відкидаємо найменші (2^64 % bound) значення, щоб діапазон, що лишився,
    // ділився на `bound` націло — це усуває зміщення, яке додав би `x % bound`.
    const uint64_t reject = (0u - bound) % bound;  // == 2^64 % bound

    uint64_t value = 0;
    do {
        if (RAND_bytes(reinterpret_cast<unsigned char*>(&value),
                       static_cast<int>(sizeof(value))) != 1)
            throw std::runtime_error("RAND_bytes failed");
    } while (value < reject);

    return value % bound;
}
```

### Мінімальний HTTPS / TLS клієнтський сокет (приклад для копіювання)

Наведений сніпет відкриває TCP-з'єднання, виконує TLS рукостискання з повною верифікацією сертифіката серверу відносно системного CA-сховища, надсилає HTTP/1.1 GET запит і повертає сирий відповідь.  Працює на Linux та macOS (POSIX сокети).

```cpp
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

// host: напр. "example.com"   port: напр. "443"   path: напр. "/index.html"
std::string https_get(const std::string& host,
                      const std::string& port,
                      const std::string& path)
{
    // 1. Розв'язання імені хосту у список адрес.
    addrinfo hints{};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo* res = nullptr;
    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0)
        throw std::runtime_error("getaddrinfo failed for " + host);

    // 2. Відкриття TCP сокету та підключення.
    const int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        freeaddrinfo(res);
        throw std::runtime_error("socket() failed");
    }
    if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
        freeaddrinfo(res);
        close(sock);
        throw std::runtime_error("connect() to " + host + ":" + port + " failed");
    }
    freeaddrinfo(res);

    // 3. Створення TLS контексту і вмикання верифікації сертифіката серверу.
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        close(sock);
        throw std::runtime_error("SSL_CTX_new failed");
    }
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, nullptr);
    SSL_CTX_set_default_verify_paths(ctx);  // використовувати системне CA-сховище

    // 4. Загортання сокету у TLS з'єднання та рукостискання.
    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    SSL_set_tlsext_host_name(ssl, host.c_str());  // розширення SNI

    if (SSL_connect(ssl) != 1) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sock);
        throw std::runtime_error("SSL_connect to " + host + " failed");
    }

    // 5. Надсилання HTTP/1.1 GET запиту через TLS.
    const std::string request =
        "GET " + path + " HTTP/1.1\r\n"
        "Host: " + host + "\r\n"
        "Connection: close\r\n\r\n";
    SSL_write(ssl, request.c_str(), static_cast<int>(request.size()));

    // 6. Читання повної відповіді.
    std::string response;
    char buf[4096];
    int n = 0;
    while ((n = SSL_read(ssl, buf, static_cast<int>(sizeof(buf)))) > 0)
        response.append(buf, static_cast<std::size_t>(n));

    // 7. Коректне завершення з'єднання.
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sock);

    return response;
}
```

**Примітка щодо OpenSSL 1.1+ / 3.x**: явні виклики ініціалізації бібліотеки (`SSL_library_init()`, `OpenSSL_add_all_algorithms()`, `ERR_load_crypto_strings()`) більше не потрібні — ініціалізація виконується автоматично починаючи з OpenSSL 1.1.0.
