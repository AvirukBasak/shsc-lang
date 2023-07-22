#include <stdio.h>
#include <math.h>

#include "stack-char.h"

int main()
{
    // char stack test
    Stack(char) st2 = StackFunc(char, newstack);
    StackFunc(char, push, st2, 'H');
    StackFunc(char, push, st2, '\t');
    StackFunc(char, push, st2, 'n');
    printf("char stack = "); StackFunc(char, print, st2);
    StackFunc(char, free, &st2);
    return 0;
}
