#!/bin/sh
# Downloads the Freesound sounds the misc/freesound-sounds.txt manifest names
# into a directory the build then reuses through the
# TEMPLATE_APP_FREESOUND_AUDIO_DIR CMake variable:
#
#   misc/scripts/fetch-freesound-audio.sh ~/freesound-audio
#   cmake -S . -B build -DTEMPLATE_APP_FREESOUND_AUDIO_DIR=~/freesound-audio
#
# The build downloads the very same sounds on it's own, so this script is for
# the hosts where the configure step has no network of it's own, for a shared
# sounds directory and for keeping the downloads out of the build tree.
#
# It also writes a LICENSES.md next to the sounds, so the directory carries the
# provenance of every file it holds even once it leaves this build tree.
set -eu

TARGET_DIR="${1:-./resources/freesound-audio}"
MANIFEST="${FREESOUND_AUDIO_MANIFEST:-misc/freesound-sounds.txt}"

if [ ! -f "$MANIFEST" ]; then
  echo "No $MANIFEST sounds manifest to read the sounds of" >&2
  exit 1
fi

if command -v curl >/dev/null 2>&1; then
  download() { curl -fsSL -o "$2" "$1"; }
elif command -v wget >/dev/null 2>&1; then
  download() { wget -q -O "$2" "$1"; }
else
  echo "Neither curl nor wget is available to download the sounds with" >&2
  exit 1
fi

mkdir -p "$TARGET_DIR"

LICENSES="$TARGET_DIR/LICENSES.md"
printf '# The sounds of this directory\n\n| Sound | Source | License |\n| --- | --- | --- |\n' > "$LICENSES"

soundsSeen=0

while IFS='|' read -r soundAlias soundUrl soundLicense; do
  case "$soundAlias" in ''|\#*) continue ;; esac

  soundAlias=$(echo "$soundAlias" | tr -d ' ')
  soundUrl=$(echo "$soundUrl" | tr -d ' ')
  soundLicense=$(echo "$soundLicense" | sed 's/^ *//; s/ *$//')

  if [ -z "$soundUrl" ] || [ -z "$soundLicense" ]; then
    echo "The '$soundAlias' line of $MANIFEST follows no <category>/<file>|<download URL>|<license> form" >&2
    exit 1
  fi

  soundsSeen=$((soundsSeen + 1))
  soundFile="$TARGET_DIR/$soundAlias"

  printf '| `%s` | %s | %s |\n' "$soundAlias" "$soundUrl" "$soundLicense" >> "$LICENSES"

  if [ -f "$soundFile" ]; then
    echo "Already available: $soundAlias ($soundLicense)"
    continue
  fi

  mkdir -p "$(dirname "$soundFile")"

  echo "Downloading $soundAlias ($soundLicense): $soundUrl"

  if ! download "$soundUrl" "$soundFile"; then
    rm -f "$soundFile"
    echo "Fail to download the $soundAlias sound from $soundUrl." >&2
    echo "Correct it's line of $MANIFEST or download the sound by hand from https://freesound.org" >&2
    exit 1
  fi
done < "$MANIFEST"

if [ "$soundsSeen" -eq 0 ]; then
  echo "The $MANIFEST manifest names no sound at all" >&2
  exit 1
fi

echo "The Freesound sounds are available under $TARGET_DIR (see $LICENSES)"
