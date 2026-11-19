#!/bin/bash -e
#
# Fails when a link of the tracked markdown files points to no file.

. "$(dirname "$0")/common.sh"

MDLIST=$(mktemp)
LINKLIST=$(mktemp)
trap 'rm -f "$MDLIST" "$LINKLIST"' EXIT

# The repository own documentation only: a build tree keeps the
# fetched third-party sources with the markdown files of their own.
git ls-files -z '*.md' | tr '\0' '\n' | sort > "$MDLIST"

while IFS= read -r mdfile; do
  grep -oE '[[][^]]*[]][(][^)]+[)]' "$mdfile" 2>/dev/null \
    | sed 's/.*][(]\(.*\)[)]$/\1/' > "$LINKLIST"

  while IFS= read -r link; do
    [ -z "$link" ] && continue
    target="${link%%#*}"
    [ -z "$target" ] && continue
    case "$target" in http://*|https://*|mailto:*|ftp://*) continue ;; esac
    if [ "${target#/}" != "$target" ]; then
      resolved="${target#/}"
    else
      resolved="$(dirname "$mdfile")/${target}"
    fi
    if [ ! -e "$resolved" ]; then
      echo "FAIL: broken link in $mdfile"
      echo "  link:     $link"
      echo "  resolved: $resolved"
      exit 1
    fi
  done < "$LINKLIST"
done < "$MDLIST"

echo "OK: all *.md files have valid links"
