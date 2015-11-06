#!/bin/sh
echo "Testing || operator"

echo "ls -a || ls -l"
../bin/rshell <<EOF
ls -a || ls -l
exit
EOF
echo

echo "dingle || ls -al"
../bin/rshell <<EOF
dingle || ls -al
exit
EOF
echo

echo "Testing && operator"

echo "ls -a && ls -l"
../bin/rshell <<EOF
ls -a && ls -l
exit
EOF

echo "dingle && ls -al"
../bin/rshell <<EOF
dingle && ls -al
exit
EOF
echo

echo "Testing ; operator"

echo "ls -a; ls -l"
../bin/rshell <<EOF
ls -a; ls -l
exit
EOF

echo "dingle; ls -al"
../bin/rshell <<EOF
dingle; ls -al
exit
EOF

