#!/bin/sh
# Downloads and unpacks the OpenGameArt sound packs the misc/opengameart-packs.txt
# manifest names into a directory the build then reuses through the
# TEMPLATE_APP_OPENGAMEART_AUDIO_DIR CMake variable:
#
#   misc/scripts/fetch-opengameart-audio.sh ~/opengameart-audio
#   cmake -S . -B build -DTEMPLATE_APP_OPENGAMEART_AUDIO_DIR=~/opengameart-audio
#
# The build downloads the very same packs on it's own, so this script is for
# the hosts where the configure step has no network of it's own, for a shared
# packs directory and for keeping the downloads out of the build tree.
set -eu

TARGET_DIR="${1:-./resources/opengameart-audio}"
MANIFEST="${OPENGAMEART_AUDIO_MANIFEST:-misc/opengameart-packs.txt}"

if [ ! -f "$MANIFEST" ]; then
  echo "No $MANIFEST packs manifest to read the packs of" >&2
  exit 1
fi

if command -v curl >/dev/null 2>&1; then
  download() { curl -fsSL -o "$2" "$1"; }
elif command -v wget >/dev/null 2>&1; then
  download() { wget -q -O "$2" "$1"; }
else
  echo "Neither curl nor wget is available to download the packs with" >&2
  exit 1
fi

if ! command -v unzip >/dev/null 2>&1; then
  echo "No unzip available to unpack the downloaded archives with" >&2
  exit 1
fi

mkdir -p "$TARGET_DIR"

packsSeen=0

# The manifest records the license next to every pack, so the provenance of the
# downloaded material stays written down rather than assumed.
while IFS='|' read -r pack packUrl packLicense; do
  case "$pack" in ''|\#*) continue ;; esac

  pack=$(echo "$pack" | tr -d ' ')
  packUrl=$(echo "$packUrl" | tr -d ' ')
  packLicense=$(echo "$packLicense" | sed 's/^ *//; s/ *$//')

  if [ -z "$packUrl" ] || [ -z "$packLicense" ]; then
    echo "The '$pack' line of $MANIFEST follows no <pack>|<archive URL>|<license> form" >&2
    exit 1
  fi

  packsSeen=$((packsSeen + 1))
  packDir="$TARGET_DIR/$pack"

  if [ -d "$packDir" ]; then
    echo "Already available: $pack ($packLicense)"
    continue
  fi

  packArchive="$TARGET_DIR/$pack.zip"

  echo "Downloading $pack ($packLicense): $packUrl"

  if ! download "$packUrl" "$packArchive"; then
    rm -f "$packArchive"
    echo "Fail to download the $pack pack from $packUrl." >&2
    echo "Correct it's line of $MANIFEST or download the pack by hand from https://opengameart.org" >&2
    exit 1
  fi

  mkdir -p "$packDir"

  if ! unzip -q "$packArchive" -d "$packDir"; then
    rm -rf "$packDir" "$packArchive"
    echo "Fail to unpack the downloaded $pack pack archive" >&2
    exit 1
  fi

  rm -f "$packArchive"
done < "$MANIFEST"

if [ "$packsSeen" -eq 0 ]; then
  echo "The $MANIFEST manifest names no pack at all" >&2
  exit 1
fi

echo "The OpenGameArt sound packs are available under $TARGET_DIR"
