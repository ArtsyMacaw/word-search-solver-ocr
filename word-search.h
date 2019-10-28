#ifndef SEARCH_H
#define SEARCH_H

#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET 65536
#define DIRECTIONS 8
#define DEFAULT_SIZE 100

#define BOLD "\x1b[31m"
#define RESET "\x1b[0m"

#define SPACE 32
#define NEWLINE 10
#define TAB 9

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
    wchar_t ch;
    int x;
    int y;
} pos;

typedef struct
{
    wchar_t ch;
    bool highlight;
} bchar;

typedef struct trie
{
    bool valid;
    struct trie *path[ALPHABET]; 
} trie;

wchar_t *get_word(FILE *inptr);
void index_node(trie *node);
void check(pos cor);
pos translate(pos cor, int dir);
void highlight(pos *cors, int length);
int row_size(void);
int col_size(void);
wchar_t **parse(FILE *inptr);
wchar_t *get_row(FILE *inptr);
bool load(FILE *list);
void insert(wchar_t *key);
trie *locate(pos *key, int length);
int max_size(void);
void unload_trie(void);
void unload_array(wchar_t **tmp);
trie *get_head(void);

#endif
