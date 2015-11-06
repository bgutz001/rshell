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

echo "dingle || ls -a || ls"
../bin/rshell <<EOF
dingle || ls -a || ls
exit
EOF

echo "ls -a || ls || dingle"
../bin/rshell <<EOF
ls -a || ls || dingle
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

echo "ls && dingle && ls"
../bin/rshell <<EOF
ls && dingle && ls
exit
EOF

echo "dingle && ls && ls"
../bin/rshell <<EOF
dingle && ls && ls
exit
EOF
echo

echo "Testing ; operator"

echo "ls -a ; ls -l"
../bin/rshell <<EOF
ls -a ; ls -l
exit
EOF

echo "dingle ; ls -al"
../bin/rshell <<EOF
dingle ; ls -al
exit
EOF
echo

echo "Testing || and && operator"

echo "ls -a || dingle && ls"
../bin/rshell <<EOF
ls -a || dingle && ls
exit
EOF

echo "dingle && git || ls"
../bin/rshell <<EOF
dingle && git || ls
exit
EOF 

echo "Testing || and ; operator"

echo "ls || git ; ping -ac 1 www.google.com"
../bin/rshell <<EOF
ls || git ; ping -ac 1 www.google.com
exit
EOF

echo "ls ; ls -a || git"
../bin/rshell <<EOF
ls ; ls -a || git
exit
EOF

echo "Testing && and ; operator"

echo "ls && git ; ping -ac 1 www.google.com"
../bin/rshell <<EOF
ls && git ; ping -ac 1 www.google.com
exit
EOF

echo "ls ; ls -a && git"
../bin/rshell <<EOF
ls ; ls -a && git
exit
EOF

echo "Testing &&, || and ; operator"

echo "ls && ip link || git ; ping -ac 1 www.google.com"
../bin/rshell <<EOF
ls && ip link || git ; ping -ac 1 www.google.com
exit
EOF

echo "ls || git && ls -a ; ls"
../bin/rshell <<EOF
ls || git && ls -a ; ls
exit
EOF
echo
