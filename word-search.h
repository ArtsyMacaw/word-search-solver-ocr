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
#define ALPHABET 1114112
#define DEFAULT_SIZE 100

typedef struct
{
    wchar_t ch;
    char color;
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

typedef enum {
    PUZZLE_LIST_IMAGE,
    WORD_LIST_IMAGE
} image_t;

FILE *read_image(char *file, image_t type);
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
bool is_image(FILE *inptr);

#endif
