#include "src/gettext/CatalogsLocator.h"

#include <filesystem>
#include <string>
#include <system_error>
#include <utility>

namespace gettexti
{

CatalogsLocator::CatalogsLocator(std::string relative, std::string build,
                                 std::string install)
    : relativeDir{std::move(relative)},
      buildDir{std::move(build)},
      installDir{std::move(install)}
{
}

std::string CatalogsLocator::locate(const std::string& execPath) const
{
  namespace fs = std::filesystem;

  std::error_code error;
  const fs::path execDir = fs::path{execPath}.parent_path();

  if (!execDir.empty()) {
    // The libintl resolves a relative directory against the current one each
    // time it loads a catalog, so an absolute one is bound.
    const fs::path nextToExec =
        fs::absolute(execDir / relativeDir, error).lexically_normal();

    if (fs::is_directory(nextToExec, error)) {
      return nextToExec.string();
    }
  }

  return fs::is_directory(buildDir, error) ? buildDir : installDir;
}

std::string CatalogsLocator::executable(const std::string& execPath)
{
  std::error_code error;
  const std::filesystem::path self =
      std::filesystem::read_symlink("/proc/self/exe", error);

  return error ? execPath : self.string();
}

}  // namespace gettexti
