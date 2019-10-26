#include <search.h>

trie *start;
int max_length = 0;

// Builds trie when given file ptr
bool load(FILE *list)
{
    start = malloc(sizeof(trie));
    init(start);
    char *word = NULL;

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

char *get_word(FILE *inptr)
{
    char ch = '\0';
    int size = DEFAULT_SIZE;
    char *word = malloc(size * sizeof(char));
    int count = 0;

    while (true)
    {
        if (size == count)
        {
            size = size * 2;
            char *tmp = realloc(word, size * sizeof(char));
            if (!tmp)
            {
                free(word);
                return tmp;
            }
            else if (tmp != word)
            {
                free(word);
                word = tmp;
            }
        }

        fread(&ch, sizeof(char), 1, inptr);
        if (ch == '\n' || ch == ' ' || feof(inptr) != 0)
        {
            break;
        }
        else
        {
            word[count] = tolower(ch);
            count++;
        }
    }

    if (count > max_length)
    {
        max_length = count;
    }

    word = realloc(word, (count + 1) * sizeof(char*));
    word[count] = '\0';

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

// Initialize trie node to null values
void init(trie *init)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        init->path[i] = NULL;
    }
    init->valid = false;
}

// Inserts string into trie
void insert(char *key)
{
    trie *trav = start;
    int n = strlen(key);
    for (int i = 0; i < n  ; i++)
    {
        if (!trav->path[key[i] - 'a'])
        {
            trie *node = malloc(sizeof(trie));
            init(node);
            trav->path[key[i] - 'a'] = node;
        }
        trav = trav->path[key[i] - 'a'];
    }
    trav->valid = true;
}

// Traverses trie using string and returns the node if it exists
trie *locate(pos *key, int n)
{
    trie *node = start;
    for (int i = 0; i < n; i++)
    {
        node = node->path[key[i].ch - 'a'];
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
