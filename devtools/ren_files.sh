#!/bin/bash

# read -p "Text to replace in filenames: " to_replace
# read -p "Change to: " change_to

to_replace="$1"
change_to="$2"

if [ -z "$to_replace" ] || [ -z "$change_to" ]; then
  echo "This script can go through a directory and rename files by replacing a given text in their names."
  echo "The renaming system is very crude, so be careful about what you'll be renaming."
  echo
  echo "USAGE: $0 'old text' 'new text'"
  exit 1
fi

find . -type f -exec sh -c 'newname="$(echo "$0" | sed "s/$1/$2/g")"; [ "$0" != "$newname" ] && mv "$0" "$newname"' {} "$to_replace" "$change_to" \;
