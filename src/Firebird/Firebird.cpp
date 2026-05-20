#include "src/Firebird/Firebird.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/Firebird/driver/FbClient.h"
#include "src/Firebird/helpers/FbConnStringMaker.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"

namespace firebirdi
{

bool Firebird::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx != nullptr);

  if (nctx == nullptr) {
    LOGE("No valid application context provided")
    return false;
  }

  actx = nctx;

  qmaker = create_query_maker();
  client = create_client();

  assert(client != nullptr);

  if (client == nullptr) {
    LOGE("Failure to create the Firebird client");
    return false;
  }

  return client->attach(make_conn_string(), actx->fb_user, actx->fb_password);
}

std::shared_ptr<IFbClient> Firebird::create_client()
{
  return driver::create_fb_client();
}

std::shared_ptr<sql::QueryMaker> Firebird::create_query_maker()
{
  return std::make_shared<sql::QueryMaker>(actx);
}

std::string Firebird::make_conn_string()
{
  auto csmaker = std::make_shared<helpers::FbConnStringMaker>();

  return csmaker->make_conn_string(actx);
}

bool Firebird::connected()
{
  return client != nullptr && client->attached();
}

std::string Firebird::get_current_date()
{
  assert(client != nullptr);
  assert(qmaker != nullptr);

  if (!connected()) {
    LOGE("Not connected");
    return {};
  }

  static const std::string dquery = qmaker->make_date_query();

  return client->query_scalar(dquery);
}

}  // namespace firebirdi
