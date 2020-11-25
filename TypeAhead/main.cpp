#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>

const std::uint8_t RESERVED_ROWS = 3;

std::shared_ptr<WordTree> readDictionary(std::string filename);
void updateQuery(std::string& query);
void printRow(int row, std::string text);
void displayPredictions(const std::string query, const std::vector<std::string>& predictions);

int main()
{
    auto wordTree = readDictionary("dictionary.txt");

    std::string query = "";

    // Event-loop
    while (true)
    {
        updateQuery(query);

        std::uint8_t howMany = static_cast<std::uint8_t>(rlutil::trows()) - RESERVED_ROWS;
        auto predictions = wordTree->predict(query, howMany);

        displayPredictions(query, predictions);
    }
}

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it
        // exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send
        // isalpha an unsigned char or it will throw exception on negative values;
        // e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(),
                        [](unsigned char c) { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(),
                           [](char c) { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}

void updateQuery(std::string& query)
{
    int key = rlutil::getkey();
    if ((key == rlutil::KEY_BACKSPACE || key == rlutil::KEY_DELETE) && query.length())
    {
        query.pop_back();
    }
    else if (std::isalpha(static_cast<char>(key)))
    {
        query += static_cast<char>(std::tolower(key));
    }
}

void printRow(int row, std::string text)
{
    for (size_t i = 0; i < text.length(); ++i)
    {
        rlutil::locate(static_cast<int>(i) + 1, row);
        rlutil::setChar(text[i]);
    }
}

void displayPredictions(const std::string query, const std::vector<std::string>& predictions)
{
    rlutil::cls();

    printRow(1, query);
    printRow(3, "--- predictions ---");

    for (size_t i = 0; i < predictions.size(); ++i)
    {
        printRow(4 + static_cast<int>(i), predictions[i]);
    }

    // Put cursor back to user input
    rlutil::locate(1 + query.length(), 1);
}