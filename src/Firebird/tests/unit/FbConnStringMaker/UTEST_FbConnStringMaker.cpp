#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/Firebird/helpers/FbConnStringMaker.h"
#include "src/app/ApplicationContext.h"

using namespace firebirdi::helpers;
using namespace app;
using namespace testing;

class UTEST_FbConnStringMaker : public Test
{
 public:
  UTEST_FbConnStringMaker()
      : maker{std::make_shared<FbConnStringMaker>()},
        ctx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    ctx->fb_dbname = "employee";
    ctx->fb_host.clear();
    ctx->fb_port.clear();
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<FbConnStringMaker> maker;
  std::shared_ptr<ApplicationContext> ctx;
};

TEST_F(UTEST_FbConnStringMaker, null_context_returns_empty)
{
  EXPECT_TRUE(maker->make_conn_string(nullptr).empty());
}

TEST_F(UTEST_FbConnStringMaker, local_database_only)
{
  EXPECT_EQ(maker->make_conn_string(ctx), "employee");
}

TEST_F(UTEST_FbConnStringMaker, remote_host_default_port)
{
  ctx->fb_host = "localhost";

  EXPECT_EQ(maker->make_conn_string(ctx), "localhost:employee");
}

TEST_F(UTEST_FbConnStringMaker, remote_host_explicit_port)
{
  ctx->fb_host = "localhost";
  ctx->fb_port = "3050";

  EXPECT_EQ(maker->make_conn_string(ctx), "localhost/3050:employee");
}

TEST_F(UTEST_FbConnStringMaker, port_without_host_is_ignored)
{
  ctx->fb_port = "3050";

  EXPECT_EQ(maker->make_conn_string(ctx), "employee");
}
