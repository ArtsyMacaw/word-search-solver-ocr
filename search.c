#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <search.h>

char **scramble;

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
        return 4;
    }
    scramble = parse(puzzle);

    int n = row_size();
    int m = col_size();
    pos cor;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cor.x = i;
            cor.y = j;
            cor.ch = tolower(scramble[i][j]);
            check(cor);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c ", scramble[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void check(pos cor)
{
    int count = 0;
    pos *buffer = malloc(max_size() * sizeof(pos));
    pos tmp;
    for (int i = 0; i < DIRECTIONS; i++)
    {
        tmp = cor;
        buffer[count] = cor;
        count++;

        while (true)
        {
            trie *node = locate(buffer, count);
            if (!node)
            {
                break;
            }
            if (node->valid)
            {
                buffer = realloc(buffer, sizeof(pos) * count);
                highlight(buffer, count);
                break;
            }
            tmp = translate(tmp, i);
            if (tmp.x == -1)
            {
                break;
            }
            buffer[count] = tmp;
            count++;
        }
        free(buffer);
        buffer = malloc(sizeof(pos) * max_size());
        count = 0;
    }
}

pos translate(pos cor, int dir)
{
    switch (dir)
    {
        case N:
            cor.y = cor.y + 1;
            break;
        case NE:
            cor.x = cor.x + 1;
            cor.y = cor.y + 1;
            break;
        case E:
            cor.x = cor.x + 1;
            break;
        case SE:
            cor.x = cor.x + 1;
            cor.y = cor.y - 1;
            break;
        case S:
            cor.y = cor.y - 1;
            break;
        case SW:
            cor.x = cor.x - 1;
            cor.y = cor.y - 1;
            break;
        case W:
            cor.x = cor.x - 1;
            break;
        case NW:
            cor.x = cor.x - 1;
            cor.y = cor.y + 1;
    }
    if ((cor.x >= row_size() || cor.x < 0) || (cor.y >= col_size() || cor.y < 0))
    {
        cor.x = -1;
        return cor;
    }
    cor.ch = tolower(scramble[cor.x][cor.y]);

    return cor;
}

void highlight(pos *cors, int length)
{
    for (int i = 0; i < length; i++)
    {
        scramble[cors[i].x][cors[i].y] = toupper(cors[i].ch);
    }
}
