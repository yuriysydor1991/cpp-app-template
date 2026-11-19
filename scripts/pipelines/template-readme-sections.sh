#!/bin/bash -e
#
# Fails when the README links the doc sections of the foreign language.
#
# Usage: template-readme-sections.sh <README> <foreign language>

. "$(dirname "$0")/common.sh"

if grep -nE "doc/sections/$2/" "$1"; then
  echo "FAIL: $1 links $2 sections; it must use its own language sections only"
  exit 1
fi
echo "OK: $1 references no $2 sections"
