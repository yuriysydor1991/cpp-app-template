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

const std::string& ApplicationContext::get_claude_token() const
{
  return mclaude_token;
}

void ApplicationContext::set_claude_token(const std::string& newValue)
{
  mclaude_token = newValue;
}

const std::string& ApplicationContext::get_claude_question() const
{
  return mclaude_question;
}

void ApplicationContext::set_claude_question(const std::string& newValue)
{
  mclaude_question = newValue;
}

const std::string& ApplicationContext::get_claude_model() const
{
  return mclaude_model;
}

void ApplicationContext::set_claude_model(const std::string& newValue)
{
  mclaude_model = newValue;
}

}  // namespace app
