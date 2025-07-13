#include "src/app/CommandLineParser.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <set>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/app/CMDParamNames.h"
#include "src/log/log.h"

namespace app
{

bool CommandLineParser::parse_args(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  for (int iter = 1; iter < ctx->argc; ++iter) {
    const int nextIter = iter + 1;
    const bool hasNext = nextIter < ctx->argc;

    const std::string param = ctx->argv[iter];
    const std::string nextParam = hasNext ? ctx->argv[nextIter] : std::string{};

    if (!parse_arg(ctx, param, hasNext, nextParam, iter)) {
      LOGE("Failure to parse arg: " << param);
      return false;
    }
  }

  return true;
}

bool CommandLineParser::check_4_data(std::shared_ptr<ApplicationContext> ctx,
                                     const std::string& param,
                                     const int& hasNext,
                                     const std::string& nextParam)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  const bool requiresData = requires_data(param);

  if (requiresData && !hasNext) {
    ctx->print_version_and_exit = true;
    ctx->push_error("Parameter " + param + " requires the data next to it.");
    LOGE("Parameter " << param << " requires the data next to it.");
    return false;
  }

  return (hasNext && !nextParam.empty()) || true;
}

bool CommandLineParser::parse_arg(std::shared_ptr<ApplicationContext> ctx,
                                  const std::string& param, const int& hasNext,
                                  const std::string& nextParam, int& paramIndex)
{
  assert(ctx != nullptr);

  if (!check_4_data(ctx, param, hasNext, nextParam)) {
    LOGE("Failure with param data");
    return false;
  }

  // add a new params parse over here
  // Also register new command line parameters in the ApplicationhelpPrinter's
  // help.
  if (param == CMDParamNames::HELPW || param == CMDParamNames::HELP) {
    ctx->print_help_and_exit = true;
  } else if (param == CMDParamNames::VERSIONW ||
             param == CMDParamNames::VERSION) {
    ctx->print_version_and_exit = true;
  } else if (param == CMDParamNames::LOGPATHW ||
             param == CMDParamNames::LOGPATH) {
    // skipping already parsed cmd params
    paramIndex++;
    return true;
  } else {
    ctx->print_help_and_exit = true;
    ctx->push_error("Unknown parameter: " + param);
    LOGE("Unknown parameter: " << param);
    return false;
  }

  if (hasNext && requires_data(param)) {
    paramIndex++;
  }

  return (hasNext && nextParam.empty()) || true;
}

const std::set<std::string>& CommandLineParser::get_params_requiring_data()
{
  // Place here command line parameters that are requiring
  // some data after it.
  static const std::set<std::string> requireNext{CMDParamNames::LOGPATHW,
                                                 CMDParamNames::LOGPATH};

  return requireNext;
}

bool CommandLineParser::requires_data(const std::string& param)
{
  const auto& requireNext = get_params_requiring_data();

  return std::find(requireNext.cbegin(), requireNext.cend(), param) !=
         requireNext.cend();
}

std::string CommandLineParser::get_custom_logfile(const int& gargc,
                                                  char** const& gargv)
{
  std::string logf;

  for (int iter = 1; iter < gargc; ++iter) {
    if ((gargv[iter] == CMDParamNames::LOGPATHW ||
         gargv[iter] == CMDParamNames::LOGPATH) &&
        (iter + 1) < gargc) {
      logf = gargv[iter + 1];
    }
  }

  return logf;
}

}  // namespace app
