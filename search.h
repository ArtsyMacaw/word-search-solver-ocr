#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET 26
#define MAX_LENGTH 50

typedef struct trie
{
    bool valid;
    struct trie *path[ALPHABET]; 
} trie;

void init(trie *init);
bool load(FILE *list);
void insert(char *key);
trie *locate(trie *head, char *key);

#endif
