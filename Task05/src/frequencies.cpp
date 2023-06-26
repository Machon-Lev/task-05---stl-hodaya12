#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdexcept>

/**
 * Prints the top numWords most frequent words from the wordCountMap.
 *
 * @param wordCountMap A multimap containing word frequencies.
 * @param numWords The number of top words to display.
 */
void printTopWords(const std::multimap<int, std::string, std::greater<int>> wordCountMap, int numWords) {
    int count = 0;
    std::cout << "Top " << numWords << " most frequent words:" << std::endl;
    for (const auto& pair : wordCountMap) {
        std::cout << pair.second << " (" << pair.first << " occurrences)" << std::endl;
        ++count;
        if (count == numWords) {
            break;
        }
    }
}

/**
 * Counts the occurrences of words in a file and prints the top numWords most frequent words.
 *
 * @param filename The name of the file to process.
 * @param numWords The number of top words to display.
 * @throws std::runtime_error if there is an error opening the file.
 */
void countWords(const std::string& filename, int numWords) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::multimap<int, std::string, std::greater<int>> wordCountMap;
    std::string word;
    std::multimap<int, std::string>::iterator it;
    std::pair<std::multimap<int, std::string>::iterator, std::multimap<int, std::string>::iterator> it1;
    while (file >> word) {
        bool found = false;
        for (const auto& pair : wordCountMap) {
            if (pair.second == word) {
                it1 = wordCountMap.equal_range(pair.first);
                found = true;
            }
        }
        if (found) {
            for (auto i = it1.first; i != it1.second; ++i)
                if (i->second == word)
                    it = i;
            wordCountMap.emplace(it->first + 1, it->second);
            wordCountMap.erase(it);

        }
        else {
            wordCountMap.emplace(1, word);
        }
    }

    file.close();

    printTopWords(wordCountMap, numWords);
}

/**
 * The entry point of the program.
 *
 * @returns 0 on success, 1 on error.
 */
int frequencies() {
    std::string filename;
    int numWords;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::cout << "Enter the number of top words to display: ";
    std::cin >> numWords;

    try {
        countWords(filename, numWords);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}