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

void init_trie(trie *init);
bool load(FILE *list);
void insert_string(char *key);
void set_valid(char *key);
trie *get_node(trie *head, char *key);
trie *build_node(trie *trav, int in);
bool check(char *key);

#endif
