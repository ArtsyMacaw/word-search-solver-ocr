#include <word-search.h>

/* Used instead of iterating over all pointers in trie
because it takes extremely long when using full unicode set */
typedef struct
{
    trie **node;
    int length;
} node_index;

static node_index trie_index;
static trie *head;
static int max_word_length = 0;

// Builds trie when given file ptr
bool load(FILE *list)
{
    trie_index.node = calloc(DEFAULT_SIZE, sizeof(trie*));
    if (!trie_index.node)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return false;
    }
    trie_index.length = 0;

    head = calloc(1, sizeof(trie));
    if (!head)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return false;
    }
    index_node(head);

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

// Does what it says on the tin indexes a node
void index_node(trie *node)
{
    static int size = DEFAULT_SIZE;

    if (size == trie_index.length)
    {
        size = size * 2;
        trie **tmp = realloc(trie_index.node, size * sizeof(trie*));
        if (!tmp)
        {
            fprintf(stderr, "Failed to allocate memory\n");
        }
        else if (tmp != trie_index.node)
        {
            trie_index.node = tmp;
        }
    }
    trie_index.node[trie_index.length] = node;
    trie_index.length++;
}

// Gets word from a file while ignoring seperating characters
wchar_t *get_word(FILE *inptr)
{
    int size = DEFAULT_SIZE;
    wchar_t *word = malloc(size * sizeof(wchar_t));
    int count = 0;

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

    if (count > max_word_length)
    {
        max_word_length = count;
    }

    word = realloc(word, (count + 1) * sizeof(wchar_t));
    word[count] = '\0';

    return word;
}

// Frees trie using index
void unload_trie(void)
{
    for (int i = 0; i < trie_index.length; i++)
    {
        free(trie_index.node[i]);
    }
    free(trie_index.node);
}

// Inserts string into trie
void insert(wchar_t *key)
{
    trie *trav = head;
    for (int i = 0; i < wcslen(key); i++)
    {
        if (!trav->path[towlower(key[i])])
        {
            trie *node = calloc(1, sizeof(trie));
            if (!node)
            {
                fprintf(stderr, "Failed to allocate memory\n");
            }
            index_node(node);
            trav->path[tolower(key[i])] = node;
        }
        trav = trav->path[towlower(key[i])];
    }
    trav->valid = true;
}

// Traverses trie using string and returns the node if it exists
trie *locate(pos *key, int n)
{
    trie *node = head;
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

int word_length(void)
{
    return max_word_length;
}
