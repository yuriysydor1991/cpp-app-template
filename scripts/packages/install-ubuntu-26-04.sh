#!/bin/bash -e
#
# Installs the packages required to build and develop the project on the
# Ubuntu 26.04. The install-ubuntu.sh script picks it on that release.
#
# Every package of the list exists in the Ubuntu 26.04 archive. A dependency the
# release packages no usable version of is built out of a pinned release tag
# of its sources with the cmake_install_from_source helper of the common.sh.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/packages/common.sh"

PACKAGES=(
    build-essential
    cmake
    g++
    git
    googletest
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
)

apt_install "${PACKAGES[@]}"

# The libllama-dev package of the release is too old for the Gemma 4 models,
# while a llama.cpp built out of its sources would shadow the libggml0 one the
# other packages of the release (the whisper.cpp one, for example) link
# against, so the project configure fetches a llama.cpp of its own instead.

log "The required packages are installed"
