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
PAGE_TEMPLATE="${KENNEY_AUDIO_PAGE_TEMPLATE:-https://kenney.nl/assets/<pack>}"

if command -v curl >/dev/null 2>&1; then
  download() { curl -fsSL -o "$2" "$1"; }
elif command -v wget >/dev/null 2>&1; then
  download() { wget -q -O "$2" "$1"; }
else
  echo "Neither curl nor wget is available to download the packs with" >&2
  exit 1
fi

# The archive address carries a content hash the site regenerates whenever the
# pack is updated, so it is read out of the pack's own page instead of being
# written down here.
pack_url()
{
  packPage=$(echo "$PAGE_TEMPLATE" | sed "s|<pack>|$1|g")
  pageFile="$TARGET_DIR/$1.html"

  if ! download "$packPage" "$pageFile" ; then
    rm -f "$pageFile"
    echo "Fail to read the $1 pack page at $packPage." >&2
    exit 1
  fi

  grep -oE "https://[^\"'[:space:]]*/assets/$1/[^\"'[:space:]]*\\.zip" "$pageFile" | head -n1

  rm -f "$pageFile"
}

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

  packUrl=$(pack_url "$pack")
  packArchive="$TARGET_DIR/$pack.zip"

  if [ -z "$packUrl" ] ; then
    echo "The $pack pack page names no archive to download." >&2
    echo "Check the pack name against https://kenney.nl/assets" >&2
    exit 1
  fi

  echo "Downloading $pack: $packUrl"

  if ! download "$packUrl" "$packArchive"; then
    rm -f "$packArchive"
    echo "Fail to download the $pack pack from $packUrl." >&2
    echo "Correct the KENNEY_AUDIO_PAGE_TEMPLATE environment variable or download the pack by hand from https://kenney.nl/assets" >&2
    exit 1
  fi

  mkdir -p "$packDir"

  if ! unzip -q "$packArchive" -d "$packDir"; then
    rm -rf "$packDir" "$packArchive"
    echo "Fail to unpack the downloaded $pack pack archive" >&2
    exit 1
  fi

  # The archives are Windows made ones and carry the DOS read-only attribute on
  # a directory of their own (the Audio one of the digital-audio pack), which
  # the extraction turns into a directory no file may be created inside any
  # more: the packs are a build input and not a read-only tree, so the write
  # permission goes back on.
  chmod -R u+w "$packDir"

  rm -f "$packArchive"
done

echo "The Kenney sound packs are available under $TARGET_DIR"
