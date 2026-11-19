#!/bin/bash -e
#
# Fails when an external URL of the tracked markdown files is unreachable,
# retrying the temporary failures.

. "$(dirname "$0")/common.sh"

MDLIST=$(mktemp)
URLLIST=$(mktemp)
UNIQLIST=$(mktemp)
BADLIST=$(mktemp)
WARNLIST=$(mktemp)
trap 'rm -f "$MDLIST" "$URLLIST" "$UNIQLIST" "$BADLIST" "$WARNLIST"' EXIT

BT='`'
DQ='"'
CURLOPTS="--silent --location --globoff --connect-timeout 15 --max-time 45 --output /dev/null"
ATTEMPTS=3
RETRY_DELAY=5

# The repository own documentation only: a build tree keeps the
# fetched third-party sources with the markdown files of their own.
git ls-files -z '*.md' | tr '\0' '\n' | sort > "$MDLIST"

# Collect every external URL together with the documentation file it
# sits in, unwrapping it from the markdown link, the inline code, the
# HTML decorations and the | separated fields (a raw | never belongs
# to an URL) and dropping the local and the templated ones.
while IFS= read -r mdfile; do
  grep -oE "(https?|ftps?|git)://[^[:space:]]+" "$mdfile" 2>/dev/null |
  while IFS= read -r raw; do
    url="$raw"
    url="${url%%${BT}*}"
    url="${url%%${DQ}*}"
    url="${url%%<*}"
    url="${url%%>*}"
    url="${url%%]*}"
    url="${url%%|*}"
    case "$url" in *"("*) ;; *) url="${url%%)*}" ;; esac
    url=$(printf '%s' "$url" | sed 's/[.,;:!?]*$//')
    case "$url" in
      *://) continue ;;
      *'$'*|*'{'*|*'@'*) continue ;;
      *//localhost*|*//127.*|*//0.0.0.0*|*//'[::1]'*|*//192.168.*) continue ;;
      *//example.com*|*//example.org*) continue ;;
    esac
    printf '%s %s\n' "$url" "$mdfile"
  done
done < "$MDLIST" | sort -u > "$URLLIST"

awk '{print $1}' "$URLLIST" | sort -u > "$UNIQLIST"
echo "Checking $(wc -l < "$UNIQLIST") external URL(s) from $(wc -l < "$MDLIST") documentation file(s)"

# A single reachability probe printing the HTTP status code or the
# word telling how the request of a non-HTTP scheme has ended.
probe_url() {
  case "$1" in
    git://*)
      git ls-remote "$1" > /dev/null 2>&1 && echo git-ok || echo git-unreachable
      return
      ;;
    ftp://*|ftps://*)
      curl $CURLOPTS "$1" > /dev/null 2>&1 && echo ftp-ok || echo ftp-unreachable
      return
      ;;
  esac

  code=$(curl $CURLOPTS --head --write-out '%{http_code}' "$1" 2>/dev/null) || true
  case "$code" in
    2*|3*) echo "$code" ; return ;;
  esac

  # Some servers reject or mishandle HEAD - retry the URL with a GET.
  code=$(curl $CURLOPTS --request GET --write-out '%{http_code}' "$1" 2>/dev/null) || true
  case "$code" in
    2*|3*) echo "$code" ; return ;;
  esac

  echo "$code"
}

# A connection failure, a rate limit or a server-side error can be a
# single hiccup, while the other answers are the server final word.
retry_worthy() {
  case "$1" in
    000|408|429|5*|git-unreachable|ftp-unreachable) return 0 ;;
  esac
  return 1
}

while IFS= read -r url; do
  attempt=1
  while : ; do
    result=$(probe_url "$url")
    retry_worthy "$result" || break
    [ "$attempt" -lt "$ATTEMPTS" ] || break
    echo "  RETRY   $url ($result on the attempt $attempt of $ATTEMPTS, the next one in ${RETRY_DELAY}s)"
    attempt=$((attempt + 1))
    sleep "$RETRY_DELAY"
  done

  case "$result" in
    git-ok) echo "  OK      $url (reachable as a git remote)" ;;
    ftp-ok) echo "  OK      $url" ;;
    2*|3*) echo "  OK      $url ($result)" ;;
    403) echo "  OK      $url (403 - the server refuses the automated requests)" ;;
    405) echo "  OK      $url (405 - the endpoint exists but refuses the HEAD and GET requests)" ;;
    401|418|429)
      echo "  WARN    $url ($result - the server refuses the automated requests)"
      echo "$url $result" >> "$WARNLIST"
      ;;
    000)
      echo "  BROKEN  $url (no response: DNS, TLS or connection failure)"
      echo "$url no-response" >> "$BADLIST"
      ;;
    git-unreachable)
      echo "  BROKEN  $url (git ls-remote failed)"
      echo "$url git-unreachable" >> "$BADLIST"
      ;;
    ftp-unreachable)
      echo "  BROKEN  $url (FTP request failed)"
      echo "$url ftp-unreachable" >> "$BADLIST"
      ;;
    *)
      echo "  BROKEN  $url ($result)"
      echo "$url $result" >> "$BADLIST"
      ;;
  esac
done < "$UNIQLIST"

if [ -s "$WARNLIST" ]; then
  echo ""
  echo "WARNING: the servers below refuse the automated requests, so their pages are left unverified:"
  while read -r url code; do
    echo "  $url ($code)"
    awk -v u="$url" '$1 == u {print "      referenced by " $2}' "$URLLIST" | sort -u
  done < "$WARNLIST"
fi

if [ -s "$BADLIST" ]; then
  echo ""
  echo "FAIL: the documentation references the unreachable external URLs:"
  while read -r url code; do
    echo "  $url ($code)"
    awk -v u="$url" '$1 == u {print "      referenced by " $2}' "$URLLIST" | sort -u
  done < "$BADLIST"
  exit 1
fi

echo ""
echo "OK: every external documentation URL is reachable"
