#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "parser.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    parse(argv[1]);
    
    return 0;
}
