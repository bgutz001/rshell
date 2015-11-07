#!/bin/sh

echo "Testing Exit by itself"
../bin/rshell <<EOF
exit
EOF
echo "Success!"
echo --------------------------------------------------------------------------

echo "Testing Exit with || command"
echo "ls || exit"
echo "dingle || exit"
../bin/rshell <<EOF
ls || exit
dingle || exit
EOF
echo "Success!"
echo --------------------------------------------------------------------------

echo "Testing Exit with && command"
echo "dingle && exit"
echo "ls && exit"
../bin/rshell <<EOF
dingle && exit
ls && exit
EOF
echo "Success!"
echo --------------------------------------------------------------------------

echo "Testing Exit with ; command"
echo "ls; exit"
../bin/rshell <<EOF
ls; exit
EOF
echo "Success!"
