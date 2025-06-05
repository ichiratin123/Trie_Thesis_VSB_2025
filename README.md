# Trie Benchmark Application

This project benchmarks three types of Trie data structures and a sequential array by measuring their insertion, search, and deletion times, as well as their memory usage:

- **Non-Sorted Array Trie** (`TrieUnsortedArray`)
- **Sorted Array Trie** (`TrieSortedArray`)
- **Hash Table Trie** (`TrieHashTable`)
- **Sequential Array Trie** (`SequentialArray`)

---

## Build Instructions

- Platform: **Windows** (uses Windows-specific headers like `<Windows.h>`, `<psapi.h>`, `_setmode`, etc.)
- Compiler: Use **Visual Studio** or any C++23 compliant compiler on Windows.

Make sure the following source files are present:

- `nonsortedTrie.cpp`
- `sortedTrie.cpp`
- `hashtable.cpp`
- `sequentialArray.cpp`
- `sortedCompressed.cpp`

---

## Makefile Usage

This project provides a Makefile for easier building.

To build the project:

```bash
make
```

To clean up the build files (remove the executable):

```bash
make clean
```

## Usage

```bash
trieapp <data_file> <command> <word_or_number>
```

### Commands

- `-s <word>`: Search for a word in all tries.
- `-s -r <number>`: Randomly select `<number>` words from the file and search them.
- `-d <word>`: Delete a word from all tries.
- `-d -r <number>`: Randomly delete `<number>` words from the tries.
- `-p <option>`: Print the trie structure.
  - `1`: Non-Sorted Array Trie
  - `2`: Sorted Array Trie
  - `3`: Hash Table Trie

### Examples

```bash
trieapp data/test.txt -s world
trieapp data/test.txt -d hello
trieapp data/test.txt -s -r 10000
trieapp data/test.txt -d -r 10000
trieapp data/test.txt -p 2
```

---

## Output Information

When inserting, searching, or deleting, the program prints:

- Time taken (in seconds)
- Memory used (in MB)
- For search and delete random modes: reports if any word failed the operation.
