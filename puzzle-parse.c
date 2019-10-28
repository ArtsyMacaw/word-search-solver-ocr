#include <word-search.h>

int rsize = 0;
int csize = 0;

wchar_t **parse(FILE *inptr)
{
    csize = 0;
    int size = DEFAULT_SIZE;
    wchar_t **col = malloc(sizeof(wchar_t*) * size);
    while (true)
    {
        if (csize == size)
        {
            size = size * 2;
            wchar_t **tmp = realloc(col, (size * sizeof(wchar_t*)));
            if (!tmp)
            {
                free(col);
                return tmp;
            }
            else if (tmp != col)
            {
                col = tmp;
            }
        }
        col[csize] = get_row(inptr);
        if (!col[csize])
        {
            break;
        }
        csize++;
    }

    col = realloc(col, (csize + 1) * sizeof(wchar_t*));
    col[csize] = NULL;
    return col;
}

wchar_t *get_row(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    wchar_t *row = malloc(sizeof(wchar_t) * size);
    int count = 0;

    while (true)
    {
        if(count == size)
        {
            size = size * 2;
            wchar_t *tmp = realloc(row, size * sizeof(wchar_t));
            if (!tmp)
            {
                free(row);
                return tmp;
            }
            else if (tmp != row)
            {
                row = tmp;
            }
        }

        wint_t wc = fgetwc(inptr);

        if(wc == NEWLINE)
        {
            break;
        }

        if (wc == WEOF)
        {
            free(row);
            return NULL;
        }

        if (wc != SPACE && wc != TAB)
        {
            row[count] = towlower(wc);
            count++;
        }    
    }
    if (rsize < count)
    {
        rsize = count;
    }
    row = realloc(row, sizeof(wchar_t) * (rsize + 1));
    row[rsize] = '\0';
    return row;
}

void unload_array(wchar_t **tmp)
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
