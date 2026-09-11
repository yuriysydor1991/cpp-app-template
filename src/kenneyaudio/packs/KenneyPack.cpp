#include "src/kenneyaudio/packs/KenneyPack.h"

#include <memory>
#include <string>
#include <utility>

#include "src/kenneyaudio/packs/IKenneyPack.h"

namespace kenneyaudio
{

KenneyPack::KenneyPack(std::string gname) : mname{std::move(gname)} {}

std::string KenneyPack::name() const { return mname; }

IKenneyPackPtr KenneyPack::create(std::string gname)
{
  return std::make_shared<KenneyPack>(std::move(gname));
}

}  // namespace kenneyaudio
