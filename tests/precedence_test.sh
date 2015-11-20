#!/bin/sh

echo "Testing precedence on a single command"
echo "(echo a)"
echo "Expecting: "
(echo a)
echo "Result"
../bin/rshell <<EOF
(echo a)
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing nested precedence on a single command"
echo "((echo a))"
echo "Expecting: "
((echo a))
echo "Result"
../bin/rshell <<EOF
((echo a))
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing precedence on a multiple commands"
echo "(echo a && echo b) || (echo c && echo d)"
echo "Expecting: "
(echo a && echo b) || (echo c && echo d)
echo "Result"
../bin/rshell <<EOF
(echo a && echo b) || (echo c && echo d)
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing precedence on left side of operator"
echo "(echo a && echo b) || echo c && echo d"
echo "Expecting: "
(echo a && echo b) || echo c && echo d
echo "Result"
../bin/rshell <<EOF
(echo a && echo b) || echo c && echo d
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing precedence on right side of operator"
echo "echo a && echo b || (echo c && echo d)"
echo "Expecting: "
echo a && echo b || (echo c && echo d)
echo "Result"
../bin/rshell <<EOF
echo a && echo b || (echo c && echo d)
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing nested precedence on multiple commands"
echo "echo e && ((echo a && echo b) || (echo c && echo d))"
echo "Expecting: "
echo e && ((echo a && echo b) || (echo c && echo d))
echo "Result"
../bin/rshell <<EOF
echo e && ((echo a && echo b) || (echo c && echo d))
exit
EOF
echo --------------------------------------------------------------------------

echo "Testing nested precedence on multiple commands"
echo "echo e || ((echo a && echo b) || (echo c && echo d))"
echo "Expecting: "
echo e || ((echo a && echo b) || (echo c && echo d))
echo "Result"
../bin/rshell <<EOF
echo e || ((echo a && echo b) || (echo c && echo d))
exit
EOF
echo --------------------------------------------------------------------------

