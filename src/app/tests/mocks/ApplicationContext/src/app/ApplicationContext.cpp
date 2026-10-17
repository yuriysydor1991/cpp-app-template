#include "src/app/ApplicationContext.h"

namespace app
{

const std::string ApplicationContext::default_db_name = "default_db_name";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}, mdb_dbname{default_db_name}
{
  // The pushed errors are kept like the real context keeps them, so the test
  // cases see them through the get_errors accessor too.
  ON_CALL(*this, push_error(testing::_))
      .WillByDefault([this](const std::string& errorDescription) {
        merrors.push_back(errorDescription);
      });
}

}  // namespace app
