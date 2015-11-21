#!/bin/sh

echo "Testing test with -e flag"
echo "test -e ../bin && echo exists"
echo "Expecting: "
test -e ../bin && echo exists
echo "Result"
../bin/rshell <<EOF
test -e ../bin && echo exists
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing test with -e flag"
echo "test -e ../bin/happy && echo exists"
echo "Expecting: "
test -e ../bin/happy && echo exists
echo "Result"
../bin/rshell <<EOF
test -e ../bin/happy && echo exists
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing test with -f flag"
echo "test -f ../bin/rshell && echo is file"
echo "Expecting: "
test -f ../bin/rshell && echo is file
echo "Result"
../bin/rshell <<EOF
test -f ../bin/rshell && echo is file
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing test with -f flag"
echo "test -f ../bin && echo is file"
echo "Expecting: "
test -f ../bin && echo is file
echo "Result"
../bin/rshell <<EOF
test -f ../bin && echo is file
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing test with -d flag"
echo "test -d ../bin && echo is dir"
echo "Expecting: "
test -d ../bin && echo is dir
echo "Result"
../bin/rshell <<EOF
test -d ../bin && echo is dir
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing test with -d flag"
echo "test -d ../bin/rshell && echo is dir"
echo "Expecting: "
test -d ../bin/rshell && echo is dir
echo "Result"
../bin/rshell <<EOF
test -d ../bin/rshell && echo is dir
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing test with no flag"
echo "test ../bin && echo exists"
echo "Expecting: "
test ../bin && echo exists
echo "Result"
../bin/rshell <<EOF
test ../bin && echo exists
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing test with no flag"
echo "test ../bin/happy && echo exists"
echo "Expecting: "
test ../bin/happy && echo exists
echo "Result"
../bin/rshell <<EOF
test ../bin/happy && echo exists
exit
EOF
echo --------------------------------------------------------------------------

#=======================================================================================================

echo "Testing [ ] with -e flag"
echo "[ -e ../bin ] && echo exists"
echo "Expecting: "
[ -e ../bin ] && echo exists
echo "Result"
../bin/rshell <<EOF
[ -e ../bin ] && echo exists
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing [ ] with -e flag"
echo "[ -e ../bin/happy ] && echo exists"
echo "Expecting: "
[ -e ../bin/happy ] && echo exists
echo "Result"
../bin/rshell <<EOF
[ -e ../bin/happy ] && echo exists
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing [ ] with -f flag"
echo "[ -f ../bin/rshell ] && echo is file"
echo "Expecting: "
[ -f ../bin/rshell ] && echo is file
echo "Result"
../bin/rshell <<EOF
[ -f ../bin/rshell ] && echo is file
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing [ ] with -f flag"
echo "[ -f ../bin ] && echo is file"
echo "Expecting: "
[ -f ../bin ] && echo is file
echo "Result"
../bin/rshell <<EOF
[ -f ../bin ] && echo is file
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing [ ] with -d flag"
echo "[ -d ../bin ] && echo is dir"
echo "Expecting: "
[ -d ../bin ] && echo is dir
echo "Result"
../bin/rshell <<EOF
[ -d ../bin ] && echo is dir
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing [ ] with -d flag"
echo "[ -d ../bin/rshell ] && echo is dir"
echo "Expecting: "
[ -d ../bin/rshell ] && echo is dir
echo "Result"
../bin/rshell <<EOF
[ -d ../bin/rshell ] && echo is dir
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing [ ] with no flag"
echo "[ ../bin ] && echo exists"
echo "Expecting: "
[ ../bin ] && echo exists
echo "Result"
../bin/rshell <<EOF
[ ../bin ] && echo exists
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing [ ] with no flag"
echo "[ ../bin/happy ] && echo exists"
echo "Expecting: "
[ ../bin/happy ] && echo exists
echo "Result"
../bin/rshell <<EOF
[ ../bin/happy ] && echo exists
exit
EOF
echo --------------------------------------------------------------------------


