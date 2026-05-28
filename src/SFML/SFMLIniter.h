#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLINITER_CLASS_H

#include <memory>

#include "src/SFML/Eventer/EventsController.h"
#include "src/SFML/Painter/Painter.h"
#include "src/SFML/SFMLContext.h"
#include "src/SFML/SFMLContextBuilder.h"
#include "src/app/ApplicationContext.h"

namespace templateSFML
{

/**
 * @brief The initialization and event loop runner class for the SFML.
 */
class SFMLIniter
{
 public:
  virtual ~SFMLIniter();
  SFMLIniter();

  /**
   * @brief Init and run the SFML event loop.
   *
   * @param ctx Application's run context with command line parameters etc.
   *
   * @return Returns the init and run return status. A zero value on the success
   * and other value otherwise.
   */
  virtual int run(std::shared_ptr<app::ApplicationContext> ctx);

 protected:
  virtual void event_loop();

  std::shared_ptr<SFMLContextBuilder> ctxBuilder;
  std::shared_ptr<SFMLContext> sfmlContext;

  std::shared_ptr<events::EventsController> events;
  std::shared_ptr<painter::Painter> painter2d;
};

}  // namespace templateSFML

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLINITER_CLASS_H
