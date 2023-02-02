#include <unistd.h>

void *foo() {
    return sbrk(0);
}
