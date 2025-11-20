#!/bin/bash

echo "Number of wrong inputs:"
echo "Wrong test: "
cat wrong_input.txt | grep -v -E '(^#)|(^$)' | wc -l

echo "./btc wrong_input.txt:"
./btc wrong_input.txt | wc -l
echo

echo "=====Input======"
echo
cat wrong_input.txt
echo

echo "==== Output ==="
echo
./btc wrong_input.txt
echo
