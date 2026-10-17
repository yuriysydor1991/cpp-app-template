#!/bin/sh
# Downloads and unpacks the Kenney CC0 sound packs the misc/kenney-packs.txt
# manifest names into a directory the build then reuses through the
# TEMPLATE_APP_KENNEY_AUDIO_DIR CMake variable:
#
#   misc/scripts/fetch-kenney-audio.sh ~/kenney-audio
#   cmake -S . -B build -DTEMPLATE_APP_KENNEY_AUDIO_DIR=~/kenney-audio
#
# The build downloads the very same packs on it's own, so this script is for
# the hosts where the configure step has no network of it's own, for a shared
# packs directory and for keeping the downloads out of the build tree.
set -eu

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <packs directory outside of the source tree>" >&2
  exit 1
fi

TARGET_DIR="$1"
MANIFEST="${KENNEY_AUDIO_MANIFEST:-$(dirname "$0")/../kenney-packs.txt}"

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

if ! command -v unzip >/dev/null 2>&1; then
  echo "No unzip available to unpack the downloaded archives with" >&2
  exit 1
fi

mkdir -p "$TARGET_DIR"

packsSeen=0

while IFS='|' read -r pack packUrl packHash; do
  case "$pack" in ''|\#*) continue ;; esac

  pack=$(echo "$pack" | tr -d ' ')
  packUrl=$(echo "$packUrl" | tr -d ' ')
  packHash=$(echo "$packHash" | tr -d ' ' | tr 'A-F' 'a-f')

  if [ -z "$packUrl" ] || [ ${#packHash} -ne 64 ]; then
    echo "The '$pack' line of $MANIFEST follows no <pack>|<archive URL>|<archive SHA-256> form" >&2
    exit 1
  fi

  packsSeen=$((packsSeen + 1))
  packDir="$TARGET_DIR/$pack"

  if [ -d "$packDir" ]; then
    echo "Already available: $pack"
    continue
  fi

  packArchive="$packDir.zip"

  echo "Downloading $pack: $packUrl"

  if ! download "$packUrl" "$packArchive"; then
    rm -f "$packArchive"
    echo "Fail to download the $pack pack from $packUrl." >&2
    echo "Correct it's line of $MANIFEST or download the pack by hand from https://kenney.nl/assets/$pack" >&2
    exit 1
  fi

  actualHash=$(checksum "$packArchive")

  if [ "$actualHash" != "$packHash" ]; then
    rm -f "$packArchive"
    echo "The $pack pack archive carries the $actualHash SHA-256 checksum instead of the $packHash one $MANIFEST pins" >&2
    exit 1
  fi

  # The pack directory appears only once the whole archive is out, so an
  # interrupted run leaves no half unpacked pack behind. The archives are
  # Windows made ones and carry the DOS read-only attribute on a directory of
  # their own (the Audio one of the digital-audio pack), which the extraction
  # turns into a directory no file may be created inside any more: the packs
  # are a build input and not a read-only tree, so the write permission goes
  # back on.
  rm -rf "${packDir:?}.unpacked"

  if ! unzip -q "$packArchive" -d "$packDir.unpacked"; then
    rm -rf "${packDir:?}.unpacked" "$packArchive"
    echo "Fail to unpack the downloaded $pack pack archive" >&2
    exit 1
  fi

  chmod -R u+w "$packDir.unpacked"
  mv "$packDir.unpacked" "$packDir"
  rm -f "$packArchive"
done < "$MANIFEST"

if [ "$packsSeen" -eq 0 ]; then
  echo "The $MANIFEST manifest names no pack at all" >&2
  exit 1
fi

echo "The Kenney sound packs are available under $TARGET_DIR"
