#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ASIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ASIGNALSHANDLER_CLASS_H

#include <memory>
#include <set>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/ISignalsHandler.h"

namespace app
{

/**
 * @brief The OS reaction on a handled signal arrival, which is the second
 * std::signal argument type - either a routine to call or one of the special
 * SIG_IGN and SIG_DFL values.
 */
using SignalDisposition = void (*)(int);

/**
 * @brief The common std::signal based skeleton of a single OS signals category
 * handler.
 *
 * The class knows how to subscribe the process to a set of the OS signals and
 * how to give them back to the OS default disposition, while a descendant only
 * tells which signals its category consists of, which routine reacts on them
 * and where the handled context pointer is kept, so a new category costs a
 * couple of small overrides only.
 */
class ASignalsHandler : public ISignalsHandler
{
 public:
  /**
   * @brief The destructor does NOT release the handled signals, since the
   * ASignalsHandler::uninstall method reaches the pure virtual
   * ASignalsHandler::store_context one, which is unreachable from a base class
   * destructor. So every descendant is the one to call the
   * ISignalsHandler::uninstall method from its own destructor.
   */
  ~ASignalsHandler() override = default;
  ASignalsHandler() = default;

  /**
   * @brief Makes the ASignalsHandler::get_signal_disposition value the OS
   * disposition of every ASignalsHandler::get_handled_signals signal and
   * remembers the given context with the ASignalsHandler::store_context
   * method. See the ISignalsHandler interface.
   *
   * @param ctx The context to hand over to the handler routine.
   *
   * @return Returns true if at least one signal of the category is handled
   * from now on and false in case of any error, as well as on the platforms
   * which are declaring none of the category signals.
   */
  virtual bool install(std::shared_ptr<ApplicationContext> ctx) override;

  /// @brief Gives the covered signals back to the OS default disposition and
  /// releases the remembered context. See the ISignalsHandler interface.
  virtual void uninstall() override;

 protected:
  /**
   * @brief Method should return the set of the OS signals numbers the
   * descendant category consists of. An empty set is a valid answer of a
   * category which the current platform declares no signals for.
   */
  virtual const std::set<int>& get_handled_signals() = 0;

  /**
   * @brief Method should return the OS reaction on every covered signal
   * arrival, which is either a routine to call or the special SIG_IGN value of
   * a category the application deliberately ignores.
   *
   * **A returned routine is allowed to use the async signal safe calls only**,
   * so it is expected to touch the lock free atomics and to do no logging, no
   * memory allocation and no locking at all.
   *
   * The SIG_DFL value is not a valid answer, since it equals a nullptr one,
   * which the ASignalsHandler::install method rejects. Leave a category out of
   * the SignalsHandler::create_handlers set to keep the OS default reaction on
   * its signals.
   */
  virtual SignalDisposition get_signal_disposition() = 0;

  /**
   * @brief Method should keep the given context pointer where the routine of
   * the ASignalsHandler::get_signal_disposition method reads it from, which is
   * a lock free atomic of the descendant, since the std::signal handler
   * accepts no user data argument. A descendant which ignores its signals has
   * nothing to keep, so an empty override is a valid one there.
   *
   * @param ctx The context to remember or a nullptr one to forget the previous
   * one.
   */
  virtual void store_context(ApplicationContext* ctx) = 0;

 private:
  /// @brief The signals that are covered by the current instance and are to be
  /// released by the ASignalsHandler::uninstall method.
  std::set<int> minstalled_signals;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ASIGNALSHANDLER_CLASS_H
