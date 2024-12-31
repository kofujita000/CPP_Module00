#!/bin/bash

echo "TEST EX00"
pushd . > /dev/null
cd ../ex00
make

echo " PATTERN[00]"
echo "  exec: ./megaphone \"shhhhh... I think the students are asleep...\""
./megaphone "shhhhh... I think the students are asleep..."
echo ""

echo " PATTERN[01]"
echo "exec: ./megaphone Damnit \" ! \" \"Sorry students, I thought this thing was off.\""
./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
echo ""

echo " PATTERN[02]"
echo "exec: ./megaphone"
./megaphone
echo ""

make fclean
popd > /dev/null
