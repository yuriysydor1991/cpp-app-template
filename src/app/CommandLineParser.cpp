#include <memory>
#include <cassert>
#include <string>
#include <set>
#include <algorithm>

#include "src/app/ApplicationContext.h"
#include "src/app/CommandLineParser.h"

namespace app {

namespace {
  const std::string HELPW {"--help"};
  const std::string HELP {"-h"};
}

bool CommandLineParser::parse_args(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr)
  { return false ; }

  for (int iter = 1; iter < ctx->argc; ++iter) 
  {
    const int nextIter = iter + 1;
    const bool hasNext = nextIter < ctx->argc;

    const std::string param = ctx->argv[iter];
    const std::string nextParam = hasNext ? ctx->argv[nextIter] : std::string{};

    if (!parse_arg(ctx, param, hasNext, nextParam, iter))
    { return false ; }
  }

  return true ;
}

bool CommandLineParser::check_4_data(
    std::shared_ptr<ApplicationContext> ctx,
    const std::string& param, 
    const int& hasNext,
    const std::string& nextParam)
{
  // Place here command line parameters that are requiring
  // some data after it.
  static const std::set<std::string> requireNext{};

  assert(ctx != nullptr);

  if (ctx == nullptr)
  { return false ; }

  const bool requiresData = std::find(
    requireNext.cbegin(), requireNext.cend(), param) != requireNext.cend();

  if (requiresData && !hasNext) 
  {
    ctx->push_error("Parameter " + param + " requires the data next to it.");
    return false ; 
  }

  return (hasNext && !nextParam.empty()) || true ;
}

bool CommandLineParser::parse_arg(
  std::shared_ptr<ApplicationContext> ctx,
  const std::string& param, 
  const int& hasNext, 
  const std::string& nextParam,
  int& paramIndex)
{
  assert(ctx != nullptr);

  if (!check_4_data (ctx, param, hasNext, nextParam))
  { return false ; }

  // add a new params parse over here
  if (param == HELPW || param == HELP)
  { ctx->print_help_and_exit = true; }
  else
  {
    ctx->print_help_and_exit = true;
    ctx->push_error("Unknown parameter: " + param);
    return false;
  }

  if (hasNext)
  { paramIndex ++ ; }

  return (hasNext && nextParam.empty()) || true ;
}

} // namespace app
