#include "src/Firebird/helpers/FbConnStringMaker.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace firebirdi::helpers
{

std::string FbConnStringMaker::make_conn_string(
    std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return {};
  }

  // Firebird database strings look like next:
  //   employee                          (local database/alias)
  //   localhost:employee                (remote, default port)
  //   localhost/3050:/var/db/test.fdb   (remote, explicit port)

  std::string connStr;

  if (!actx->get_fb_host().empty()) {
    connStr += actx->get_fb_host();

    if (!actx->get_fb_port().empty()) {
      connStr += "/" + actx->get_fb_port();
    }

    connStr += ":";
  }

  connStr += actx->get_fb_dbname();

  return connStr;
}

}  // namespace firebirdi::helpers
