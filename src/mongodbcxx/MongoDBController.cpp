#include "src/mongodbcxx/MongoDBController.h"

#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"
#include "src/log/log.h"
#include "src/mongodbcxx/converters/MongoDBDate2String.h"
#include "src/mongodbcxx/helpers/MongoDBConnStringMaker.h"

namespace mongodbcxxi
{

MongoDBController::MongoDBController()
{
  // should be created only once
  static mongocxx::instance inst{};
}

bool MongoDBController::connect(std::shared_ptr<app::ApplicationContext> nctx)
{
  assert(nctx != nullptr);

  if (nctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  actx = nctx;

  try {
    auto csMaker = std::make_shared<helpers::MongoDBConnStringMaker>();
    qmaker = std::make_shared<helpers::QueryMaker>(actx);

    const std::string connString = csMaker->make_conn_string(actx);

    const mongocxx::uri connURI{connString};

    dbclient = mongocxx::client{connURI};

    dbconnection = dbclient["admin"];
  }
  catch (const std::exception& e) {
    LOGE("Error during query execution: " << e.what());
    return false;
  }

  return true;
}

bool MongoDBController::connected()
{
  assert(qmaker != nullptr);

  std::shared_ptr<DBJsonRes> pingRes =
      execute_query(qmaker->create_ping_query());

  return pingRes != nullptr;
}

std::shared_ptr<MongoDBController::DBJsonRes> MongoDBController::execute_query(
    JsonDoc queryDoc)
{
  std::shared_ptr<DBJsonRes> result;

  try {
    result = std::make_shared<DBJsonRes>(
        dbconnection.run_command(std::move(queryDoc)));
  }
  catch (const std::exception& e) {
    LOGE("Error during query execution: " << e.what());
  }

  return result;
}

std::string MongoDBController::get_current_date()
{
  assert(qmaker != nullptr);

  if (!connected()) {
    return {};
  }

  std::shared_ptr<DBJsonRes> result =
      execute_query(qmaker->create_date_query());

  assert(result != nullptr);

  if (result == nullptr) {
    return {};
  }

  auto view = result->view();
  auto ltiter = view.find(localTime);

  if (ltiter == view.end()) {
    return {};
  }

  const auto retrievedDate = ltiter->get_date();
  converters::MongoDBDate2String date_cvt;

  return date_cvt.convert(retrievedDate);
}

}  // namespace mongodbcxxi
