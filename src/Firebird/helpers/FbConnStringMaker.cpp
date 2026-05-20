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

  if (!actx->fb_host.empty()) {
    connStr += actx->fb_host;

    if (!actx->fb_port.empty()) {
      connStr += "/" + actx->fb_port;
    }

    connStr += ":";
  }

  connStr += actx->fb_dbname;

  return connStr;
}

}  // namespace firebirdi::helpers
