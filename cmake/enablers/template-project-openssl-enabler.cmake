cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_OPENSSL
    "Enables the OpenSSL library (TLS/SSL connections, cryptographic primitives: SHA, AES, HMAC, RSA, EVP API) through a system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_OPENSSL)
    return()
endif()

# NOTE: OpenSSL uses a Perl-based Configure build system, so the FetchContent
# fallback below cannot actually compile it; a system-installed package is the
# supported path. The git source is kept for parity with the other enablers.
set(TEMPLATE_APP_OPENSSL_GIT "https://github.com/openssl/openssl.git" CACHE STRING "The OpenSSL library git source repository")
set(TEMPLATE_APP_OPENSSL_GIT_TAG "master" CACHE STRING "The OpenSSL project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME OpenSSL
  GIT_REPOSITORY ${TEMPLATE_APP_OPENSSL_GIT}
  GIT_TAG ${TEMPLATE_APP_OPENSSL_GIT_TAG}
  COMPONENTS SSL Crypto
)

# Link OpenSSL::SSL for TLS/SSL/DTLS connections and OpenSSL::Crypto for
# standalone cryptographic primitives (SHA, AES, RSA, HMAC, EVP API, etc.).
# See doc/sections/en_US/5-35-enabling-the-openssl-library.md (and the uk_UA
# copy) for copy-paste C++ usage examples: SHA-256, HMAC-SHA256, and a
# minimal HTTPS/TLS client.
target_link_libraries(
  ${PROJECT_BINARY_NAME}
  OpenSSL::SSL
  OpenSSL::Crypto
)
