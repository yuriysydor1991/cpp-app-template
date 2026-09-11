#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDPACK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDPACK_CLASS_H

#include <memory>
#include <string>

/**
 * @brief The Freesound CC0 sound categories adaptor subsystem namespace.
 */
namespace freesoundaudio
{

/**
 * @brief A single Freesound sound category.
 *
 * Freesound publishes it's sound effects as separate CC0 categories, each one
 * downloaded as an own archive and unpacked into an own subdirectory of the
 * categories root directory. Every descendant answers for one of those
 * categories, so the calling code names a category by an instance instead of an
 * enumeration value and gains a new category by a new descendant alone.
 */
class IFreesoundCategory
{
 public:
  using IFreesoundCategoryPtr = std::shared_ptr<IFreesoundCategory>;

  virtual ~IFreesoundCategory() = default;

  /**
   * @brief Gives the category name, which is also the name of it's subdirectory
   * inside the categories root directory.
   *
   * @return Returns the category name, the "interface-sounds" one for example.
   */
  virtual std::string name() const = 0;
};

using IFreesoundCategoryPtr = IFreesoundCategory::IFreesoundCategoryPtr;

}  // namespace freesoundaudio

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFREESOUNDPACK_CLASS_H
