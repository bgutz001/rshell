#/bin/sh
echo Testing single commands with no arguments
echo ls
ls
echo dingle
dingle
echo git
git
echo 

echo Testing single commands that are commented
echo "#ls"
#ls
echo "#dingle"
#dingle
echo "#git"
#git
echo

echo Testing single commands with one argument
echo ls -a
ls -a
echo git status
git status
echo happy birthday
happy birthday
echo ip link
ip link
echo ls -l
ls -l 
echo

echo Testing single commands with one argument that are commented
echo "#ls -a"
#ls -a
echo "#git status"
#git status
echo "#happy Birthday"
#happy Birthday
echo "#ip link"
#ip link
echo "#ls -l"
#ls -l
echo

echo Testing single commands with multiple arguments

