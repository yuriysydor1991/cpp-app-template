#include "src/app/ApplicationContext.h"

#include <string>
#include <vector>

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}
{
}

int& ApplicationContext::get_argc() const { return margc; }

char**& ApplicationContext::get_argv() const { return margv; }

bool ApplicationContext::get_print_help_and_exit() const
{
  return mprint_help_and_exit;
}

void ApplicationContext::set_print_help_and_exit(const bool newValue)
{
  mprint_help_and_exit = newValue;
}

bool ApplicationContext::get_print_version_and_exit() const
{
  return mprint_version_and_exit;
}

void ApplicationContext::set_print_version_and_exit(const bool newValue)
{
  mprint_version_and_exit = newValue;
}

const std::vector<std::string>& ApplicationContext::get_errors() const
{
  return merrors;
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  merrors.emplace_back(errorDescription);
}

bool ApplicationContext::get_stop() const { return mstop.load(); }

void ApplicationContext::set_stop(const bool newValue)
{
  mstop.store(newValue);
}

bool ApplicationContext::get_pause() const { return mpause.load(); }

void ApplicationContext::set_pause(const bool newValue)
{
  mpause.store(newValue);
}

bool ApplicationContext::get_reload() const { return mreload.load(); }

void ApplicationContext::set_reload(const bool newValue)
{
  mreload.store(newValue);
}

bool ApplicationContext::get_first_user_request() const
{
  return mfirst_user_request.load();
}

void ApplicationContext::set_first_user_request(const bool newValue)
{
  mfirst_user_request.store(newValue);
}

bool ApplicationContext::get_second_user_request() const
{
  return msecond_user_request.load();
}

void ApplicationContext::set_second_user_request(const bool newValue)
{
  msecond_user_request.store(newValue);
}

}  // namespace app
