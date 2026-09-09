#!/usr/bin/env bash
# QMK build/flash environment for this checkout.
#
#   source ./qmk-env.sh          then use `gmake` / `qmk` normally
#   ./qmk-env.sh build           build the bgkeeb miryoku firmware
#   ./qmk-env.sh flash           build, then wait for a half in bootloader and flash it
#                                (run once per half; both halves take the same hex,
#                                 handedness comes from MASTER_RIGHT, not EE_HANDS)
#
# avr-gcc@8 is keg-only, so it needs an explicit PATH entry. The qmk CLI lives in a
# checkout-local venv instead of the global Python. Apple's /usr/bin/make is 3.81,
# which QMK does not support, so GNU make 4.x is used as `gmake`.

QMK_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")" && pwd)"
export PATH="$QMK_ROOT/.venv/bin:/opt/homebrew/opt/avr-gcc@8/bin:$PATH"

TARGET="fingerpunch/bgkeeb:manna-harbour_miryoku"

case "${1:-}" in
    build) gmake "$TARGET" ;;
    flash) gmake "$TARGET:avrdude" ;;
    "")    ;;  # sourced: PATH is set, nothing else to do
    *)     echo "usage: $0 [build|flash]" >&2; exit 1 ;;
esac
