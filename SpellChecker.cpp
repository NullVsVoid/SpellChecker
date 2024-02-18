//
// Copyright Caiden Sanders - All Rights Reserved
//
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
//
// Written by Caiden Sanders <work.caidensanders@gmail.com>, February 17, 2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "./CTL/include/hashtable/hashtable.hpp"

// Function prototypes.
int levenshtein_distance(const std::string& word1, const std::string& word2);
CTL::HashTable<std::string, bool> load_dictionary(const std::string& filename);
std::vector<std::string> spell_check(
    const std::string& text, const std::unordered_set<std::string>& dictionary);
std::vector<std::pair<std::string, std::string>> suggest_corrections(
    const std::vector<std::string>& misspelled,
    const std::unordered_set<std::string>& dictionary);
void print_results(
    const std::vector<std::string>& misspelled,
    const std::vector<std::pair<std::string, std::string>>& corrections);
void add_word_to_dictionary(CTL::HashTable<std::string, bool>& dictionary);

/**
 * Implementation of the Levenshtein distance algorithm to calculate the
 * minimum number of single-character edits (insertions, deletions, or
 * substitutions) required to change one word into another.
 *
 * @param word1 The first word.
 * @param word2 The second word.
 * @return The Levenshtein distance between the two words.
 * @see https://en.wikipedia.org/wiki/Levenshtein_distance
 */
int levenshtein_distance(const std::string& word1, const std::string& word2) {
    // Create a 2D array to store the distances between prefixes of the two
    // words.
    std::vector<std::vector<int>> distances(word1.size() + 1,
                                            std::vector<int>(word2.size() + 1));

    // Initialize the first row and column of the array with the distances from
    // the empty string to each prefix of the words.
    for (int i = 0; i <= word1.size(); i++) {
        distances[i][0] = i;
    }
    for (int j = 0; j <= word2.size(); j++) {
        distances[0][j] = j;
    }

    // Calculate the minimum distance between prefixes of the words.
    for (int i = 1; i <= word1.size(); i++) {
        for (int j = 1; j <= word2.size(); j++) {
            if (word1[i - 1] == word2[j - 1]) {
                distances[i][j] = distances[i - 1][j - 1];
            } else {
                distances[i][j] =
                    1 + std::min({distances[i - 1][j], distances[i][j - 1],
                                  distances[i - 1][j - 1]});
            }
        }
    }

    // The Levenshtein distance is the value in the bottom-right corner of the
    // array.
    return distances[word1.size()][word2.size()];
}

/**
 * Load a dictionary of words from a file into a hash table.
 *
 * @param filename The name of the file containing the dictionary.
 * @return A hash table containing the words from the dictionary.
 */
CTL::HashTable<std::string, bool> load_dictionary(const std::string& filename) {
    CTL::HashTable<std::string, bool> dictionary(100);
    std::ifstream file;

    file.open(filename);
    if (!file) {
        std::cerr << "Error: could not open " << filename << std::endl;
        return dictionary;
    }

    std::string word;
    while (file >> word) {
        dictionary.insert(word, true);
    }

    file.close();

    return dictionary;
}

/**
 * Add a new word to the dictionary stored in the hash table.
 *
 * @param dictionary The hash table containing the dictionary of words.
 */
void add_word_to_dictionary(CTL::HashTable<std::string, bool>& dictionary) {
    std::string new_word;

    std::cout << "Enter the word to add to the dictionary: ";
    std::getline(std::cin, new_word);

    auto result = dictionary.insert(new_word, true);

    if (result.second) {
        std::cout << "Word added successfully." << std::endl;
    } else {
        std::cout << "Word already exists in the dictionary." << std::endl;
    }
}

/**
 * Take a string of text as input and check each word in the text against the
 * words in the dictionary stored in the hash table. Identify any words that
 * are not found in the dictionary and display them as "mispelled".
 *
 * @param text The string of text to check.
 * @param dictionary The hash table containing the dictionary of words.
 * @return A vector of misspelled words.
 */
