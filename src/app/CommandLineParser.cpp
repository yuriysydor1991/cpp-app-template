#include "src/app/CommandLineParser.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>
#include <set>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/app/CMDParamNames.h"
#include "src/log/log.h"

namespace app
{

namespace
{

using PathSetter = void (ApplicationContext::*)(const std::string&);

/// @brief The parameters of the files paths with the context setters of
/// theirs.
const std::map<std::string, PathSetter>& path_params()
{
  static const std::map<std::string, PathSetter> params{
      {CMDParamNames::CFGW, &ApplicationContext::set_cfg_path},
      {CMDParamNames::CFG, &ApplicationContext::set_cfg_path},
      {CMDParamNames::WEIGHTSW, &ApplicationContext::set_weights_path},
      {CMDParamNames::WEIGHTS, &ApplicationContext::set_weights_path},
      {CMDParamNames::DXXWJZ1W, &ApplicationContext::set_dxxwjz1_path},
      {CMDParamNames::DXXWJZ2W, &ApplicationContext::set_dxxwjz2_path},
      {CMDParamNames::NAMESW, &ApplicationContext::set_names_path},
      {CMDParamNames::NAMES, &ApplicationContext::set_names_path},
      {CMDParamNames::IMAGEW, &ApplicationContext::set_image_path},
      {CMDParamNames::IMAGE, &ApplicationContext::set_image_path}};

  return params;
}

}  // namespace

bool CommandLineParser::parse_args(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  for (int iter = 1; iter < ctx->get_argc(); ++iter) {
    const int nextIter = iter + 1;
    const bool hasNext = nextIter < ctx->get_argc();

    const std::string param = ctx->get_argv()[iter];
    const std::string nextParam =
        hasNext ? ctx->get_argv()[nextIter] : std::string{};

    if (!parse_arg(ctx, param, hasNext, nextParam, iter)) {
      LOGE("Failure to parse arg: " << param);
      return false;
    }
  }

  return true;
}

bool CommandLineParser::check_4_data(
    std::shared_ptr<ApplicationContext> ctx, const std::string& param,
    const bool hasNext, [[maybe_unused]] const std::string& nextParam)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return false;
  }

  const bool requiresData = requires_data(param);

  if (requiresData && !hasNext) {
    ctx->set_print_version_and_exit(true);
    ctx->push_error("Parameter " + param + " requires the data next to it.");
    LOGE("Parameter " << param << " requires the data next to it.");
    return false;
  }

  return true;
}

bool CommandLineParser::parse_arg(std::shared_ptr<ApplicationContext> ctx,
                                  const std::string& param, const bool hasNext,
                                  [[maybe_unused]] const std::string& nextParam,
                                  int& paramIndex)
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
    ctx->set_print_help_and_exit(true);
  } else if (param == CMDParamNames::VERSIONW ||
             param == CMDParamNames::VERSION) {
    ctx->set_print_version_and_exit(true);
  } else if (param == CMDParamNames::LOGPATHW ||
             param == CMDParamNames::LOGPATH) {
    // skipping already parsed cmd params
    paramIndex++;
    return true;
  } else if (const auto path = path_params().find(param);
             path != path_params().cend()) {
    ((*ctx).*(path->second))(nextParam);
  } else {
    ctx->set_print_help_and_exit(true);
    ctx->push_error("Unknown parameter: " + param);
    LOGE("Unknown parameter: " << param);
    return false;
  }

  if (hasNext && requires_data(param)) {
    paramIndex++;
  }

  return true;
}

const std::set<std::string>& CommandLineParser::get_params_requiring_data()
{
  // Place here command line parameters that are requiring
  // some data after it.
  static const std::set<std::string> requireNext{
      CMDParamNames::LOGPATHW, CMDParamNames::LOGPATH,  CMDParamNames::CFGW,
      CMDParamNames::CFG,      CMDParamNames::WEIGHTSW, CMDParamNames::WEIGHTS,
      CMDParamNames::DXXWJZ1W, CMDParamNames::DXXWJZ2W, CMDParamNames::NAMESW,
      CMDParamNames::NAMES,    CMDParamNames::IMAGEW,   CMDParamNames::IMAGE};

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
