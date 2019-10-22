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
    init_trie(start);
    char word[MAX_LENGTH];
    while (fscanf(list, "%s", word) != EOF)
    {
        strncpy(word, word, strlen(word) + 1);
        word[strlen(word)] = '\0';
        for (int i = 0; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }
        insert_string(word);
    }
    return true;
}

// Checks if word exists
bool check(char *key)
{
    trie *word = get_node(start, key);
    if (!word)
    {
        return false;
    }
    return word->valid;
}

// Initialize trie node to null values
void init_trie(trie *init)
{
    for (int i = 0; i < ALPHABET; i++)
    {
        init->path[i] = NULL;
    }
    init->valid = false;
}

// Inserts string into trie
void insert_string(char *key)
{
    trie *trav = start;
    int n = strlen(key);
    for (int i = 0; i < n; i++)
    {
        trav = build_node(trav, key[i] - 'a');
    }
    set_valid(key);
}

void set_valid(char *key)
{
    trie *node = malloc(sizeof(trie));
    node = get_node(start, key);
    node->valid = true;
}

// Traverses trie using string
trie *get_node(trie *head, char *key)
{
    trie *node = head;
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

// Inserts a single character into trie
trie *build_node(trie *trav, int in)
{
    if (trav->path[in])
    {
        return trav->path[in];
    }
    else
    {
        trie *node = malloc(sizeof(trie));
        init_trie(node);
        trav->path[in] = node;
        return node;
    }
}
