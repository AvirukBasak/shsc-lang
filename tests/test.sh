#!/bin/bash

# check if make, bison and gcc are installed
if ! [ -x "$(command -v make)" ]; then
  echo 'test.sh: error: make is not installed.' >&2
  exit 1
fi

if ! [ -x "$(command -v bison)" ]; then
  echo 'test.sh: error: bison is not installed.' >&2
  exit 1
fi

if ! [ -x "$(command -v gcc)" ]; then
  echo 'test.sh: error: gcc is not installed.' >&2
  exit 1
fi


# check flags
make run-sanitize ARGS="-h"
make run-sanitize ARGS="--help"
make run-sanitize ARGS="-v"
make run-sanitize ARGS="--version"
make run-sanitize ARGS="-tf"
make run-sanitize ARGS="--astf"
make run-sanitize ARGS="-r"
make run-sanitize ARGS="--run"



# resolve and normalize path '../example' to absolute with relative to this script directory
testpath="$(cd "$(dirname "$0")" && pwd)/../examples"
testpath="$(realpath "$testpath")"

# run all scripts in ../examples/ using make run-sanitize ARGS="$filename"
for filename in "$testpath/"*.txt; do
    echo -e "\n-----------------------------------------------------\n"
    echo -e ">> Running $filename\n"
    make run-sanitize ARGS="$filename"
done



# individual tests
echo -e "\n-----------------------------------------------------\n"
echo -e ">> Running $testpath/oop/\n"
make run-sanitize ARGS="$testpath/oop/*.txt"



# new testpath, resolve and normalize, ../tests/
testpath="$(cd "$(dirname "$0")" && pwd)/../tests"
testpath="$(realpath "$testpath")"


echo -e "\n-----------------------------------------------------\n"
echo -e ">> Bulk running $testpath/build.txt\n"
# flag -tf test
# run make run-sanitize ARGS="-tf tests/SyntaxTree.json -r tests/build.txt"
# test fails if theres a difference between old and new SyntaxTree.json
# this can be checked with git
make run-sanitize ARGS="-tf tests/SyntaxTree.json -r tests/build.txt"

# check if there are any differences between old and new SyntaxTree.json
# if there are differences, the test fails
if ! git diff --quiet --exit-code tests/SyntaxTree.json; then
    echo 'test.sh: error: SyntaxTree.json has changed.' >&2
    exit 1
fi
