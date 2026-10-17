#include "src/opengameartaudio/packs/OpenGameArtPack.h"

#include <memory>
#include <string>
#include <utility>

#include "src/opengameartaudio/packs/IOpenGameArtPack.h"

namespace opengameartaudio
{

OpenGameArtPack::OpenGameArtPack(std::string gname, std::string glicense)
    : mname{std::move(gname)}, mlicense{std::move(glicense)}
{
}

std::string OpenGameArtPack::name() const { return mname; }

std::string OpenGameArtPack::license() const { return mlicense; }

IOpenGameArtPackPtr OpenGameArtPack::create(std::string gname,
                                            std::string glicense)
{
  return std::make_shared<OpenGameArtPack>(std::move(gname),
                                           std::move(glicense));
}

}  // namespace opengameartaudio
