#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H

#include <Wt/WApplication.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"
#include "src/wt4/Wt4Context.h"
#include "src/wt4/widgets/WidgetsFactory.h"

/**
 * @brief The Wt4 implementation namespace for the template project.
 */
namespace wt4server
{

/**
 * @brief The Wt instance initer and runner class.
 */
class Wt4Server : public Wt::WApplication
{
 public:
  virtual ~Wt4Server() = default;
  Wt4Server(const Wt::WEnvironment& env, std::shared_ptr<Wt4Context> nwt4ctx);

  /**
   * @brief Starts the Wt4 application http service.
   *
   * @param ctx Application's run context with provided data to run the Wt site.
   *
   * @return Returns the application return status. A zero value on the success
   * and other value otherwise.
   */
  static int run(std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  static std::unique_ptr<Wt4Server> build_server(
      const Wt::WEnvironment& env,
      std::shared_ptr<app::ApplicationContext> ctx);
  static std::shared_ptr<Wt4Context> create_context(
      std::shared_ptr<app::ApplicationContext> ctx);

  std::shared_ptr<Wt4Context> wt4ctx;
  std::unique_ptr<widgets::WidgetsFactory> wfactory;
};

}  // namespace wt4server

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H
