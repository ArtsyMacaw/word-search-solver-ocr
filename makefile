CC=clang
CFLAGS=-I. -fsanitize=integer -fsanitize=undefined -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow
DEPS=search.h
OBJ=search.o trie.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

word-search: $(OBJ)
	$(CC) -o word-search trie.o search.o