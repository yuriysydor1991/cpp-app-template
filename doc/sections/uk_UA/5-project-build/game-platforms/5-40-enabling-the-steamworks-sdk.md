## Вмикання інтеграції Steamworks SDK

Для того щоб увімкнути [Steamworks SDK](https://partner.steamgames.com/doc/sdk) (інтеграцію з платформою Steam: досягнення, оверлей, хмарні збереження, майстерня тощо) для проекту, необхідно встановити значення `ON` для CMake змінної `ENABLE_STEAMWORKS` та вказати збірці шлях до локально розпакованого SDK.

На відміну від усіх інших бібліотек цього проекту Steamworks SDK є **пропрієтарним**: його не пакують дистрибутиви й неможливо завантажити через з'єднання, тож у його модулі немає ані пошуку в системі, ані запасного варіанту через FetchContent. Завантаж архів зі [сторінки завантажень Steamworks](https://partner.steamgames.com/downloads/list) за наявності облікового запису Steamworks (прийнявши Steamworks SDK Access Agreement), розпакуй його та передай збірці директорію `sdk`, яку він містить:

```
# в середині кореневої директорії проекту

cmake -S . -B build -DENABLE_STEAMWORKS=ON -DTEMPLATE_APP_STEAMWORKS_SDK_DIR=/шлях/до/steamworks_sdk/sdk
```

Змінна оточення `STEAMWORKS_SDK_DIR` підхоплюється як типове значення для `TEMPLATE_APP_STEAMWORKS_SDK_DIR`, що є зручним для CI:

```
export STEAMWORKS_SDK_DIR=/шлях/до/steamworks_sdk/sdk

cmake -S . -B build -DENABLE_STEAMWORKS=ON
```

Модуль перериває конфігурування зі змістовним повідомленням, коли змінна порожня або коли вказана директорія не містить ані заголовка `public/steam/steam_api.h`, ані бібліотеки для поточної платформи.

Дивись модуль `cmake/enablers/game-platforms/template-project-steamworks-enabler.cmake` щодо цілі (`Steamworks::Steamworks`), яку слід прилінкувати до твоїх цільових об'єктів. Модуль обирає бібліотеку відповідно до платформи та архітектури, що збирається:

| Платформа | Бібліотека всередині SDK |
| --- | --- |
| GNU/Linux x86_64 | `redistributable_bin/linux64/libsteam_api.so` |
| GNU/Linux x86 | `redistributable_bin/linux32/libsteam_api.so` |
| GNU/Linux aarch64 | `redistributable_bin/linuxarm64/libsteam_api.so` |
| MS Windows x64 | `redistributable_bin/win64/steam_api64.dll` (+ імпортна бібліотека `steam_api64.lib`) |
| MS Windows x86 | `redistributable_bin/steam_api.dll` (+ імпортна бібліотека `steam_api.lib`) |
| macOS | `redistributable_bin/osx/libsteam_api.dylib` |

### Запуск зібраного виконуваного файлу

Клієнтська бібліотека Steam завантажується з директорії поруч із виконуваним файлом, тож модуль додає обрану бібліотеку до встановлення поруч із бінарником проекту, а отже й до кожного згенерованого пакунка. Для бінарника, що запускається просто з дерева збірки, її потрібно один раз скопіювати вручну:

```
cmake -E copy /шлях/до/steamworks_sdk/sdk/redistributable_bin/linux64/libsteam_api.so build/src/
```

Під час розробки, доки застосунок ще не запускається через сам Steam, поклади поруч із виконуваним файлом файл `steam_appid.txt`, що містить лише твій App ID — інакше ініціалізація завершиться помилкою `k_ESteamAPIInitResult_NoSteamClient`. Прибери цей файл із версії, що постачається. Клієнт Steam має бути запущеним, а користувач — увійти в обліковий запис, інакше API не ініціалізується взагалі.

### Спілкування зі Steam (приклади для копіювання)

Після `ENABLE_STEAMWORKS=ON` та прилінкування цілі Steamworks (наприклад `target_link_libraries(${PROJECT_BINARY_NAME} Steamworks::Steamworks)`) підключи `<steam/steam_api.h>` і скопіюй сніпети нижче.

Запуск та зупинка API — два виклики, які огортають увесь сеанс:

```cpp
#include <steam/steam_api.h>

#include <cstdio>

// Заміни на App ID власного застосунку. 480 — це тестовий застосунок
// Spacewar, яким може користуватися будь-який обліковий запис Steamworks.
constexpr uint32 APP_ID = 480;

bool steam_start()
{
  // Перезапускає виконуваний файл через клієнт Steam, якщо його було
  // запущено напряму, тож завершуй роботу одразу, щойно повернено true.
  if (SteamAPI_RestartAppIfNecessary(APP_ID)) {
    return false;
  }

  // SteamAPI_InitEx() повідомляє, чому ініціалізація не вдалася, на відміну
  // від SteamAPI_Init(), що повертає лише булеве значення.
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

Steam надає свої відповіді у вигляді зворотних викликів, тож цикл застосунку має їх прокачувати, а об'єкти, що їх очікують, оголошують свої обробники макросом `STEAM_CALLBACK`:

```cpp
#include <steam/steam_api.h>

#include <cstdio>

class SteamAchievements
{
 public:
  // Відкриває досягнення за API назвою, наданою йому на партнерському сайті
  // Steamworks, та надсилає зміну на сервери Steam.
  void unlock(const char* achievementId)
  {
    if (SteamUserStats()->SetAchievement(achievementId)) {
      SteamUserStats()->StoreStats();
    }
  }

 private:
  // Макрос оголошує обробник OnUserStatsReceived() та реєструє його для
  // зворотного виклику UserStatsReceived_t, доки живе цей об'єкт.
  STEAM_CALLBACK(SteamAchievements, OnUserStatsReceived, UserStatsReceived_t);
};

void SteamAchievements::OnUserStatsReceived(UserStatsReceived_t* callback)
{
  std::printf("Stats received, result %d\n", int(callback->m_eResult));
}

// Викликай раз на кадр із циклу застосунку: без цього жоден зі зворотних
// викликів та жоден результат виклику ніколи не буде доставлено.
void steam_pump_callbacks()
{
  SteamAPI_RunCallbacks();
}
```

Доступи до інтерфейсів `SteamFriends()`, `SteamUserStats()`, `SteamUser()`, `SteamUtils()` та решти є дійсними лише між успішною ініціалізацією та викликом `SteamAPI_Shutdown()`, тож тримай їх подалі від конструкторів і деструкторів глобально створених об'єктів.
