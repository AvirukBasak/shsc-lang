#!/bin/bash

# read -p "Text to replace: " to_replace
# read -p "Change to: " change_to

to_replace="$1"
change_to="$2"

if [ -z "$to_replace" ] || [ -z "$change_to" ]; then
  echo "This script can go through every source file and replace a given text into a new text"
  echo "The replacement system is very crude and you must be careful about what you'll be renaming"
  echo
  echo "USAGE: $0 'old name' 'new name'"
  exit 1
fi

find . -type f \( -name "*.y" -o -name "*.c" -o -name "*.h" \) \
       -exec grep -l "$to_replace" {} \;                       \
       -exec sed -i "s/$to_replace/$change_to/g" {} \;         \
       ;
