#include "stack-char.h"

StackDefine(char, {
    // print value if printable ascii
    if (value >= 33 && value <= 127)
        printf("[ %0x02x, %c ]", value, value);
    else
        printf("[ %0x02x, . ]", value);
});
