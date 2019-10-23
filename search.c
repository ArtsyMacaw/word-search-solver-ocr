#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <search.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: search list puzzle\n");
        return 1;
    }
    
    FILE *list, *puzzle;

    list = fopen(argv[1], "r");
    if (!list)
    {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }
    if (!load(list))
    {
        printf("Failed to build trie\n");
        return 3;
    }

    puzzle = fopen(argv[2], "r");
    if (!puzzle)
    {
        printf("Could not open %s\n", argv[2]);
        return 2;
    }
    char **scramble = parse(puzzle);

    int n = row_size();
    int m = col_size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", scramble[i][j]);
        }
        printf("\n");
    }
}
