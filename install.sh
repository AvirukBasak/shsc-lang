#!/bin/bash

# check if make, bison and gcc are installed

if ! [ -x "$(command -v make)" ]; then
  echo 'install.sh: error: make is not installed.' >&2
  exit 1
fi

if ! [ -x "$(command -v bison)" ]; then
  echo 'install.sh: error: bison is not installed.' >&2
  exit 1
fi

if ! [ -x "$(command -v gcc)" ]; then
  echo 'install.sh: error: gcc is not installed.' >&2
  exit 1
fi


# run make
if ! make; then
    echo 'install.sh: error: make failed.' >&2
    exit 1
fi

# installation
echo -e "\n-----------------------------------------------------\n"
echo "To install run:"
echo "sudo make install"
echo -e "\n-----------------------------------------------------\n"
