#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/CFITSIO/CFITSIOController.h"
#include "src/WCSLIB/WCSLIBController.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace cfitsioi;
using namespace wcslibi;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override
  {
    CFITSIOController::onMockCreate = nullptr;
    WCSLIBController::onMockCreate = nullptr;
  }

  inline static const std::string IMAGE_PATH{"/tmp/an-image.fits"};

  /// @brief Any world coordinate of the two celestial axes the read image
  /// holds does, so this is just a readable pair.
  inline static const WCSLIBController::coordinates SAMPLE_WORLD{10.0, 20.0};

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_Application, context_without_an_image_reads_nothing)
{
  MockFunction<void(CFITSIOController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_)).Times(0);

  CFITSIOController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, reads_the_image_of_the_context)
{
  appCtx->set_image_path(IMAGE_PATH);

  MockFunction<void(CFITSIOController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](CFITSIOController& instance) {
        EXPECT_CALL(instance, open(IMAGE_PATH, false))
            .Times(1)
            .WillOnce(Return(true));
        EXPECT_CALL(instance, create_image(_, _)).Times(0);
        EXPECT_CALL(instance, write(_)).Times(0);

        // Once for the size report and once for the centre pixel of it.
        EXPECT_CALL(instance, get_image_size()).Times(2);
        EXPECT_CALL(instance, get_hdu_count()).Times(1);
        EXPECT_CALL(instance, read_keyword(_)).Times(1);
        EXPECT_CALL(instance, read()).Times(1);
        EXPECT_CALL(instance, read_header()).Times(1);
      }));

  CFITSIOController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, reports_the_coordinates_of_the_read_image)
{
  appCtx->set_image_path(IMAGE_PATH);

  MockFunction<void(WCSLIBController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](WCSLIBController& instance) {
        InSequence conversion;

        EXPECT_CALL(instance, parse(_)).WillOnce(Return(true));
        EXPECT_CALL(instance, get_axis_type(_)).Times(2);
        EXPECT_CALL(instance, to_world(_)).WillOnce(Return(SAMPLE_WORLD));
      }));

  WCSLIBController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, unopenable_image_returns_invalid)
{
  appCtx->set_image_path(IMAGE_PATH);

  MockFunction<void(CFITSIOController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](CFITSIOController& instance) {
        EXPECT_CALL(instance, open(_, _)).Times(1).WillOnce(Return(false));
        EXPECT_CALL(instance, read()).Times(0);
        EXPECT_CALL(instance, read_header()).Times(0);
      }));

  CFITSIOController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(1);

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, image_without_the_coordinates_is_still_read)
{
  appCtx->set_image_path(IMAGE_PATH);

  MockFunction<void(WCSLIBController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](WCSLIBController& instance) {
        EXPECT_CALL(instance, parse(_)).WillOnce(Return(false));
        EXPECT_CALL(instance, to_world(_)).Times(0);
      }));

  WCSLIBController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, image_with_the_untyped_axes_is_still_read)
{
  appCtx->set_image_path(IMAGE_PATH);

  MockFunction<void(WCSLIBController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](WCSLIBController& instance) {
        EXPECT_CALL(instance, parse(_)).WillOnce(Return(true));
        EXPECT_CALL(instance, get_axis_type(_))
            .WillRepeatedly(Return(std::string{}));
        EXPECT_CALL(instance, to_world(_)).Times(0);
      }));

  WCSLIBController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, unconvertible_centre_pixel_is_still_read)
{
  appCtx->set_image_path(IMAGE_PATH);

  MockFunction<void(WCSLIBController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](WCSLIBController& instance) {
        EXPECT_CALL(instance, parse(_)).WillOnce(Return(true));
        EXPECT_CALL(instance, to_world(_))
            .WillOnce(Return(WCSLIBController::coordinates{}));
      }));

  WCSLIBController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_EQ(app->run(appCtx), 0);
}
