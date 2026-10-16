#!/bin/bash -e
#
# Installs the packages required to build and develop the project on Debian by
# running the install-debian-<version>.sh script of the running release, e.g.
# the install-debian-13.sh one on the Debian 13.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/packages/common.sh"

exec_release_script "$@"
