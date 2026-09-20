## The HTTP client hardening constraints

The [CURLController](/src/CURL/CURLController.cpp) of the template performs no request without the constraints that keep a hostile or a broken answer from exhausting the resources of the application, so nothing has to be enabled for that. Every constraint is a CMake cache variable of the [cmake/template-project-misc-variables-declare.cmake](/cmake/template-project-misc-variables-declare.cmake) module, which the [src/project-global-decls.h.in](/src/project-global-decls.h.in) template turns into a compile time constant of the `project_decls` namespace:

| CMake variable | Default | What it limits |
| --- | --- | --- |
| `PROJECT_CURL_MAX_RESPONSE_BYTES` | `8388608` (8 MiB) | the size of the response body a single request may receive |
| `PROJECT_CURL_CONNECT_TIMEOUT_SECONDS` | `10` | the time the establishing of the connection may take |
| `PROJECT_CURL_TRANSFER_TIMEOUT_SECONDS` | `30` | the time a whole download or reachability check may take |
| `PROJECT_CURL_POST_TIMEOUT_SECONDS` | `300` | the time a whole POST request may take |
| `PROJECT_CURL_ALLOWED_PROTOCOLS` | `http,https,file` | the protocols a request URL may use |

A build tightening every one of them looks like this:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
  -DPROJECT_CURL_MAX_RESPONSE_BYTES=1048576 \
  -DPROJECT_CURL_CONNECT_TIMEOUT_SECONDS=5 \
  -DPROJECT_CURL_TRANSFER_TIMEOUT_SECONDS=15 \
  -DPROJECT_CURL_POST_TIMEOUT_SECONDS=60 \
  -DPROJECT_CURL_ALLOWED_PROTOCOLS=https
```

### The response size constraint

An answer announcing a size above the allowed one is refused by the `CURLOPT_MAXFILESIZE_LARGE` option of the libcurl before a single byte of it is transferred. An answer announcing no size at all - a chunked one, for example - is cut by the write callback instead, which stops appending as soon as the buffer would outgrow the limit and thereby aborts the whole transfer:

```
ERR CURLController.cpp:112 : The response has outgrown the allowed 8388608 bytes
```

The received buffer is left empty in both cases and the `last_response_successfull` call reports a failure, so a partially received answer is never mistaken for a complete one.

### The timeouts

The connect timeout is applied to every request kind, while the transfer one separates the plain download and the reachability check from the POST request: a server composing an answer keeps the connection silent meanwhile, which a short timeout would take for a stall. The download additionally aborts a transfer that crawls below one byte per second for ten seconds (the `CURLOPT_LOW_SPEED_LIMIT` and the `CURLOPT_LOW_SPEED_TIME` options), which the POST one does not, for the very same reason.

The `CURLOPT_NOSIGNAL` option is on, so the timeouts raise no signal and the controller stays usable from a thread of it's own.

### The allowed protocols

The `CURLOPT_PROTOCOLS_STR` option limits the request to the protocols of the `PROJECT_CURL_ALLOWED_PROTOCOLS` list, so a crafted URL reaches no `scp`, no `smb` and no `dict` service of the local network. The `file` one is allowed by default because the template itself and it's component test download over it; an application taking it's URLs from an untrusted source is to narrow the list down to `https` alone, which leaves no local file readable through a request either.

The option arrived with the libcurl 7.85.0 release and is applied by the newer one only, so an older libcurl keeps the protocols of it's own build. A protocol name the libcurl does not know fails the request with the message naming the variable to correct:

```
ERR CURLController.cpp:194 : Fail to allow the htttp protocols only. Check the PROJECT_CURL_ALLOWED_PROTOCOLS value
```

### The TLS constraints

| libcurl option | Value | What it does |
| --- | --- | --- |
| `CURLOPT_SSL_VERIFYPEER` | `1` | the certificate of the server is verified against the certificate authorities of the system |
| `CURLOPT_SSL_VERIFYHOST` | `2` | the host name of the certificate is matched against the one of the URL |
| `CURLOPT_SSLVERSION` | `CURL_SSLVERSION_TLSv1_2` | the TLS 1.2 is the lowest accepted protocol version |

The first two are the defaults of the libcurl already and are set anyway, so that neither a build carrying another default nor a descendant lowers them unnoticed. The redirect following stays off, which it is by default too, so an authorization header of a request reaches the asked host and no other one.

### Checking the result

The values the build has taken are the ones of the generated `project-global-decls.h` header of the build directory:

```bash
grep PROJECT_CURL build/project-global-decls.h
```

The [CTEST_CURLController](/src/CURL/tests/component/CURLController/CTEST_CURLController.cpp) component test checks that a response above the allowed size is refused, and the [UTEST_CURLController](/src/CURL/tests/unit/CURLController/UTEST_CURLController.cpp) unit test checks that the buffer stops growing at the very limit.
