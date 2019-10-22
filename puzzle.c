#include <stdio.h>
#include <search.h>
#include <stdbool.h>
#include <string.h>

char **parse(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    int count = 0;
    char **col = malloc(sizeof(char *) * size);
    while (feof(inptr) == 0)
    {
        if (count == size)
        {
            size = size * 2;
            col = realloc(col, size);
        }
        else
        {
            col[count] = get_row(inptr);
            count++;
        }
    }
    strncpy(col, col, count + 1);
    col[count] = '\0';
    return col;
}

char *get_row(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    char *row = malloc(sizeof(char) * size);
    int count = 0;
    while (true)
    {
        if(count = size)
        {
            size = size * 2;
            row = realloc(row, size);
        }
        char ch = fgetc(inptr);
        if (ch == '\n')
        {
            break;
        }
        else if (ch != ' ')
        {
            row[count] = ch;
            count++;
        }    
    }
    strncpy(row, row, count + 1);
    row[count] = '\0';
    return row;
}