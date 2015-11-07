#!/bin/sh
echo Testing commented out commands
echo "#ls" 
../bin/rshell <<EOF
#ls
exit
EOF

echo "#git"
../bin/rshell <<EOF
#git
exit
EOF

echo Testing single commands with one commented out argument
echo "ls #-a"
../bin/rshell <<EOF
ls #-a
exit
EOF

echo "git #status"
../bin/rshell <<EOF
git #status
exit
EOF

echo "happy #birthday"
../bin/rshell <<EOF
happy #birthday
exit
EOF

echo "ls #-l"
../bin/rshell <<EOF
ls #-l 
exit
EOF

echo Testing two commands with second one commented
echo "echo hi && #ls -a"
../bin/rshell <<EOF
echo hi && #ls -a
exit
EOF

echo Testing two commands with first one commented
echo "#echo hi && ls -a"
../bin/rshell <<EOF
#echo hi && ls -a
exit
EOF
