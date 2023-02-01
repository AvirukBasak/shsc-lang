#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tlib/bst-map/bst-map.template.h"

BstMapDeclarePrototypes(char);

BstMapDefine(char, {
    /* print value if printable ascii */
    if (value >= 33 && value <= 127)
        printf("[ 0x%02x, %c ]", value, value);
    else
        printf("[ 0x%02x, . ]", value);
});

int main(int argc, char **argv)
{
    BstMap(char) m2 = BstMapFunc(char, newmap);
    BstMapFunc(char, set, m2, BstMapFunc(char, hashString, "key1"), 'A');
    BstMapFunc(char, set, m2, BstMapFunc(char, hashString, "key2"), '\n');
    printf("char map = "); BstMapFunc(char, print, m2);
    BstMapFunc(char, free, &m2);
    return 0;
}
