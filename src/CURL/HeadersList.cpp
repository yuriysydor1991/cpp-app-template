#include "src/CURL/HeadersList.h"

#include <string>
#include <vector>

#include "src/log/log.h"

namespace curli
{

HeadersList::HeadersList(const std::vector<std::string>& headers)
{
  for (const auto& header : headers) {
    // A failed append gives a null back and leaves the list untouched, so the
    // list is kept for the release instead of being overwritten by the null.
    struct curl_slist* const extended = curl_slist_append(list, header.c_str());

    if (extended == nullptr) {
      LOGE("Fail to append an HTTP header to the request");
      appended = false;
      return;
    }

    list = extended;
  }
}

HeadersList::~HeadersList() { curl_slist_free_all(list); }

bool HeadersList::complete() const { return appended; }

struct curl_slist* HeadersList::raw() const { return list; }

}  // namespace curli
