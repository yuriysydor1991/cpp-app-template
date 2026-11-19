#!/bin/bash -e
#
# Fails when a doc/sections file is linked in no README of its language.

. "$(dirname "$0")/common.sh"

status=0
for langdir in doc/sections/*/; do
  [ -d "$langdir" ] || continue
  lang="$(basename "$langdir")"
  if [ "$lang" = "en_US" ]; then
    readme="README.md"
  else
    readme="doc/README.${lang}.md"
  fi
  if [ ! -f "$readme" ]; then
    echo "FAIL: no README ($readme) found for the doc/sections/$lang language"
    status=1
    continue
  fi
  for f in "$langdir"*; do
    [ -f "$f" ] || continue
    if ! grep -qF "$f" "$readme"; then
      echo "FAIL: $f is not linked in $readme"
      status=1
    fi
  done
done
[ "$status" -eq 0 ] || exit 1
echo "OK: every doc/sections file is linked in its README"
