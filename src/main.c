#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "globals.h"
#include "io.h"
#include "parser.h"

int main(int argc, char **argv)
{
    if (argc < 2) io_errndie("no args provided");
    for (int i = 1; i < argc; i++) {
        global_currfile = argv[i];
        FILE *f = (argv[i][0] == '-' && !argv[i][1]) ?
            stdin :
            fopen(argv[i], "rb");
        if (!f) io_errndie("couldn't read file: '%s'", argv[i]);
        parser_interpret(f);
        if (f != stdin) fclose(f);
    }
    return 0;
}
