# WORD-SEARCH-SOLVER
## Purpose
A word search solver that supports all UTF-8 characters, is reasonably fast, and
supports parsing images. Also personally created as an educational experience
in data structures, encoding, and the life cycle of a project.
## Usage
Simple run "word-search list puzzle" where list is file that contains the
hidden words with each word on a line, and puzzle is a file which contains
the scrambled letters.
## Implementation Details
Begins by creating a trie of all key words, and then proceeds to load puzzle
into a 2d array, checks all characters in a direction until the trie confirms either
a certain path of characters doesn't exist or that its valid then highlights those
characters.
## TODO
- [X] Implement basic functionality
- [ ] Implement colored output
- [X] Improve NULL safety checks
- [X] Fix memory leaks
- [ ] Support other puzzle shapes besides squares
- [ ] Improve puzzle parser
- [ ] Add ocr support
- [ ] Support all UTF-8 characters
- [X] Allow key words of arbitrary length
- [ ] Standardize function naming scheme
- [ ] Improve file naming scheme
