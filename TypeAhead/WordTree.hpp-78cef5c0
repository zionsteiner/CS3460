/*
 * WordTree is a class that stores a dictionary of words in an efficiently
 * searchable format
 */

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class WordTree
{
  private:
    struct TreeNode
    {
        bool endOfWord = false;
        std::array<std::shared_ptr<TreeNode>, 26> children;
    };

    std::shared_ptr<TreeNode> m_root;
    std::size_t m_size;

    std::size_t calcLetterIndex(char c);
    char indexToLetter(std::size_t i);

  public:
    WordTree();

    // Add word to tree
    void add(std::string word);
    // Returns true if word is in tree
    bool find(std::string word);
    // Returns vector of howMany predictions given partial input
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    // Returns number of words in tree
    std::size_t size();

    using NodeWithString = std::pair<std::shared_ptr<TreeNode>, std::string>;
};