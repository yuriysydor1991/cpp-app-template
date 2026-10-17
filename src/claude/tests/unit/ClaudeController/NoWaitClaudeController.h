#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_UTEST_NOWAITCLAUDECONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_UTEST_NOWAITCLAUDECONTROLLER_CLASS_H

#include "src/claude/ClaudeController.h"

/**
 * @brief The Claude questioner repeating the failed calls right away, so the
 * retry tests take no retry delays.
 */
class NoWaitClaudeController : public claudei::ClaudeController
{
 public:
  using claudei::ClaudeController::ClaudeController;

 protected:
  void wait_before_retry(const unsigned int /*attempt*/) const override {}
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_UTEST_NOWAITCLAUDECONTROLLER_CLASS_H
