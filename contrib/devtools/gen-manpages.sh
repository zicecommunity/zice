#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

ZICED=${ZICED:-$SRCDIR/ziced}
ZICECLI=${ZICECLI:-$SRCDIR/zice-cli}
ZICETX=${ZICETX:-$SRCDIR/zice-tx}

[ ! -x $ZICED ] && echo "$ZICED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
ZCEVERSTR=$($ZICECLI --version | head -n1 | awk '{ print $NF }')
ZCEVER=$(echo $ZCEVERSTR | awk -F- '{ OFS="-"; NF--; print $0; }')
ZCECOMMIT=$(echo $ZCEVERSTR | awk -F- '{ print $NF }')

# Create a footer file with copyright content.
# This gets autodetected fine for ziced if --version-string is not set,
# but has different outcomes for zice-cli.
echo "[COPYRIGHT]" > footer.h2m
$ZICED --version | sed -n '1!p' >> footer.h2m

for cmd in $ZICED $ZICECLI $ZICETX; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=$ZCEVER --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-$ZCECOMMIT//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
