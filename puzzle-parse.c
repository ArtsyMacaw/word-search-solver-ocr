#include <word-search.h>

static int rsize = INVALID;
static int csize = 0;

bchar **parse(FILE *inptr)
{
    csize = 0;
    int size = DEFAULT_SIZE;
    bchar **col = malloc(sizeof(bchar*) * size);
    while (true)
    {
        if (csize == size)
        {
            size = size * 2;
            bchar **tmp = realloc(col, (size * sizeof(bchar*)));
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

    col = realloc(col, (csize + 1) * sizeof(bchar*));
    col[csize] = NULL;
    return col;
}

bchar *get_row(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    bchar *row = malloc(sizeof(bchar) * size);
    int count = 0;

    while (true)
    {
        if(count == size)
        {
            size = size * 2;
            bchar *tmp = realloc(row, size * sizeof(bchar));
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

        if(wc == '\n')
        {
            break;
        }

        if (wc == WEOF)
        {
            free(row);
            return NULL;
        }

        if (wc != ' ' && wc != '	')
        {
            row[count].ch = wc;
            row[count].color = INVALID;
            count++;
        }    
    }
    if (rsize > count || rsize == INVALID)
    {
        rsize = count;
    }
    row = realloc(row, sizeof(bchar) * (rsize + 1));
    row[rsize].ch = '\0';
    return row;
}

void unload_array(bchar **tmp)
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
