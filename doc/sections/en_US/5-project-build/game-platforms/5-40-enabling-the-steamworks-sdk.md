## Enabling the Steamworks SDK

In order to enable the [Steamworks SDK](https://partner.steamgames.com/doc/sdk) (the Steam platform integration: achievements, the overlay, the cloud saves, the workshop and so on) for the project set an `ON` value to the `ENABLE_STEAMWORKS` CMake variable and point the build at a locally extracted SDK.

Unlike every other library of this project the Steamworks SDK is **proprietary**: it is neither packaged by the distributions nor fetchable over the connection, so there is no system probe and no FetchContent fallback in its enabler module. Download the archive from the [Steamworks downloads page](https://partner.steamgames.com/downloads/list) with a Steamworks account (accepting the Steamworks SDK Access Agreement), unpack it and hand the `sdk` directory it contains to the build:

```
# Inside the source root directory

cmake -S . -B build -DENABLE_STEAMWORKS=ON -DTEMPLATE_APP_STEAMWORKS_SDK_DIR=/path/to/steamworks_sdk/sdk
```

The `STEAMWORKS_SDK_DIR` environment variable is picked up as the default value of the `TEMPLATE_APP_STEAMWORKS_SDK_DIR` one, which is handy for the CI runners:

```
export STEAMWORKS_SDK_DIR=/path/to/steamworks_sdk/sdk

cmake -S . -B build -DENABLE_STEAMWORKS=ON
```

The module fails the configuration with a descriptive message when the variable is empty or when the given directory holds neither the `public/steam/steam_api.h` header nor the redistributable of the current platform.

See the `cmake/enablers/game-platforms/template-project-steamworks-enabler.cmake` module for the target (`Steamworks::Steamworks`) to link to your targets of interest. The module picks the redistributable matching the platform and the architecture being built:

| Platform | Redistributable inside the SDK |
| --- | --- |
| GNU/Linux x86_64 | `redistributable_bin/linux64/libsteam_api.so` |
| GNU/Linux x86 | `redistributable_bin/linux32/libsteam_api.so` |
| GNU/Linux aarch64 | `redistributable_bin/linuxarm64/libsteam_api.so` |
| MS Windows x64 | `redistributable_bin/win64/steam_api64.dll` (+ the `steam_api64.lib` import library) |
| MS Windows x86 | `redistributable_bin/steam_api.dll` (+ the `steam_api.lib` import library) |
| macOS | `redistributable_bin/osx/libsteam_api.dylib` |

### Running the built binary

The Steam client library is loaded from beside the executable, so the module adds the picked redistributable to the installation next to the project binary and therefore to every generated package as well. A binary run straight from the build tree needs it copied over by hand once:

```
cmake -E copy /path/to/steamworks_sdk/sdk/redistributable_bin/linux64/libsteam_api.so build/src/
```

During the development, before the application is launched through Steam itself, put a `steam_appid.txt` file holding nothing but your App ID next to the executable — otherwise the initialization fails with `k_ESteamAPIInitResult_NoSteamClient`. Remove that file from the shipped build. The Steam client has to be running and logged in for the API to initialize at all.

### Talking to Steam (copy-paste examples)

After `ENABLE_STEAMWORKS=ON` and linking the Steamworks target (e.g. `target_link_libraries(${PROJECT_BINARY_NAME} Steamworks::Steamworks)`), include `<steam/steam_api.h>` and copy-paste the snippets below.

Starting and stopping the API — the two calls that wrap the whole session:

```cpp
#include <steam/steam_api.h>

#include <cstdio>

// Replace with the App ID of your own application. 480 is the Spacewar test
// application every Steamworks account may use.
constexpr uint32 APP_ID = 480;

bool steam_start()
{
  // Relaunches the executable through the Steam client when it was started
  // directly, so quit immediately once it returns true.
  if (SteamAPI_RestartAppIfNecessary(APP_ID)) {
    return false;
  }

  // SteamAPI_InitEx() reports why the initialization failed, unlike the
  // boolean returning SteamAPI_Init().
  SteamErrMsg error = {};
  if (SteamAPI_InitEx(&error) != k_ESteamAPIInitResult_OK) {
    std::printf("Steamworks init failed: %s\n", error);
    return false;
  }

  std::printf("Logged in as %s\n", SteamFriends()->GetPersonaName());
  return true;
}

void steam_stop()
{
  SteamAPI_Shutdown();
}
```

Steam delivers its answers as the callbacks, so the application loop has to pump them, and the objects that listen for them declare their handlers with the `STEAM_CALLBACK` macro:

```cpp
#include <steam/steam_api.h>

#include <cstdio>

class SteamAchievements
{
 public:
  // Unlocks an achievement by the API name given to it in the Steamworks
  // partner site and pushes the change to the Steam servers.
  void unlock(const char* achievementId)
  {
    if (SteamUserStats()->SetAchievement(achievementId)) {
      SteamUserStats()->StoreStats();
    }
  }

 private:
  // The macro declares the OnUserStatsReceived() handler and registers it for
  // the UserStatsReceived_t callback for as long as this object lives.
  STEAM_CALLBACK(SteamAchievements, OnUserStatsReceived, UserStatsReceived_t);
};

void SteamAchievements::OnUserStatsReceived(UserStatsReceived_t* callback)
{
  std::printf("Stats received, result %d\n", int(callback->m_eResult));
}

// Call once per frame from the application loop: without it no callback and no
// call result of the ones above is ever delivered.
void steam_pump_callbacks()
{
  SteamAPI_RunCallbacks();
}
```

The `SteamFriends()`, `SteamUserStats()`, `SteamUser()`, `SteamUtils()` and the rest of the interface accessors are only valid between a successful initialization and the `SteamAPI_Shutdown()` call, so keep them out of the constructors and the destructors of the globally created objects.
