#!/bin/bash

INPUT_FILE="$(pwd)/01_test_input_data.txt"

echo "TEST EX01"
pushd . > /dev/null
cd ../ex01
make

./phone_book < "$INPUT_FILE"

make fclean
popd > /dev/null
