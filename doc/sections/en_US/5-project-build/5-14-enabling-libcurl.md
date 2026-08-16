## Enabling the libcurl

In order to enable [libcurl](https://uk.wikipedia.org/wiki/CURL) for the project by using the installed system one or by fetching it by the available connection set an `ON` value to the `ENABLE_LIBCURL` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_LIBCURL=ON
```

### The requests the CURLController performs

The `curli::CURLController` class of the `src/CURL` directory keeps a single libcurl easy handle and performs the requests with it:

| Call | Request |
| --- | --- |
| `download(url)` | the GET request downloading the body of the given URL |
| `download(url, headers)` | the same GET request with the additional headers, each one in the `Name: value` form (an authorization one, for example) |
| `post(url, body, headers)` | the POST request sending the given body with the additional headers |
| `is_url_alive(url)` | the HEAD request checking the reachability of the URL without downloading it's body |
| `last_response_successfull()` | tells whether the last performed request has been answered with a success status |
| `last_response_code()` | the HTTP status code of the last performed request |
| `get()` | the buffer holding the body received by the last request |

Every call drops the body received by the previous one and resets the handle options, so a download performed after a post inherits neither it's method, nor it's body and headers. The received body is given back as a `std::vector<char>` reference, which stays empty in case of any error.

Ask the `last_response_successfull` method about the outcome rather than comparing the `last_response_code` value with a status constant of your own, which keeps the HTTP statuses inside the controller. The codeless protocols are the reason: a file transfer reports a zero response code both when it succeeds and when it fails, so the code alone tells the two apart in no way, while a redirect answer counts as no success either. The `last_response_code` value is left for the messages and for the calling code that really needs a status of it's own:

```cpp
#include <string>

#include "src/CURL/CURLController.h"

auto curl = curli::CURLController::create();

if (!curl->is_url_alive("https://example.com/api/")) {
  return;
}

const auto& answer =
    curl->post("https://example.com/api/", R"({"ask":"something"})",
               {"content-type: application/json",
                "authorization: Bearer a-token-of-yours"});

if (!curl->last_response_successfull()) {
  // the request has failed or the server has reported an error status,
  // which the last_response_code method gives the exact value of
}

const std::string received{answer.begin(), answer.end()};
```

A redirect answer counts as alive and is not followed, while a server rejecting the HEAD method itself (with the `405` status, for example) is reported as not alive, so check such an URL with a download instead.

A download gives up after the `DEFAULT_TIMEOUT` seconds and aborts a stalled transfer even earlier (less than the `DEFAULT_LOWSPEEDLIMIT` bytes per second during the `DEFAULT_LOWSPEEDSECS` seconds). A post applies no low speed abort at all and waits for the `DEFAULT_POST_TIMEOUT` seconds instead, because a server composing an answer keeps the connection silent meanwhile. All of them are the class fields to change for the needs of your requests.

### Testing the controller

Two test binaries of the `src/CURL/tests` directory cover the class, both performing no network communication at all:

- `UTEST_CURLController` is the unit test of the calls that give up before any transfer starts, like the ones with an empty URL or with an unsupported protocol. Enable it with the [ENABLE_UNIT_TESTS](/doc/sections/en_US/5-project-build/testing/5-3-1-enabling-unit-testing.md) CMake variable.
- `CTEST_CURLController` is the component test driving the real libcurl over the file protocol against the files it writes into it's own build directory. Enable it with the `ENABLE_COMPONENT_TESTS` CMake variable.

The code using the controller is tested against it's gmock replacement of the `src/app/tests/mocks/CURLController` directory instead, which the `UTEST_Application` and the `CTEST_app` targets include ahead of the real header. Keep the mock in sync with the class when extending the one.
