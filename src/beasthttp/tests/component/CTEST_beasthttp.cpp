#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <thread>

#include "src/beasthttp/HttpController.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace testing;
using namespace beasthttp;

class CTEST_beasthttp : public Test
{
 public:
  virtual ~CTEST_beasthttp() = default;
  CTEST_beasthttp(): http{HttpController::create()} {
    EXPECT_NE(http, nullptr);
  }

  std::shared_ptr<HttpController> http;
};

TEST_F(CTEST_beasthttp, invalid_context_pointer_failure)
{
  EXPECT_FALSE(http->serve({}));
}

TEST_F(CTEST_beasthttp, bootstrap_success)
{
  int argc{0};
  char** argv{nullptr};

  auto actx = std::make_shared<ApplicationContext>(argc, argv);
  
  actx->stop(true);

  std::thread httpThread{[this, actx](){
    EXPECT_TRUE(http->serve(actx));
  }};

  httpThread.join();
}
