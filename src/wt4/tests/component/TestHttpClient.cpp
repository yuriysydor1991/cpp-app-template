#include "TestHttpClient.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <string>

namespace
{

sockaddr_in loopback(const int port)
{
  sockaddr_in addr{};

  addr.sin_family = AF_INET;
  addr.sin_port = htons(static_cast<uint16_t>(port));
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  return addr;
}

}  // namespace

int TestHttpClient::free_port()
{
  const int sock = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in addr = loopback(0);
  socklen_t len = sizeof(addr);

  int port = 0;

  if (bind(sock, reinterpret_cast<sockaddr*>(&addr), len) == 0 &&
      getsockname(sock, reinterpret_cast<sockaddr*>(&addr), &len) == 0) {
    port = ntohs(addr.sin_port);
  }

  close(sock);

  return port;
}

std::string TestHttpClient::get(const int port, const std::string& path)
{
  const int sock = socket(AF_INET, SOCK_STREAM, 0);
  const sockaddr_in addr = loopback(port);

  std::string response;

  if (connect(sock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) ==
      0) {
    const std::string request =
        "GET " + path + " HTTP/1.0\r\nHost: 127.0.0.1\r\n\r\n";

    if (send(sock, request.data(), request.size(), 0) ==
        static_cast<ssize_t>(request.size())) {
      std::array<char, 4096> buf{};

      for (ssize_t got = 0; (got = recv(sock, buf.data(), buf.size(), 0)) > 0;) {
        response.append(buf.data(), static_cast<size_t>(got));
      }
    }
  }

  close(sock);

  return response;
}
