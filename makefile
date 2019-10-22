search:
	clang -fsanitize=integer -fsanitize=undefined -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -include search.h -Wshadow -c -o trie.o trie.c
	clang -fsanitize=integer -fsanitize=undefined -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -include search.h -Wshadow -c -o search.o search.c
	clang -fsanitize=integer -fsanitize=undefined -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wshadow -o search trie.o search.o
