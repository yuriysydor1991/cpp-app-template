#include "src/fontawesome/FontAwesomeSvgsDirectory.h"

#include <filesystem>
#include <string>
#include <system_error>
#include <vector>

#include "fontawesome-decls.h"

namespace fontawesome
{

const std::string& FontAwesomeSvgsDirectory::path()
{
  using namespace fontawesome_decls;

  static const std::string root = []() {
    const auto binaryDir = executableDirectory();

    return firstExisting(
        {binaryDir.empty() ? binaryDir
                           : (std::filesystem::path{binaryDir} /
                              FONTAWESOME_SVGS_INSTALLED_RELATIVE_DIR)
                                 .lexically_normal()
                                 .string(),
         FONTAWESOME_SVGS_DIR, FONTAWESOME_SVGS_INSTALLED_DIR},
        FONTAWESOME_SVGS_DIR);
  }();

  return root;
}

std::string FontAwesomeSvgsDirectory::firstExisting(
    const std::vector<std::string>& candidates, const std::string& fallback)
{
  for (const auto& candidate : candidates) {
    std::error_code error;

    if (!candidate.empty() && std::filesystem::is_directory(candidate, error)) {
      return candidate;
    }
  }

  return fallback;
}

std::string FontAwesomeSvgsDirectory::executableDirectory()
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

}  // namespace fontawesome
