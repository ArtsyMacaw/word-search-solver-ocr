#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <search.h>

trie *start;
int max_length = 0;

// Builds trie when given file ptr
bool load(FILE *list)
{
    start = malloc(sizeof(trie));
    init(start);
    char word[MAX_LENGTH];
    while (fscanf(list, "%s", word) != EOF)
    {
        int n = strlen(word);
        strncpy(word, word, n + 1);
        word[n]= '\0';
        if (n > max_length)
        {
            max_length = n;
        }
        for (int i = 0; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }
        insert(word);
    }
    return true;
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
        if (trav->path[key[i] - 'a'])
        {
            trav = trav->path[key[i] - 'a'];
        }
        else
        {
            trie *node = malloc(sizeof(trie));
            init(node);
            trav->path[key[i] - 'a'] = node;
            trav = trav->path[key[i] - 'a'];
        }
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
