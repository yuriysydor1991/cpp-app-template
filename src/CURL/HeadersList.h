#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HEADERSLIST_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HEADERSLIST_CLASS_H

#include <curl/curl.h>

#include <string>
#include <vector>

namespace curli
{

/**
 * @brief Keeps the libcurl headers list alive during the request and releases
 * it afterwards, so every request kind builds it's headers the same way.
 */
class HeadersList
{
 public:
  /**
   * @brief Builds the libcurl list of the given headers.
   *
   * @param headers The HTTP headers, each one in the "Name: value" form.
   */
  explicit HeadersList(const std::vector<std::string>& headers);
  ~HeadersList();
  HeadersList(const HeadersList&) = delete;
  HeadersList(HeadersList&&) = delete;

  /**
   * @brief Tells whether every given header has made it into the list.
   *
   * @return Returns false when the libcurl has failed to append any of them,
   * so no request goes out with a part of it's headers (an authorization one,
   * for example) silently missing.
   */
  bool complete() const;

  /**
   * @brief Gives the list to hand over to the CURLOPT_HTTPHEADER option.
   *
   * @return Returns the list or nullptr when no header has been given.
   */
  struct curl_slist* raw() const;

 private:
  struct curl_slist* list{nullptr};
  bool appended{true};
};

}  // namespace curli

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HEADERSLIST_CLASS_H
