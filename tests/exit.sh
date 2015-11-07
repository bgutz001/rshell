#!/bin/sh

echo "Testing Exit by itself"
../bin/rshell <<EOF
exit
EOF
echo "Success!"
echo --------------------------------------------------------------------------

echo "Testing Exit with || command"
echo "ls || exit"
echo "ls && exit"
../bin/rshell <<EOF
ls || exit
ls && exit
EOF
echo "Success!"
echo --------------------------------------------------------------------------

