#include <search.h>

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
            char **tmp = realloc(col, (size * sizeof(char*)));
            if (!tmp)
            {
                return tmp;
            }
            else if (tmp != col)
            {
                free(col);
                col = tmp;
            }
        }
        col[csize] = get_row(inptr);
        csize++;
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
            char *tmp = realloc(row, size);
            if (!tmp)
            {
                return tmp;
            }
            else if (tmp != row)
            {
                free(row);
                row = tmp;
            }
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
    row = realloc(row, sizeof(char) * (rsize + 1));
    row[rsize] = '\0';
    return row;
}

void unload_array(char **tmp)
{
    int n = col_size();
    for (int i = 0; i < n; i++)
    {
        free(tmp[i]);
    }
    free(tmp);
}

int row_size(void)
{
    return rsize;
}

int col_size(void)
{
    return csize;
}
