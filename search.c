#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <search.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: search list scrambled out");
        return 1;
    }
    
    FILE *list, *scramble, *out;

    list = fopen(argv[1], "r");
    if (!list)
    {
        printf("Could not open %s", argv[1]);
        return 2;
    }

    scramble = fopen(argv[2], "r");
    if (!scramble)
    {
        printf("Could not open %s", argv[2]);
        return 2;
    }
    
    load(list);
}
