## Швидкі скрипти побудови

Директорія [scripts/build](/scripts/build) містить скрипти оболонки, які виконують кроки конфігурації, побудови і встановлення проекту системою CMake, отож цілий цикл `Release` або `Debug` виконується однією командою замість окремих викликів CMake, описаних у секції [Побудова проекту-шаблону через командний рядок](/doc/sections/uk_UA/5-project-build/5-2-command-line-build.md).

Кожен скрипт тримає своє дерево побудови всередині директорії `build` проекту: `Release` у `build/release`, а `Debug` у `build/debug`.

### Скрипти повного циклу

Кожен зі скриптів нижче виконує кроки конфігурації, побудови і встановлення один за одним. Ті зі скриптів `Debug`, які будують увесь проект, виконують ще й крок тестування, поміж кроками побудови і встановлення:

| Скрипт | Виконує |
| --- | --- |
| [release.sh](/scripts/build/release.sh) | побудову `Release` |
| [debug.sh](/scripts/build/debug.sh) | побудову `Debug` з увімкненими тестами, документацією, `cppcheck`, `valgrind` і `callgrind` |
| [debug-cppcheck.sh](/scripts/build/debug-cppcheck.sh) | побудову `Debug` цілі `cppcheck` |
| [debug-valgrind.sh](/scripts/build/debug-valgrind.sh) | побудову `Debug` цілі `valgrind` |
| [debug-callgrind.sh](/scripts/build/debug-callgrind.sh) | побудову `Debug` цілі `callgrind` |
| [debug-clang-tidy.sh](/scripts/build/debug-clang-tidy.sh) | побудову `Debug` з параметром `ENABLE_CLANG_TIDY` |
| [debug-sanitizers.sh](/scripts/build/debug-sanitizers.sh) | побудову `Debug` з параметром `ENABLE_SANITIZERS` |
| [debug-sanitizers-threads.sh](/scripts/build/debug-sanitizers-threads.sh) | побудову `Debug` з параметром `ENABLE_SANITIZERS_THREADS` |
| [debug-compiler-analyzer.sh](/scripts/build/debug-compiler-analyzer.sh) | побудову `Debug` з параметром `ENABLE_COMPILER_CODE_ANALYZER` |

Скрипти [debug-cppcheck.sh](/scripts/build/debug-cppcheck.sh), [debug-valgrind.sh](/scripts/build/debug-valgrind.sh) і [debug-callgrind.sh](/scripts/build/debug-callgrind.sh) будують окрему ціль CMake, до складу якої виконувані файли тестів не входять, отож ці три кроку тестування не виконують зовсім.

Повна побудова `Release` виконується однією командою:

```
# в середині кореневої директорії проекту

scripts/build/release.sh
```

### Скрипти пакувальників

Кожен зі скриптів нижче виконує крок конфігурації `Release` з увімкненою однією опцією пакувальника, а потім будує ціль, яка утворює пакунок. Окремого кроку побудови немає: кожна з тих цілей будує те, що їй потрібно, сама, тому нічого зайвого до директорії `build/release` наперед не будується. Вони приймають параметри скриптів повного циклу вище, а утворений пакунок потрапляє туди ж:

| Скрипт | Утворює | Параметр `--install` встановлює його командою |
| --- | --- | --- |
| [build-appimage.sh](/scripts/build/build-appimage.sh) | пакунок AppImage - опція `ENABLE_APPIMAGE` і ціль `appimage` | `install` у каталог `${HOME}/.local/bin` |
| [build-deb.sh](/scripts/build/build-deb.sh) | пакунок DEB - опція `ENABLE_DEB` і ціль `package` | `sudo apt-get install` |
| [build-flatpak.sh](/scripts/build/build-flatpak.sh) | звʼязку flatpak - опція `ENABLE_FLATPAK` і ціль `flatpak` | `flatpak install --user` |
| [build-freebsd-pkg.sh](/scripts/build/build-freebsd-pkg.sh) | пакунок FreeBSD pkg - опція `ENABLE_FREEBSD_PKG` і ціль `package` | `sudo pkg add` |
| [build-rpm.sh](/scripts/build/build-rpm.sh) | пакунок RPM - опція `ENABLE_RPM` і ціль `package` | `sudo dnf install` |
| [build-snap.sh](/scripts/build/build-snap.sh) | пакунок snap - опція `ENABLE_SNAP` і ціль `snap` | `sudo snap install --dangerous` |
| [build-wix.sh](/scripts/build/build-wix.sh) | інсталятор WIX MSI - опція `ENABLE_WIX` і ціль `package` | `msiexec //i` |