std::vector<std::string> spell_check(
    const std::string& text,
    const CTL::HashTable<std::string, bool>& dictionary) {
    std::vector<std::string> misspelled;
    std::string word;
    std::string current_word;
    std::istringstream textStream(text);

    while (textStream >> word) {
        if (!dictionary.get(word)) {
            misspelled.push_back(word);
        }
    }

    return misspelled;
}

/**
 * Based off of a vector of mispelled words and a dictionary stored in a
 * hash table, suggest a correction for each misspelled word using the
 * Levenshtein distance algorithm. Only include words that are likely
 * to be mispelled and have a distance that is related to the size
 * of the word.
 *
 * @param misspelled A vector of misspelled words.
 * @param dictionary The hash table containing the dictionary of words.
 * @return A vector of pairs, where each pair contains a misspelled word and
 *         its suggested correction.
 */
std::vector<std::pair<std::string, std::string>> suggest_corrections(
    const std::vector<std::string>& misspelled,
    const CTL::HashTable<std::string, bool>& dictionary) {
    std::vector<std::pair<std::string, std::string>> corrections;

    for (const auto& word : misspelled) {
        std::string best_match;
        int best_distance = std::numeric_limits<int>::max();

        for (const auto& table : dictionary.get_table()) {
            for (const auto& pair : table) {
                std::string entry = pair.first;
                int distance = levenshtein_distance(word, entry);

                if (distance < best_distance) {
                    best_distance = distance;
                    best_match = entry;
                }
            }
        }

        if (best_distance <= 2 && !best_match.empty()) {
            corrections.push_back({word, best_match});
        }
    }

    return corrections;
}

/**
 * Print the results of the spell check, including the misspelled words and
 * their suggested corrections.
 *
 * @param misspelled A vector of misspelled words.
 * @param corrections A vector of pairs, where each pair contains a
 * misspelled word and its suggested correction.
 */
void print_results(
    const std::vector<std::string>& misspelled,
    const std::vector<std::pair<std::string, std::string>>& corrections) {
    std::cout << "\n";

    if (misspelled.empty()) {
        std::cout << "No misspelled words found." << std::endl;
    } else {
        std::cout << "Misspelled words:" << std::endl;
        for (const auto& word : misspelled) {
            std::cout << word << std::endl;
        }
    }

    if (!corrections.empty()) {
        std::cout << "Corrections:" << std::endl;
        for (const auto& correction : corrections) {
            std::cout << correction.first << " -> " << correction.second
                      << std::endl;
        }
    }
}

/**
 * Entry point of the program. Displays a UI to the user asking to input a
 * file name and a string of text to spell check. The program then reads the
 * dictionary from the file, checks the text for misspelled words, and
 * suggests corrections for any misspelled words found. The user can add new
 * words to the dictionary, and the hash table containing the dictionary
 * will be updated.
 */
int main() {
    CTL::HashTable<std::string, bool> dictionary;
    std::string dictionary_filename, text, choice;

    while (true) {
        std::cout << "\n---- Spell Checker Menu ----\n"
                  << "[L] Load dictionary\n"
                  << "[C] Check spelling\n"
                  << "[A] Add word to dictionary\n"
                  << "[Q] Quit\n"
                  << "Choose an option: ";
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == "L" || choice == "l") {
            std::cout << "\nEnter the name of the dictionary file: ";
            std::getline(std::cin, dictionary_filename);
            dictionary = load_dictionary(dictionary_filename);

            if (dictionary.empty()) {
                std::cerr << "\nFailed to load dictionary.\n";
            } else {
                std::cout << "\nDictionary loaded successfully.\n";
            }
        } else if (choice == "C" || choice == "c") {
            if (dictionary.empty()) {
                std::cout << "\nPlease load a dictionary first.\n";
                continue;
            }
            std::cout << "\nEnter the text to spell check:\n";
            std::getline(std::cin, text);
            auto misspelled = spell_check(text, dictionary);
            auto corrections = suggest_corrections(misspelled, dictionary);
            print_results(misspelled, corrections);
        } else if (choice == "A" || choice == "a") {
            add_word_to_dictionary(dictionary);
        } else if (choice == "Q" || choice == "q") {
            std::cout << "\nExiting program.\n";
            break;
        } else {
            std::cout << "\nInvalid option. Please try again.\n";
        }
    }

    return 0;
}