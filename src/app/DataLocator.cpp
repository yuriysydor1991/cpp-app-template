#include "src/app/DataLocator.h"

#include <filesystem>
#include <string>
#include <system_error>

#include "project-global-decls.h"

namespace app
{

std::string DataLocator::locate(const std::string& path)
{
  namespace fs = std::filesystem;

  const auto name = fs::path{path}.filename();
  const auto binaryDir = executable_directory();

  // A directory given with the trailing separator names no installed copy.
  if (name.empty()) {
    return path;
  }

  for (const auto& candidate :
       {binaryDir.empty()
            ? fs::path{}
            : (fs::path{binaryDir} /
               project_decls::PROJECT_DATA_INSTALLED_RELATIVE_DIR / name)
                  .lexically_normal(),
        fs::path{path},
        fs::path{project_decls::PROJECT_DATA_INSTALLED_DIR} / name}) {
    std::error_code error;

    if (!candidate.empty() && fs::exists(candidate, error)) {
      return candidate.string();
    }
  }

  return path;
}

std::string DataLocator::executable_directory()
{
  // Linux names the running executable by the first link, FreeBSD (with the
  // procfs mounted) by the second one.
  for (const auto* link : {"/proc/self/exe", "/proc/curproc/file"}) {
    std::error_code error;

    const auto executable = std::filesystem::read_symlink(link, error);

    if (!error) {
      return executable.parent_path().string();
    }
  }

  return {};
}

}  // namespace app
