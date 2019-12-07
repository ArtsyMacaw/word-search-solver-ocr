# WORD-SEARCH-SOLVER
## Purpose
A word search solver that supports all UTF-8 characters, is reasonably fast, and
supports parsing images. Also personally created as an educational experience
in data structures, encoding, and the life cycle of a project.
## Usage
Simply run "word-search list puzzle" where list is file that contains the
hidden words with each word separated by a space or line, and puzzle is a file which contains
the scrambled letters. Also can take either a PNG or JPEG in and process them for solving.
## Implementation Details
Begins by creating a trie of all key words, and then proceeds to load puzzle
into a 2d array, checks all characters in a direction until the trie confirms either
a certain path of characters doesn't exist or that its valid then highlights those
characters.
## Compiling from Source
Install dependencies:  
    * tesseract  
    * leptonica  
```
Run these commands:
git clone https://github.com/ArtsyMacaw/word-search-solver-ocr.git
cd word-search-solver-ocr
meson build
cd build
ninja
```
## TODO
- [X] Implement basic functionality
- [X] Implement colored output
- [X] Improve NULL safety checks
- [X] Fix memory leaks
- [ ] Support other puzzle shapes besides squares
- [ ] Improve puzzle parser
- [X] Add ocr support
- [X] Support all UTF-8 characters
- [X] Allow key words of arbitrary length
- [X] Standardize function naming scheme
- [X] Improve file naming scheme
