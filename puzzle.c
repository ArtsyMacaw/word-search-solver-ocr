#include <stdio.h>
#include <search.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int rsize = 0;
int csize = 0;

char **parse(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    csize = 0;
    char **col = malloc(sizeof(char*) * size);
    while (true)
    {
        if (csize == size)
        {
            size = size * 2;
            col = realloc(col, (size * sizeof(char*)));
        }
        else
        {
            col[csize] = get_row(inptr);
            csize++;
        }
        char ch;
        fread(&ch, sizeof(char), 1, inptr);
        if (feof(inptr) != 0)
        {
            break;
        }
        fseek(inptr, -1, SEEK_CUR);
    }
    col = realloc(col, (csize + 1) * sizeof(char*));
    col[csize] = NULL;
    return col;
}

char *get_row(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    if (feof(inptr) != 0)
    {
        return NULL;
    }
    char *row = malloc(sizeof(char) * size);
    rsize = 0;
    char ch;
    while (true)
    {
        if(rsize == size)
        {
            size = size * 2;
            row = realloc(row, size);
        }
        fread(&ch, sizeof(char), 1, inptr);
        if (ch == '\n')
        {
            break;
        }
        else if (ch != ' ')
        {
            row[rsize] = tolower(ch);
            rsize++;
        }    
    }
    strncpy(row, row, rsize + 1);
    row[rsize] = '\0';
    return row;
}

int row_size(void)
{
    return rsize;
}

int col_size(void)
{
    return csize;
}
