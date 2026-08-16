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

const std::string& ApplicationContext::get_openai_token() const
{
  return mopenai_token;
}

void ApplicationContext::set_openai_token(const std::string& newValue)
{
  mopenai_token = newValue;
}

const std::string& ApplicationContext::get_openai_question() const
{
  return mopenai_question;
}

void ApplicationContext::set_openai_question(const std::string& newValue)
{
  mopenai_question = newValue;
}

const std::string& ApplicationContext::get_openai_model() const
{
  return mopenai_model;
}

void ApplicationContext::set_openai_model(const std::string& newValue)
{
  mopenai_model = newValue;
}

}  // namespace app
