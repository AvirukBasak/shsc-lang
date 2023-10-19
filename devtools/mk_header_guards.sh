# Write a script that takes input a directory and creates header guards for all the files in that directory.
# USAGE: ./mk_header_guard.sh MY_HEADER_PREFIX directory/
# result: non-recursively take only all the files in that directory and genereate the header as:
#    "#ifndef MY_HEADER_PREFIX_$FNAME\n"
#    "#define MY_HEADER_PREFIX_$FNAME\n"
#    "\n"
#    "\n"
#    "\n"
#    "#endif\n"
# if file basename is abc.c.h, FNAME will become ABC_C_H
# if file basename is abc.h, FNAME will become ABC_H
# if file basename is abc.c, FNAME will become ABC_C
# generate a bash script that does this

# take args from cli args
prefix=$1
directory=$2

# check if input is valid
if [[ $# -ne 2 ]]; then
    echo "USAGE: $0 [HEADER_PREFIX] [directory]"
    exit 1
fi

# loop through all the files in the directory
for file in $directory/*; do
    # get the basename of the file
    base=$(basename $file)
    # check if file name ends with .c.h
    if [[ $base == *.c.h ]]; then
        # if yes, then remove the .c.h and convert to uppercase
        fname=$(echo ${base%.c.h} | tr '[:lower:]' '[:upper:]')
        # append _C_H to the end
        fname="${fname}_C_H"
    # check if file name ends with .h
    elif [[ $base == *.h ]]; then
        # if yes, then remove the .h and convert to uppercase
        fname=$(echo ${base%.h} | tr '[:lower:]' '[:upper:]')
        # append _H to the end
        fname="${fname}_H"
    # check if file name ends with .c
    elif [[ $base == *.c ]]; then
        # if yes, then remove the .c and convert to uppercase
        fname=$(echo ${base%.c} | tr '[:lower:]' '[:upper:]')
        # append _C to the end
        fname="${fname}_C"
    fi
    # print the header guards
    echo "#ifndef ${prefix}_${fname}"  > $file
    echo "#define ${prefix}_${fname}" >> $file
    echo "" >> $file
    echo "" >> $file
    echo "" >> $file
    if [[ $base == *.c.h ]]; then
        echo "#else" >> $file
        echo "    #warning re-inclusion of module '$directory/$(basename $file)'" >> $file
    fi
    echo "#endif" >> $file
    echo "Updated $file"
done
