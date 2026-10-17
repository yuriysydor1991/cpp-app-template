## Required packages for the Boost.Log

The logger of this branch is the [Boost.Log](https://www.boost.org/doc/libs/release/libs/log/) library. The project links its shared `log`, `log_setup`, `thread` and `filesystem` libraries and fetches no sources of them, so install their development files (GNU/Linux based OS):

```
sudo apt install -y libboost-log-dev libboost-thread-dev libboost-filesystem-dev
```

The `libboost-all-dev` package the install scripts take carries them as well, the Red Hat family names them `boost-devel` and the FreeBSD `boost-libs`. The executable needs the Boost.Log runtime libraries alone, which the DEB package depends on (the `dpkg-shlibdeps` tool detects them) and the snap package stages.

See the [Boost.Log logger](/doc/sections/en_US/5-project-build/5-66-the-Boost-Log-logger.md) section for the way the project logs through it.
