#include "src/CURL/CURLController.h"

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "project-global-decls.h"
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

  // A returned size other than the given one aborts the whole transfer, which
  // is how the response size constraint is enforced for an answer carrying no
  // length of it's own (a chunked one, for example).
  if (!controller->append(static_cast<const char*>(contents), givenSize)) {
    return 0U;
  }

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

bool CURLController::append(const char* const data, const std::size_t size)
{
  assert(data != nullptr);

  if (cbuff.size() + size > MAX_RESPONSE_BYTES) {
    LOGE("The response has outgrown the allowed " << MAX_RESPONSE_BYTES
                                                  << " bytes");
    return false;
  }

  // No reserve of the exact size here: it would reallocate the whole buffer
  // for every arriving chunk, which a server sending the answer byte by byte
  // would turn into a copying of a quadratic cost.
  cbuff.insert(cbuff.end(), data, data + size);

  return true;
}

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

  return harden();
}

bool CURLController::harden()
{
  // No signal is raised for the timeouts, which keeps the request usable from
  // a thread of it's own.
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

  // The defaults of the libcurl already, set here so that no build with
  // another default and no descendant lowers them unnoticed.
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, SSL_VERIFY_HOSTNAME);
  curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);

  // The answer announcing a bigger size is refused before a single byte of it
  // is transferred. The one announcing no size at all is cut by the write
  // callback instead.
  curl_easy_setopt(curl, CURLOPT_MAXFILESIZE_LARGE,
                   static_cast<curl_off_t>(MAX_RESPONSE_BYTES));

#if LIBCURL_VERSION_NUM >= 0x075500
  // A crafted URL reaches no scp, no smb and no dict service of the local
  // network. The option arrived with the 7.85.0 release, so an older libcurl
  // keeps the protocols of it's own build.
  if (curl_easy_setopt(curl, CURLOPT_PROTOCOLS_STR,
                       project_decls::PROJECT_CURL_ALLOWED_PROTOCOLS.c_str()) !=
      CURLE_OK) {
    LOGE("Fail to allow the "
         << project_decls::PROJECT_CURL_ALLOWED_PROTOCOLS
         << " protocols only. Check the PROJECT_CURL_ALLOWED_PROTOCOLS value");
    return false;
  }
#endif

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
