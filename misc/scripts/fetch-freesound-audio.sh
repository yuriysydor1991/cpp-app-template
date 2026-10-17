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

if command -v sha256sum >/dev/null 2>&1; then
  checksum() { sha256sum "$1" | cut -d ' ' -f 1; }
elif command -v shasum >/dev/null 2>&1; then
  checksum() { shasum -a 256 "$1" | cut -d ' ' -f 1; }
elif command -v sha256 >/dev/null 2>&1; then
  checksum() { sha256 -q "$1"; }
else
  echo "No sha256sum, shasum or sha256 available to check the downloads with" >&2
  exit 1
fi

mkdir -p "$TARGET_DIR"

LICENSES="$TARGET_DIR/LICENSES.md"
printf '# The sounds of this directory\n\n| Sound | Source | License |\n| --- | --- | --- |\n' > "$LICENSES"

soundsSeen=0

while IFS='|' read -r soundAlias soundUrl soundLicense soundHash; do
  case "$soundAlias" in ''|\#*) continue ;; esac

  soundAlias=$(echo "$soundAlias" | tr -d ' ')
  soundUrl=$(echo "$soundUrl" | tr -d ' ')
  soundLicense=$(echo "$soundLicense" | sed 's/^ *//; s/ *$//')
  soundHash=$(echo "$soundHash" | tr -d ' ' | tr 'A-F' 'a-f')

  if [ -z "$soundUrl" ] || [ -z "$soundLicense" ] || [ ${#soundHash} -ne 64 ]; then
    echo "The '$soundAlias' line of $MANIFEST follows no <category>/<file>|<download URL>|<license>|<file SHA-256> form" >&2
    exit 1
  fi

  soundsSeen=$((soundsSeen + 1))
  soundFile="$TARGET_DIR/$soundAlias"

  # shellcheck disable=SC2016 # the backticks are the markdown code marks
  printf '| `%s` | %s | %s |\n' "$soundAlias" "$soundUrl" "$soundLicense" >> "$LICENSES"

  if [ -f "$soundFile" ]; then
    echo "Already available: $soundAlias ($soundLicense)"
    continue
  fi

  mkdir -p "$(dirname "$soundFile")"

  echo "Downloading $soundAlias ($soundLicense): $soundUrl"

  # The file appears only once it is complete and checked, so an interrupted
  # or altered download leaves nothing behind to be taken for the sound.
  if ! download "$soundUrl" "$soundFile.part"; then
    rm -f "$soundFile.part"
    echo "Fail to download the $soundAlias sound from $soundUrl." >&2
    echo "Correct it's line of $MANIFEST or download the sound by hand from https://freesound.org" >&2
    exit 1
  fi

  actualHash=$(checksum "$soundFile.part")

  if [ "$actualHash" != "$soundHash" ]; then
    rm -f "$soundFile.part"
    echo "The $soundAlias sound carries the $actualHash SHA-256 checksum instead of the $soundHash one $MANIFEST pins" >&2
    exit 1
  fi

  mv "$soundFile.part" "$soundFile"
done < "$MANIFEST"

if [ "$soundsSeen" -eq 0 ]; then
  echo "The $MANIFEST manifest names no sound at all" >&2
  exit 1
fi

echo "The Freesound sounds are available under $TARGET_DIR (see $LICENSES)"
