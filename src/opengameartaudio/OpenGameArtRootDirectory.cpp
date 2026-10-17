#include "src/opengameartaudio/OpenGameArtRootDirectory.h"

#include <filesystem>
#include <string>
#include <system_error>
#include <vector>

#include "opengameart-audio-decls.h"

namespace opengameartaudio
{

const std::string& OpenGameArtRootDirectory::path()
{
  using namespace opengameart_audio_decls;

  static const std::string root = []() {
    const auto binaryDir = executableDirectory();

    return firstExisting(
        {binaryDir.empty() ? binaryDir
                           : (std::filesystem::path{binaryDir} /
                              OPENGAMEART_AUDIO_INSTALLED_RELATIVE_DIR)
                                 .lexically_normal()
                                 .string(),
         OPENGAMEART_AUDIO_ROOT_DIR, OPENGAMEART_AUDIO_INSTALLED_DIR},
        OPENGAMEART_AUDIO_ROOT_DIR);
  }();

  return root;
}

std::string OpenGameArtRootDirectory::firstExisting(
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

std::string OpenGameArtRootDirectory::executableDirectory()
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

}  // namespace opengameartaudio
