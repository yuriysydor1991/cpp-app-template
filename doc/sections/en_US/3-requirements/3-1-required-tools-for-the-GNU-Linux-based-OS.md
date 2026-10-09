## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appGettext` branch additionally needs the [GNU gettext](https://www.gnu.org/software/gettext/) tools which compile the translations, while the libintl library they are read with is a part of the GNU C library:

```
sudo apt install -y gettext
```

The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs it together with the rest of the required packages. On RPM-based distributions the equivalent package is `gettext`; on FreeBSD they are `devel/gettext-runtime` and `devel/gettext-tools` from `pkg`. The translations show up under an installed locale only, see the [Enabling the GNU gettext translations](/doc/sections/en_US/5-project-build/i18n/5-62-enabling-the-gettext-translations.md) section.
