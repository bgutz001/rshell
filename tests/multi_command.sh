#!/bin/sh
echo "Testing || operator"

echo "ls -a || ls -l"
echo "Expecting:"
ls -a || ls -l
echo "Result:"
../bin/rshell <<EOF
ls -a || ls -l
exit
EOF
echo -----------------------------------------------------

echo "dingle || ls -al"
echo "Expecting:"
dingle || ls -al
echo "Result:"
../bin/rshell <<EOF
dingle || ls -al
exit
EOF
echo -----------------------------------------------------

echo "dingle || ls -a || ls"
echo "Expecting:"
dingle || ls -a || ls
echo "Result:"
../bin/rshell <<EOF
dingle || ls -a || ls
exit
EOF
echo -----------------------------------------------------

echo "ls -a || ls || dingle"
echo "Expecting:"
ls -a || ls || dingle
echo "Result:"
../bin/rshell <<EOF
ls -a || ls || dingle
exit
EOF
echo -----------------------------------------------------
echo

echo "Testing && operator"

echo "ls -a && ls -l"
echo "Expecting:"
ls -a && ls -l
echo "Result:"
../bin/rshell <<EOF
ls -a && ls -l
exit
EOF
echo -----------------------------------------------------

echo "dingle && ls -al"
echo "Expecting:"
dingle && ls -al
echo "Result:"
../bin/rshell <<EOF
dingle && ls -al
exit
EOF
echo -----------------------------------------------------

echo "ls && dingle && ls"
echo "Expecting:"
ls && dingle && ls
echo "Result:"
../bin/rshell <<EOF
ls && dingle && ls
exit
EOF
echo -----------------------------------------------------

echo "dingle && ls && ls"
echo "Expecting:"
dingle && ls && ls
echo "Result:"
../bin/rshell <<EOF
dingle && ls && ls
exit
EOF
echo -----------------------------------------------------
echo

echo "Testing ; operator"

echo "ls -a ; ls -l"
echo "Expecting:"
ls -a; ls -l
echo "Result:"
../bin/rshell <<EOF
ls -a; ls -l
exit
EOF
echo -----------------------------------------------------

echo "dingle ; ls -al"
echo "Expecting:"
dingle; ls -al
echo "Result:"
../bin/rshell <<EOF
dingle ; ls -al
exit
EOF
echo -----------------------------------------------------
echo

echo "Testing || and && operator"

echo "ls -a || dingle && ls"
echo "Expecting:"
ls -a || dingle && ls
echo "Result:"
../bin/rshell <<EOF
ls -a || dingle && ls
exit
EOF
echo -----------------------------------------------------

echo "dingle && git || ls"
echo "Expecting:"
dingle && git || ls
echo "Result:"
../bin/rshell <<EOF
dingle && git || ls
exit
EOF 
echo -----------------------------------------------------

echo "Testing || and ; operator"

echo "ls || git ; ping -ac 1 www.google.com"
echo "Expecting:"
ls || git; ping -ac 1 www.google.com
echo "Result:"
../bin/rshell <<EOF
ls || git ; ping -ac 1 www.google.com
exit
EOF
echo -----------------------------------------------------

echo "ls ; ls -a || git"
echo "Expecting:"
ls; ls -a || git
echo "Result:"
../bin/rshell <<EOF
ls ; ls -a || git
exit
EOF
echo -----------------------------------------------------
echo

echo "Testing && and ; operator"

echo "ls && git ; ping -ac 1 www.google.com"
echo "Expecting:"
ls && git; ping -ac www.google.com
echo "Result:"
../bin/rshell <<EOF
ls && git ; ping -ac 1 www.google.com
exit
EOF
echo -----------------------------------------------------

echo "ls ; ls -a && git"
echo "Expecting:"
ls; ls -a && git
echo "Result:"
../bin/rshell <<EOF
ls ; ls -a && git
exit
EOF
echo -----------------------------------------------------
echo

echo "Testing &&, || and ; operator"

echo "ls && ip link || git ; ping -ac 1 www.google.com"
echo "Expecting:"
ls && ip link || git; ping -ac 1 www.google.com
echo "Result:"
../bin/rshell <<EOF
ls && ip link || git ; ping -ac 1 www.google.com
exit
EOF
echo -----------------------------------------------------

echo "ls || git && ls -a ; ls"
echo "Expecting:"
ls || git && ls -a; ls
echo "Result:"
../bin/rshell <<EOF
ls || git && ls -a ; ls
exit
EOF
echo -----------------------------------------------------
echo
