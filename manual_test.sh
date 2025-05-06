#!/bin/bash

echo "Generating input..."
build/GenerateInput /../tmp/input.bin 1000

echo "Sorting..."
build/TapeSorter /../tmp/input.bin /../tmp/output.bin

echo "Checking sort correctness..."
build/CheckSorted /../tmp/output.bin