#include "src/CURL/CURLController.h"

#include <cassert>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "src/log/log.h"

namespace curli
{

namespace
{

size_t wcallback(void* contents, size_t size, size_t nmemb, void* userp)
{
  assert(contents != nullptr);
  assert(userp != nullptr);

  const auto givenSize = size * nmemb;

  if (givenSize == 0) {
    LOGD("No data fetch");
    return givenSize;
  }

  LOGT("Fetch " << givenSize << " bytes");

  CURLController* controller = static_cast<CURLController*>(userp);

  assert(controller != nullptr);

  if (controller == nullptr) {
    LOGE("Unknown dst type");
    return 0U;
  }

  char* rawb = static_cast<char*>(contents);

  auto& buff = controller->get();

  buff.reserve(buff.size() + givenSize);

  buff.insert(buff.end(), rawb, rawb + givenSize);

  return givenSize;
}

/**
 * @brief Keeps the libcurl headers list alive during the request and releases
 * it afterwards, so every request kind builds it's headers the same way.
 */
class HeadersList
{
 public:
  explicit HeadersList(const std::vector<std::string>& headers)
  {
    for (const auto& header : headers) {
      list = curl_slist_append(list, header.c_str());
    }
  }

  ~HeadersList() { curl_slist_free_all(list); }

  HeadersList(const HeadersList&) = delete;
  HeadersList(HeadersList&&) = delete;

  struct curl_slist* raw() const { return list; }

 private:
  struct curl_slist* list{nullptr};
};

}  // namespace

CURLController::~CURLController() { curl_easy_cleanup(curl); }

CURLController::CURLController()
{
  static const CURLcode initedCode = curl_global_init(CURL_GLOBAL_ALL);

  if (initedCode != CURLE_OK) {
    LOGE("Fail to init CURL globally, code: "
         << static_cast<unsigned int>(initedCode));
    return;
  }

  LOGT("curl globally inited");

  cbuff.reserve(DEFAULT_BUFF_RESERVE);

  curl = curl_easy_init();

  assert(curl != nullptr);

  if (curl == nullptr) {
    LOGE("Fail to allocate curl easy context instance");
    return;
  }
}

CURLController::download_buffer& CURLController::get() { return cbuff; }

long CURLController::last_response_code() const { return responseCode; }

bool CURLController::last_response_successfull() const
{
  if (!responseReceived) {
    return false;
  }

  // A protocol that carries no statuses (the file one, for example) reports a
  // zero code, so a received answer is the success proof by itself.
  return responseCode == 0L || (responseCode >= HTTP_FIRST_SUCCESS_STATUS &&
                                responseCode <= HTTP_LAST_SUCCESS_STATUS);
}

bool CURLController::prepare(const std::string& url)
{
  cbuff.clear();
  responseCode = 0L;
  responseReceived = false;

  assert(!url.empty());

  if (url.empty()) {
    LOGE("Invalid URL provided");
    return false;
  }

  if (curl == nullptr) {
    LOGE("Fail to create download context");
    return false;
  }

  // dropping the options of the previous request, so a plain download after
  // a post does not inherit it's method, body and headers.
  curl_easy_reset(curl);

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wcallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, DEFAULT_CONNECTTIMEOUT);

  return true;
}

CURLcode CURLController::perform()
{
  const CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    LOGE("CURL error: " << curl_easy_strerror(res));
    cbuff.clear();
    return res;
  }

  responseReceived = true;

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);

  LOGT("Fetched " << cbuff.size() << " bytes total with the " << responseCode
                  << " HTTP status");

  return res;
}

CURLController::download_buffer& CURLController::download(
    const std::string& url)
{
  return download(url, {});
}

CURLController::download_buffer& CURLController::download(
    const std::string& url, const std::vector<std::string>& headers)
{
  if (!prepare(url)) {
    return cbuff;
  }

  const HeadersList headerList{headers};

  curl_easy_setopt(curl, CURLOPT_TIMEOUT, DEFAULT_TIMEOUT);
  curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, DEFAULT_LOWSPEEDSECS);
  curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, DEFAULT_LOWSPEEDLIMIT);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList.raw());

  LOGT("Trying to download the data for " << url);

  perform();

  return cbuff;
}

CURLController::download_buffer& CURLController::post(
    const std::string& url, const std::string& body,
    const std::vector<std::string>& headers)
{
  if (!prepare(url)) {
    return cbuff;
  }

  const HeadersList headerList{headers};

  // No low speed abort here: a server that is still composing it's answer
  // sends nothing meanwhile, which the low speed limit takes for a stall.
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, DEFAULT_POST_TIMEOUT);
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(body.size()));
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList.raw());

  LOGT("Trying to post " << body.size() << " bytes to " << url);

  perform();

  return cbuff;
}

bool CURLController::is_url_alive(const std::string& url)
{
  if (!prepare(url)) {
    return false;
  }

  curl_easy_setopt(curl, CURLOPT_TIMEOUT, DEFAULT_TIMEOUT);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

  LOGT("Trying to check whether the " << url << " is alive");

  if (perform() != CURLE_OK) {
    return false;
  }

  // A protocol that carries no statuses (the file one, for example) reports a
  // zero code, so a performed request is the reachability proof by itself.
  return responseCode < HTTP_FIRST_ERROR_STATUS;
}

CURLControllerPtr CURLController::create()
{
  return std::make_shared<CURLController>();
}

}  // namespace curli
