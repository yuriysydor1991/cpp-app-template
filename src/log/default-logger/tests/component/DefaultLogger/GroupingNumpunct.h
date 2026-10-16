#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GROUPINGNUMPUNCT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GROUPINGNUMPUNCT_CLASS_H

#include <locale>
#include <string>

/**
 * @brief A numpunct facet which groups the digits by three, like most of the
 * real world locales do. Imbuing it globally is what an application does
 * implicitly by calling std::locale::global(std::locale("")) on a host
 * configured with such a locale.
 */
class GroupingNumpunct : public std::numpunct<char>
{
 protected:
  char do_thousands_sep() const override;
  std::string do_grouping() const override;
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GROUPINGNUMPUNCT_CLASS_H
