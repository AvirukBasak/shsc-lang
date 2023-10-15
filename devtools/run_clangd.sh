#!/bin/bash

# Define the command to run clangd
CLANGD_COMMAND="clangd"  # You may need to specify the full path if clangd is not in your PATH

# Find all source files in the current directory and subdirectories
SOURCE_FILES=$(find . -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" \))

# Loop through each source file and run clangd on it
for file in $SOURCE_FILES; do
    echo "Running clangd on $file"
    $CLANGD_COMMAND --check="$file"
done
