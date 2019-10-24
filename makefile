CC=clang
CFLAGS=-I. -ggdb -O0 -fsanitize=integer -fsanitize=undefined -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow
DEPS=search.h
OBJ=search.o trie.o puzzle.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

word-search: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o word-search

.PHONY : clean
clean:
	-rm *.o
