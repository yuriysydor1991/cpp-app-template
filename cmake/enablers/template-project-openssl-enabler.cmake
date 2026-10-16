cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_OPENSSL
    "Enables the OpenSSL library (TLS/SSL connections, cryptographic primitives: SHA, AES, HMAC, RSA, EVP API) through the system installed one"
    OFF
)

if (NOT ENABLE_OPENSSL)
    return()
endif()

# OpenSSL builds with its own Perl based Configure script, which the CMake
# FetchContent can not drive, so the system installed package is the only
# supported source of it.
find_package(OpenSSL COMPONENTS SSL Crypto)

if (NOT OPENSSL_FOUND)
  message(
    FATAL_ERROR
    "The ENABLE_OPENSSL=ON requires the system installed OpenSSL development "
    "package: libssl-dev on Debian/Ubuntu, openssl-devel on Fedora/RHEL, "
    "openssl on Homebrew (the FreeBSD base system ships it). Install it or set "
    "ENABLE_OPENSSL=OFF."
  )
endif()

message(STATUS "OpenSSL ${OPENSSL_VERSION} found")

# Link OpenSSL::SSL for TLS/SSL/DTLS connections and OpenSSL::Crypto for
# standalone cryptographic primitives (SHA, AES, RSA, HMAC, EVP API, etc.).
# See doc/sections/en_US/5-project-build/security/5-35-enabling-the-openssl-library.md
# (and the uk_UA copy) for copy-paste C++ usage examples: SHA-256, HMAC-SHA256,
# and a minimal HTTPS/TLS client. The library holds the project code, the
# executable only calls it.
target_link_libraries(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
)
