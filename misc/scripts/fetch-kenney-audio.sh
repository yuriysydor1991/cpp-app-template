#!/bin/sh
# Downloads and unpacks the Kenney CC0 sound packs into a directory the build
# then reuses through the TEMPLATE_APP_KENNEY_AUDIO_DIR CMake variable:
#
#   misc/scripts/fetch-kenney-audio.sh ~/kenney-audio
#   cmake -S . -B build -DTEMPLATE_APP_KENNEY_AUDIO_DIR=~/kenney-audio
#
# The build downloads the very same packs on it's own, so this script is for
# the hosts where the configure step has no network of it's own, for a shared
# packs directory and for keeping the downloads out of the build tree.
set -eu

TARGET_DIR="${1:-./resources/kenney-audio}"
PACKS="${KENNEY_AUDIO_PACKS:-interface-sounds impact-sounds digital-audio ui-audio}"
URL_TEMPLATE="${KENNEY_AUDIO_URL_TEMPLATE:-https://kenney.nl/media/pages/assets/<pack>/<pack>.zip}"

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

for pack in $PACKS; do
  packDir="$TARGET_DIR/$pack"

  if [ -d "$packDir" ]; then
    echo "Already available: $pack"
    continue
  fi

  packUrl=$(echo "$URL_TEMPLATE" | sed "s|<pack>|$pack|g")
  packArchive="$TARGET_DIR/$pack.zip"

  echo "Downloading $pack: $packUrl"

  if ! download "$packUrl" "$packArchive"; then
    rm -f "$packArchive"
    echo "Fail to download the $pack pack from $packUrl." >&2
    echo "Correct the KENNEY_AUDIO_URL_TEMPLATE environment variable or download the pack by hand from https://kenney.nl/assets" >&2
    exit 1
  fi

  mkdir -p "$packDir"

  if ! unzip -q "$packArchive" -d "$packDir"; then
    rm -rf "$packDir" "$packArchive"
    echo "Fail to unpack the downloaded $pack pack archive" >&2
    exit 1
  fi

  rm -f "$packArchive"
done

echo "The Kenney sound packs are available under $TARGET_DIR"
