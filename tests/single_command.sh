#!/bin/sh
../bin/rshell <<EOF
echo Testing single commands with no arguments
echo ls
ls
echo
echo dingle
dingle
echo
echo git
git
echo
echo 
echo Testing single commands with one argument
echo ls -a
ls -a
echo
echo git status
git status
echo
echo happy birthday
happy birthday
echo
echo ip link
ip link
echo
echo ls -l
ls -l 
echo
echo
echo Testing single commands with multiple arguments
echo ping -ac 3 www.google.com
ping -ac 3 www.google.com
echo
echo ls ../ -a
ls ../ -a
echo
exit
EOF
