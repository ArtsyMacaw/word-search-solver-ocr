#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: search word-list scrambled output");
        return 1;
    }
    
    FILE *list, *scram, *out;
    list = fopen(argv[1], "r");
    if (!list)
    {
        printf("Could not open %s", argv[1]);
        return 2;
    }
    scram = fopen(argv[2], "r");
    if (!scram)
    {
        printf("Could not open %s", argv[2]);
        return 2;
    }
}
