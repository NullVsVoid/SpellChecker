# Spell Checker Program README

## Overview

This spell checker program is a console-based application designed to load a dictionary of words from a file into a hash table, check input text for spelling errors, suggest possible corrections based on edit distance, allow users to add new words to the dictionary, and handle hash table collisions using separate chaining. It aims to provide a fast and efficient way to identify and correct spelling mistakes with a user-friendly interface.

## Approach

The program is implemented in C++ and uses a custom hash table class template (`CTL::HashTable`) for storing the dictionary. The hash table employs separate chaining to resolve collisions, ensuring efficient handling of insertions, deletions, and searches.

### Key Components:

- **Levenshtein Distance Algorithm**: Used to calculate the edit distance between two words, enabling the suggestion of corrections for misspelled words.
- **Hash Table with Separate Chaining**: Stores the dictionary, offering efficient lookup and insertion performance.
- **User Interface**: A simple, menu-driven command-line interface that guides the user through loading dictionaries, spell checking, adding words, and suggesting corrections.

## Optimization Techniques

- **Separate Chaining for Collision Resolution**: Reduces the impact of collisions on the performance of dictionary operations, ensuring consistent lookup times even as the dictionary size grows.
- **Dynamic Hash Table Resizing**: The hash table automatically resizes based on the load factor, maintaining a balance between memory usage and access time.

## Performance Measurements

Performance measurements were conducted to evaluate the efficiency of the spell checker program in terms of time complexity and memory usage. The tests involved varying dictionary sizes and input text lengths to assess scalability and performance under different conditions.

- **Load Time**: The time taken to load the dictionary into the hash table, O(n).
- **Spell Check Time**: The time required to check and identify misspelled words in a given text, O(n).
- **Suggestion Time**: The time to generate suggestions for all misspelled words using the Levenshtein distance algorithm, O(n * d * l^2).

## User Manual

### Running the Program

1. Compile the program using a C++ compiler, ensuring all required files are included.
2. Launch the program from a command-line interface.

### Menu Options

- **[L] Load Dictionary**: Load a dictionary file into the hash table. You will be prompted to enter the filename.
- **[C] Check Spelling**: Check the spelling of text entered. After selecting this option, input the text to be checked.
- **[A] Add Word to Dictionary**: Add a new word to the dictionary. You will be prompted to enter the word.
- **[Q] Quit**: Exit the program.

### Adding a New Dictionary

To add a new dictionary, ensure the file is in plain text format with one word per line. Use the **[L] Load Dictionary** option and specify the file path when prompted.

## Conclusion

The spell checker program demonstrates efficient spell checking and correction suggestion capabilities through the use of a custom hash table implementation and the Levenshtein distance algorithm. It is designed to be user-friendly and efficient, with optimizations aimed at maintaining high performance as the dictionary size increases.
