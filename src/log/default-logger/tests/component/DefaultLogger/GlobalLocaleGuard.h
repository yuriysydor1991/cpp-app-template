#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBALLOCALEGUARD_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBALLOCALEGUARD_CLASS_H

#include <locale>

/**
 * @brief Restores the previously installed global locale, so a single test can
 * not leak its locale into the rest of the test binary.
 */
class GlobalLocaleGuard
{
 public:
  explicit GlobalLocaleGuard(const std::locale& newGlobal);

  ~GlobalLocaleGuard();

 private:
  std::locale previous;
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GLOBALLOCALEGUARD_CLASS_H
