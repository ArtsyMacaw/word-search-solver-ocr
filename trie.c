#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <search.h>

trie *start;

// Builds trie when given file ptr
bool load(FILE *list)
{
    start = malloc(sizeof(trie));
    init(start);
    char word[MAX_LENGTH];
    while (fscanf(list, "%s", word) != EOF)
    {
        strncpy(word, word, strlen(word) + 1);
        word[strlen(word)] = '\0';
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
trie *locate(char *key)
{
    trie *node = start;
    int n = strlen(key);
    for (int i = 0; i < n; i++)
    {
        node = node->path[key[i] - 'a'];
        if (!node)
        {
            return NULL;
        }
    }
    return node;
}
