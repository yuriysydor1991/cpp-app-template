## Enabling the OpenSSL library

In order to enable [OpenSSL](https://www.openssl.org/) (TLS/SSL connections, cryptographic primitives: SHA, AES, HMAC, RSA, EVP API) for the project using the system-installed package, set an `ON` value to the `ENABLE_OPENSSL` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_OPENSSL=ON
```

OpenSSL uses the Perl-based `Configure` build system and is **not** compatible with CMake FetchContent, so a system package is required before configuring:

| Platform | Install command |
|---|---|
| Debian / Ubuntu | `sudo apt install libssl-dev` |
| Fedora / RHEL | `sudo dnf install openssl-devel` |
| Arch Linux | `sudo pacman -S openssl` |
| macOS (Homebrew) | `brew install openssl` |

See the `cmake/enablers/template-project-openssl-enabler.cmake` module for the CMake imported targets:
- `OpenSSL::SSL` — TLS/SSL/DTLS sockets and handshake support
- `OpenSSL::Crypto` — standalone cryptographic primitives (SHA, AES, RSA, HMAC, EVP API, etc.)

Both targets are linked to `${PROJECT_BINARY_NAME}` when `ENABLE_OPENSSL=ON`.

### Computing a SHA-256 hash (copy-paste example)

After `ENABLE_OPENSSL=ON`, include `<openssl/evp.h>` and use the EVP digest API (recommended over the deprecated `SHA256()` convenience function):

```cpp
#include <openssl/evp.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// Returns the raw 32-byte SHA-256 digest of the input buffer.
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

### Checksums in multiple digest algorithms (copy-paste example)

A checksum is just the digest rendered as printable lowercase hex (the same string the `sha256sum` CLI prints). The EVP API is algorithm-agnostic: pass a different `EVP_MD*` to switch algorithms — the output length adapts automatically. The helper below returns the hex checksum for any digest OpenSSL ships:

```cpp
#include <openssl/evp.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

// Returns the lowercase-hex checksum of `data` computed with the given digest
// algorithm, e.g. checksum_hex(EVP_sha256(), bytes).
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

Call it with whichever algorithm you need — for `{'a', 'b', 'c'}` the SHA-256 checksum is the well-known NIST test vector:

```cpp
const std::vector<uint8_t> data{'a', 'b', 'c'};

checksum_hex(EVP_sha256(), data);
// "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
checksum_hex(EVP_sha512(), data);
checksum_hex(EVP_sha3_256(), data);
```

OpenSSL exposes one `EVP_*()` accessor per algorithm; the common checksum digests are:

| Algorithm | Accessor | Digest size |
|---|---|---|
| SHA-1 | `EVP_sha1()` | 20 bytes / 40 hex chars |
| SHA-224 | `EVP_sha224()` | 28 bytes / 56 hex chars |
| SHA-256 | `EVP_sha256()` | 32 bytes / 64 hex chars |
| SHA-384 | `EVP_sha384()` | 48 bytes / 96 hex chars |
| SHA-512 | `EVP_sha512()` | 64 bytes / 128 hex chars |
| SHA3-256 | `EVP_sha3_256()` | 32 bytes / 64 hex chars |
| SHA3-512 | `EVP_sha3_512()` | 64 bytes / 128 hex chars |
| BLAKE2b-512 | `EVP_blake2b512()` | 64 bytes / 128 hex chars |
| MD5 (legacy — non-cryptographic) | `EVP_md5()` | 16 bytes / 32 hex chars |

To pick an algorithm by name at runtime, resolve it with `EVP_get_digestbyname("sha256")` (returns `nullptr` for an unknown name).

### HMAC-SHA256 authentication code (copy-paste example)

```cpp
#include <openssl/evp.h>
#include <openssl/hmac.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// Returns the 32-byte HMAC-SHA256 of `data` authenticated with `key`.
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

### Generating cryptographic random numbers (copy-paste example)

For keys, nonces, IVs, salts or tokens use OpenSSL's CSPRNG through `RAND_bytes` — never `std::rand` or `std::mt19937`, which are not cryptographically secure. In OpenSSL 1.1.1+ / 3.x the generator is seeded automatically from the OS entropy source and is thread-safe; `RAND_bytes` returns `1` on success and **must** be checked:

```cpp
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

// Returns `n` cryptographically secure random bytes from OpenSSL's CSPRNG.
std::vector<uint8_t> random_bytes(std::size_t n)
{
    std::vector<uint8_t> buf(n);
    if (RAND_bytes(buf.data(), static_cast<int>(n)) != 1)
        throw std::runtime_error("RAND_bytes failed (CSPRNG could not be seeded)");
    return buf;
}
```

For secret material that must never be exposed (private keys, long-term secrets) prefer `RAND_priv_bytes`, which draws from a separate private DRBG with the same signature: `RAND_priv_bytes(buf.data(), static_cast<int>(n))`.

To obtain a uniformly distributed integer in a range, draw raw bytes and reject the unfair tail — a plain `value % bound` would skew the result toward the low end (modulo bias):

```cpp
#include <openssl/rand.h>

#include <cstdint>
#include <stdexcept>

// Returns a uniformly distributed value in [0, bound) with no modulo bias.
uint64_t random_uint64_below(uint64_t bound)
{
    if (bound == 0)
        throw std::invalid_argument("bound must be non-zero");

    // Reject the smallest (2^64 % bound) draws so the kept range divides
    // evenly by `bound` — this removes the bias a plain `x % bound` adds.
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

### Minimal HTTPS / TLS client socket (copy-paste example)

The snippet below opens a TCP connection, performs a TLS handshake with full certificate verification against the system CA store, sends an HTTP/1.1 GET request, and returns the raw response.  Works on Linux and macOS (POSIX sockets).

```cpp
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

// host: e.g. "example.com"   port: e.g. "443"   path: e.g. "/index.html"
std::string https_get(const std::string& host,
                      const std::string& port,
                      const std::string& path)
{
    // 1. Resolve the hostname to an address list.
    addrinfo hints{};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo* res = nullptr;
    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0)
        throw std::runtime_error("getaddrinfo failed for " + host);

    // 2. Open a TCP socket and connect.
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

    // 3. Create a TLS context and enable peer certificate verification.
    SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        close(sock);
        throw std::runtime_error("SSL_CTX_new failed");
    }
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, nullptr);
    SSL_CTX_set_default_verify_paths(ctx);  // use system CA store

    // 4. Wrap the socket in a TLS connection and handshake.
    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    SSL_set_tlsext_host_name(ssl, host.c_str());  // SNI extension

    if (SSL_connect(ssl) != 1) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        close(sock);
        throw std::runtime_error("SSL_connect to " + host + " failed");
    }

    // 5. Send an HTTP/1.1 GET request over TLS.
    const std::string request =
        "GET " + path + " HTTP/1.1\r\n"
        "Host: " + host + "\r\n"
        "Connection: close\r\n\r\n";
    SSL_write(ssl, request.c_str(), static_cast<int>(request.size()));

    // 6. Read the full response.
    std::string response;
    char buf[4096];
    int n = 0;
    while ((n = SSL_read(ssl, buf, static_cast<int>(sizeof(buf)))) > 0)
        response.append(buf, static_cast<std::size_t>(n));

    // 7. Clean shutdown.
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sock);

    return response;
}
```

**Note on OpenSSL 1.1+ / 3.x**: explicit library initialization calls (`SSL_library_init()`, `OpenSSL_add_all_algorithms()`, `ERR_load_crypto_strings()`) are no longer required — initialization is automatic since OpenSSL 1.1.0.
