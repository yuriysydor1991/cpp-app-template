## Required Wt packages

The branch builds its web site on the [Wt C++ framework](https://www.webtoolkit.eu/wt) 4. The project configure probes the system for an installed Wt first and, when there is none, fetches the Wt `4.11.4` release sources from [https://github.com/emweb/wt](https://github.com/emweb/wt) and builds them together with the project: the stand-alone httpd connector only, without the Dbo database backends, the examples and the tests. No Ubuntu 24.04/26.04 or Debian 13 release packages the Wt, so the fetched build is the usual case there, and it needs the packages the [Packages required to build the Wt](/doc/sections/en_US/3-requirements/3-13-3-packages-required-to-build-the-Wt.md) subsection lists.

The Wt related configure options are:

- `ENABLE_WT4` (`ON` by default) makes the Wt available to the project. The `src/wt4` component and the `Application` class are built on it, so it stays `ON` unless the project drops them.
- `WT4_TRY_SYSTEM_PROBE` (`ON` by default) probes the system installed Wt before fetching it. Set it to `OFF` to always build the fetched sources.
- `TEMPLATE_APP_WT4_GIT` and `TEMPLATE_APP_WT4_GIT_TAG` (`https://github.com/emweb/wt.git` and `4.11.4` by default) name the repository and the tag to fetch.
- `WT4_DOCKER_PORT` (`8000` by default) is the port the docker single run image listens to and publishes on the loopback interface.

For example:

```
# inside the project root directory

cmake -S . -B build -DWT4_TRY_SYSTEM_PROBE=OFF
```

Other possible methods described in next subsections.

1. [Cloning and building from sources](/doc/sections/en_US/3-requirements/3-13-1-cloning-and-building-from-sources.md)
1. [Installing via the command line](/doc/sections/en_US/3-requirements/3-13-2-installing-via-the-command-line.md)
1. [Packages required to build the Wt](/doc/sections/en_US/3-requirements/3-13-3-packages-required-to-build-the-Wt.md)
