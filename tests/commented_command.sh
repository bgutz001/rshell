#!/bin/sh
../bin/rshell <<EOF
echo Testing commented out commands
echo ls -p
#ls
echo
echo git
#git
echo
echo 
echo Testing single commands with one commented out argument
echo ls -a
ls #-a
echo
echo git status
git #status
echo
echo happy birthday
happy #birthday
echo
echo
echo ls -l
ls #-l 
echo
echo
echo Testing two commands with second one commented
echo echo hi and ls -a
echo hi && #ls -a
echo
echo
echo Testing two commands with first one commented
echo echo hi and ls -a
#echo hi && ls -a
echo
echo
exit
EOF