Власний аргумент `-D<змінна>=<значення>` передається до кроку конфігурації після опції пакувальника, тому перекриває і її, і будь-яке інше налаштування проекту:

```
# у кореневій директорії проекту

scripts/build/build-deb.sh -DPROJECT_MAINTAINER_EMAIL=me@example.org
```

Самі опції пакувальників, потрібні їм інструменти і їх власні налаштування описано у підсекціях пакувальників секції [Побудова проекту](/doc/sections/uk_UA/5-project-build/5-project-build.md).

### Скрипти окремих кроків

Кожен скрипт повного циклу вище є ланцюжком зі скриптів окремих кроків нижче, які можна запускати самостійно, коли потрібен лише один крок:

| Скрипт | Виконує |
| --- | --- |
| [release-configure.sh](/scripts/build/release-configure.sh), [debug-configure.sh](/scripts/build/debug-configure.sh) | крок конфігурації `cmake -B <директорія побудови> -S .` |
| [release-build.sh](/scripts/build/release-build.sh), [debug-build.sh](/scripts/build/debug-build.sh) | крок побудови `cmake --build <директорія побудови>` |
| [debug-test.sh](/scripts/build/debug-test.sh) | крок тестування `ctest` всередині директорії побудови `Debug` |
| [release-install.sh](/scripts/build/release-install.sh), [debug-install.sh](/scripts/build/debug-install.sh) | крок встановлення `sudo cmake --install <директорія побудови>` |

### Параметри, які приймають скрипти

Скрипти приймають наступні власні параметри, які ніколи не передаються до CMake:

| Параметр | Дія |
| --- | --- |
| `--no-reconfigure` | Зберігає наявну директорію побудови і повністю пропускає крок конфігурації. Без цього параметра крок конфігурації **стирає** директорію побудови перед новою конфігурацією проекту. |
| `--test` | Виконує крок тестування, який запускає команду `ctest` всередині директорії побудови `Debug`. Без цього параметра крок тестування пропускається. Параметр належить лише скриптам `Debug`, оскільки тести вмикає тільки їхній крок конфігурації. |
| `--install` | Виконує крок встановлення. Без цього параметра крок встановлення пропускається, отож для звичайної побудови пароль `sudo` ніколи не запитується. Скрипти пакувальників натомість встановлюють щойно утворений ними пакунок засобом того пакувальника. |

Будь-який аргумент виду `-D<змінна>=<значення>` передається до кроку конфігурації, що робить доступним для скриптів кожен параметр CMake з цієї документації:

```
# в середині кореневої директорії проекту

# побудова Release з увімкненою генерацією DEB-пакунка
scripts/build/release.sh -DENABLE_DEB=ON

# та ж побудова з повторним використанням вже сконфігурованої
# директорії побудови і наступним встановленням у префікс /usr
scripts/build/release.sh --no-reconfigure --install

# побудова Debug з виконанням усього набору тестів одразу після неї
scripts/build/debug.sh --test
```

Решта аргументів передається до кроків побудови, тестування і встановлення, отож параметр, який належить лише одному кроку, слід передавати відповідному скрипту окремого кроку, а не скрипту повного циклу:

```
# в середині кореневої директорії проекту

# побудова окремої цілі всередині вже сконфігурованої директорії побудови Debug
scripts/build/debug-build.sh --target cppcheck

# запуск частини набору тестів всередині вже побудованої директорії побудови Debug
scripts/build/debug-test.sh --test -R "CTEST_log\."
```

Виклик конфігурації `cmake -B` не приймає ані параметра `--target`, ані `--verbose`, отож передача такого аргументу скрипту повного циклу завершить крок конфігурації помилкою.
