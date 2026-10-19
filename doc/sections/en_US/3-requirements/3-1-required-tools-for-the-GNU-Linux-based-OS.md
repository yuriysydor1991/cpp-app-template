## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appLlamaCPP` branch additionally needs the git and the internet access, since the configure fetches and builds the [llama.cpp](https://github.com/ggml-org/llama.cpp) library unless the system packages a new enough one, and downloads the language model of several gigabytes. The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script builds and installs the `v0.7.0` llama.cpp out of it's sources on the Ubuntu 24.04 and the Debian 13, which package none, while on the Ubuntu 26.04 the configure fetches one of it's own, since the `libllama-dev` package of the release is too old for the Gemma 4 models. The Debian forky packages a new enough one as the `libllama-dev` and the FreeBSD as the `misc/llama-cpp` one, while the `llama-cpp-devel` one of the Fedora is too old, so the configure fetches the llama.cpp there. See the [Enabling the llama.cpp language models](/doc/sections/en_US/5-project-build/ai/5-73-enabling-the-llama-cpp-language-models.md) section for the models and the RAM they need.

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
