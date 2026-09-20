## The HTTP server hardening constraints

The Boost.Beast server of the template refuses an oversized, a slow and a too numerous request on it's own, so nothing has to be enabled for that. Every constraint is a CMake cache variable of the [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake) module, which the [src/project-global-decls.h.in](/src/project-global-decls.h.in) template turns into a compile time constant of the `project_decls` namespace:

| CMake variable | Default | What it limits |
| --- | --- | --- |
| `PROJECT_HTTP_MAX_REQUEST_BODY_BYTES` | `8388608` (8 MiB) | the size of the request body a single request may carry |
| `PROJECT_HTTP_MAX_REQUEST_HEADER_BYTES` | `8192` (8 KiB) | the size of the whole request headers, the request line included |
| `PROJECT_HTTP_REQUEST_TIMEOUT_SECONDS` | `30` | the time the reading of a whole request may take |
| `PROJECT_HTTP_RESPONSE_TIMEOUT_SECONDS` | `30` | the time the writing of a whole response may take |
| `PROJECT_HTTP_MAX_CONNECTIONS` | `128` | the connections served at once |
| `PROJECT_HTTP_LISTEN_BACKLOG` | `128` | the established connections waiting to be accepted |

A build tightening every one of them looks like this:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
  -DPROJECT_HTTP_MAX_REQUEST_BODY_BYTES=5242880 \
  -DPROJECT_HTTP_MAX_REQUEST_HEADER_BYTES=4096 \
  -DPROJECT_HTTP_REQUEST_TIMEOUT_SECONDS=10 \
  -DPROJECT_HTTP_RESPONSE_TIMEOUT_SECONDS=10 \
  -DPROJECT_HTTP_MAX_CONNECTIONS=64 \
  -DPROJECT_HTTP_LISTEN_BACKLOG=64
```

### The request size constraints

The [RequestReader](/src/beasthttp/rhandlers/RequestReader.cpp) reads through a [http::request_parser](https://www.boost.org/doc/libs/latest/libs/beast/doc/html/beast/ref/boost__beast__http__request_parser.html) whose `header_limit` and `body_limit` are taken from the session context. A request outgrowing either one is refused by the parser at the very byte that crosses the limit - nothing bigger is ever buffered - and the connection is closed with no answer:

```
ERR RequestReader.cpp:71 : Fail to read the request: body limit exceeded
ERR RequestReader.cpp:71 : Fail to read the request: header limit exceeded
```

The Boost.Beast defaults are 1 MiB for the body and 8 KiB for the headers, so the body one of the template is the raised one: an application receiving no upload at all is free to lower it down to a few kilobytes.

### The timeouts

The reading and the writing are performed by the asynchronous calls over a [beast::tcp_stream](https://www.boost.org/doc/libs/latest/libs/beast/doc/html/beast/ref/boost__beast__basic_stream.html) whose `expires_after` is set beforehand, because the blocking calls of the Boost.Asio honor no timeout at all and would leave a thread waiting forever. Each session drives an `io_context` of it's own, so the timer of one session is served by the thread of that session and by no other one.

A client sending it's request byte by byte, or never finishing it, therefore pins a thread for the request timeout only:

```
ERR RequestReader.cpp:71 : Fail to read the request: The socket was closed due to a timeout
```

The response timeout covers the opposite case of a client that asks for an answer and stops reading it.

### The connection constraints

The accepted connection above the `PROJECT_HTTP_MAX_CONNECTIONS` one is closed right away, so a crowd of clients grows neither the thread count nor the memory of the server without a bound:

```
WRN HttpController.cpp:56 : Dropping the accepted connection: already serving the allowed 128 ones
```

The `PROJECT_HTTP_LISTEN_BACKLOG` one is handed over to the `listen` call of the acceptor and caps the queue the OS fills with the connections that are established but not accepted yet.

### The response header fields

The [ResponseBuilder](/src/beasthttp/rhandlers/ResponseBuilder.cpp) sets the header fields that leave the browser no liberty of it's own with the answered page:

| Field | Value | What it does |
| --- | --- | --- |
| `X-Content-Type-Options` | `nosniff` | the announced content type is the one used, with no guessing by the content |
| `X-Frame-Options` | `DENY` | the page is embedded into no frame of another one, so it is clickjacked by none |
| `Referrer-Policy` | `no-referrer` | a followed link carries no address of the page it has been followed from |
| `Content-Security-Policy` | `default-src 'none'; frame-ancestors 'none'; base-uri 'none'; form-action 'none'` | the page loads nothing at all, which is what the default page of the template does |

The policy of the last one is given by the `get_content_security_policy` method, which is to be overridden once the page starts to load a script, a style or an image of it's own. The `Strict-Transport-Security` field is set by none of them on purpose: the template serves the plain HTTP, and the field is honored over a TLS connection only.

### Tuning a single session

Every constraint of a single session is a field of the [HTTPSessionContext](/src/beasthttp/rhandlers/HTTPSessionContext.h) instance the `HttpController::create_http_session_context` method creates, so an override of that method is the place to lower them further:

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

The connection constraints belong to the whole server rather than to a single session, so they live in the `HttpContext` instance and are lowered in the constructor of it's descendant instead.

### Checking the result

With the server running on it's default address, the `curl` tells what the constraints do. An answer carrying the header fields above:

```bash
curl -D - -o /dev/null http://127.0.0.1:8080/
```

A request body over the allowed size, which is refused with no answer at all (the `curl: (52) Empty reply from server` message):

```bash
head -c 9000000 /dev/zero | tr '\0' 'a' > /tmp/oversized.data
curl -H "Expect:" --data-binary @/tmp/oversized.data http://127.0.0.1:8080/
```

A header over the allowed size, refused the same way:

```bash
curl -H "X-Big: $(head -c 9000 /dev/zero | tr '\0' 'b')" http://127.0.0.1:8080/
```

The [CTEST_beasthttp](/src/beasthttp/tests/component/CTEST_beasthttp.cpp) component test checks every one of them against a controller whose constraints are lowered to the test size.
