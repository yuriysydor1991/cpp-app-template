#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_BEAST_INCLUDES_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_BEAST_INCLUDES_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace beasthttp
{

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_BEAST_INCLUDES_H
