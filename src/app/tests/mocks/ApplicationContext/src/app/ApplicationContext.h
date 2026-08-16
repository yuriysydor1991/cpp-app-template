#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <atomic>
#include <string>
#include <vector>

namespace app
{

class ApplicationContext
{
 public:
  ApplicationContext(int& gargc, char**& gargv);

  int& get_argc() const { return margc; }
  char**& get_argv() const { return margv; }

  bool get_print_help_and_exit() const { return mprint_help_and_exit; }
  void set_print_help_and_exit(const bool newValue)
  {
    mprint_help_and_exit = newValue;
  }

  bool get_print_version_and_exit() const { return mprint_version_and_exit; }
  void set_print_version_and_exit(const bool newValue)
  {
    mprint_version_and_exit = newValue;
  }

  const std::vector<std::string>& get_errors() const { return merrors; }

  bool get_stop() const { return mstop.load(); }
  void set_stop(const bool newValue) { mstop.store(newValue); }

  const std::string& get_openai_token() const { return mopenai_token; }
  void set_openai_token(const std::string& newValue)
  {
    mopenai_token = newValue;
  }

  const std::string& get_openai_question() const { return mopenai_question; }
  void set_openai_question(const std::string& newValue)
  {
    mopenai_question = newValue;
  }

  const std::string& get_openai_model() const { return mopenai_model; }
  void set_openai_model(const std::string& newValue)
  {
    mopenai_model = newValue;
  }

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

 private:
  int& margc;
  char**& margv;
  bool mprint_help_and_exit{false};
  bool mprint_version_and_exit{false};
  std::vector<std::string> merrors;
  std::atomic_bool mstop{false};
  std::string mopenai_token;
  std::string mopenai_question;
  std::string mopenai_model;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
