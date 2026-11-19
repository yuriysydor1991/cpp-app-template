#!/bin/bash -e
#
# Fails when a tracked file holds the git conflict markers.

. "$(dirname "$0")/common.sh"

if git grep -nE "^(<<<<<<<|>>>>>>>)" -- .; then
  echo "FAIL: the files listed above contain git conflict markers (unmerged content)"
  exit 1
fi
echo "OK: no git conflict markers found in the tracked files"
