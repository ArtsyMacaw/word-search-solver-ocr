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

int row_size(void);
int col_size(void);
char **parse(FILE *inptr);
char *get_row(FILE *inptr);
void init(trie *init);
bool load(FILE *list);
void insert(char *key);
trie *locate(char *key);

#endif
