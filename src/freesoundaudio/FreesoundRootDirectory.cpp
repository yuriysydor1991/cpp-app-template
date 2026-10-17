#include "src/freesoundaudio/FreesoundRootDirectory.h"

#include <filesystem>
#include <string>
#include <system_error>
#include <vector>

#include "freesound-audio-decls.h"

namespace freesoundaudio
{

const std::string& FreesoundRootDirectory::path()
{
  using namespace freesound_audio_decls;

  static const std::string root = []() {
    const auto binaryDir = executableDirectory();

    return firstExisting(
        {binaryDir.empty() ? binaryDir
                           : (std::filesystem::path{binaryDir} /
                              FREESOUND_AUDIO_INSTALLED_RELATIVE_DIR)
                                 .lexically_normal()
                                 .string(),
         FREESOUND_AUDIO_ROOT_DIR, FREESOUND_AUDIO_INSTALLED_DIR},
        FREESOUND_AUDIO_ROOT_DIR);
  }();

  return root;
}

std::string FreesoundRootDirectory::firstExisting(
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

std::string FreesoundRootDirectory::executableDirectory()
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

}  // namespace freesoundaudio
