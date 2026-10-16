#!/bin/bash -e
#
# Installs the packages required to build and develop the project on Ubuntu by
# running the install-ubuntu-<version>.sh script of the running release, e.g.
# the install-ubuntu-26-04.sh one on the Ubuntu 26.04.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/packages/common.sh"

exec_release_script "$@"
