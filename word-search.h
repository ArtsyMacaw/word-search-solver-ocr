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

#define INVALID -1
#define ALPHABET 65536
#define DEFAULT_SIZE 100

typedef struct
{
    wchar_t ch;
    bool highlight;
} bchar;

typedef struct
{
    wchar_t ch;
    int x;
    int y;
} pos;

typedef struct trie
{
    bool valid;
    struct trie *path[ALPHABET]; 
} trie;

FILE *read_puzzle_image(char *file);
FILE *read_list_image(char *file);
wchar_t *get_word(FILE *inptr);
void index_node(trie *node);
void check(pos cor);
pos translate(pos cor, int dir);
void highlight(pos *cors, int length);
int row_size(void);
int col_size(void);
bchar **parse(FILE *inptr);
bchar *get_row(FILE *inptr);
bool load(FILE *list);
void insert(wchar_t *key);
trie *locate(pos *key, int length);
void unload_trie(void);
void unload_array(bchar **tmp);
int word_length(void);
bool isImage(FILE *inptr);

#endif
