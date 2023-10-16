#!/bin/bash
find . -type f \( -name "*.y" -o -name "*.c" -o -name "*.h" \) \
       -exec grep -l '[[:space:]]$' {} \;                      \
       -exec sed -i 's/[[:space:]]*$//g' {} \;                 \
       ;
