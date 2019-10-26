#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET 26
#define DIRECTIONS 8
#define DEFAULT_SIZE 100

#define BOLD "\x1b[31m"
#define RESET "\x1b[0m"

#define N 0
#define NE 1
#define E 2
#define SE 3
#define S 4
#define SW 5
#define W 6
#define NW 7

typedef struct
{
    char ch;
    int x;
    int y;
} pos;

typedef struct trie
{
    bool valid;
    struct trie *path[ALPHABET]; 
} trie;

char *get_word(FILE *inptr);
void check(pos cor);
pos translate(pos cor, int dir);
void highlight(pos *cors, int length);
int row_size(void);
int col_size(void);
char **parse(FILE *inptr);
char *get_row(FILE *inptr);
void init(trie *init);
bool load(FILE *list);
void insert(char *key);
trie *locate(pos *key, int length);
int max_size(void);
void unload_trie(trie *trav);
void unload_array(char **tmp);
trie *get_head(void);

#endif
