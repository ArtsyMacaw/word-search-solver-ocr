#include <search.h>

trie *start;
int max_length = 0;
int length = 0;

// Builds trie when given file ptr
bool load(FILE *list)
{
    start = calloc(1, sizeof(trie));
    wchar_t *word = NULL;

    while (feof(list) == 0)
    {
        word = get_word(list);
        if (!word)
        {
            return false;
        }
        insert(word);
        free(word);
    }

    return true;
}

wchar_t *get_word(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    wchar_t *word = malloc(size * sizeof(wchar_t));
    int count = 0;
    length = 0;

    while (true)
    {
        if (size == count)
        {
            size = size * 2;
            wchar_t *tmp = realloc(word, size * sizeof(wchar_t));
            if (!tmp)
            {
                free(word);
                return tmp;
            }
            else if (tmp != word)
            {
                word = tmp;
            }
        }

        wint_t wc = fgetwc(inptr);
        if (wc == '\n' || wc == ' ' || wc == WEOF)
        {
            break;
        }

        word[count] = towlower(wc);
        count++;
    }

    if (count > max_length)
    {
        max_length = count;
    }

    word = realloc(word, (count + 1) * sizeof(wchar_t));
    word[count] = '\0';

    length = count;
    return word;
}

void unload_trie(trie *trav)
{
    trie *node = NULL;
    for (int i = 0; i < ALPHABET; i++)
    {
        node = trav->path[i];
        if (node)
        {
            unload_trie(node);
        }
    }
    free(trav);
}

// Inserts string into trie
void insert(wchar_t *key)
{
    trie *trav = start;
    for (int i = 0; i < length  ; i++)
    {
        if (!trav->path[towlower(key[i])])
        {
            trie *node = calloc(1, sizeof(trie));
            trav->path[tolower(key[i])] = node;
        }
        trav = trav->path[towlower(key[i])];
    }
    trav->valid = true;
}

// Traverses trie using string and returns the node if it exists
trie *locate(pos *key, int n)
{
    trie *node = start;
    for (int i = 0; i < n; i++)
    {
        node = node->path[towlower(key[i].ch)];
        if (!node)
        {
            return NULL;
        }
    }
    return node;
}

int max_size(void)
{
    return max_length;
}

trie *get_head(void)
{
    return start;
}
