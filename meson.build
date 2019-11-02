project('word-search-solver', 'c')
install_headers('word-search.h')
lib = shared_library('wordsearch', 'trie.c', 'puzzle-parse.c')
executable('word-search', 'word-search.c', link_with : lib)
