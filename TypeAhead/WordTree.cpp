#include "WordTree.hpp"
#include <queue>

WordTree::WordTree()
{
    m_root = std::make_shared<TreeNode>();
    m_size = 0;
}

void WordTree::add(std::string word)
{
    // Exit if word already inserted
    if (find(word))
    {
        return;
    }

    // Traverse
    auto currNode = m_root;
    for (size_t i = 0; i < word.length(); ++i)
    {
        size_t currIndex = calcLetterIndex(word[i]);

        // Make new node if necessary
        if (!currNode->children[currIndex])
        {
            currNode->children[currIndex] = std::make_shared<TreeNode>();
        }

        currNode = currNode->children[currIndex];

        // Mark the last node as endOfWord
        if (i == word.length() - 1)
        {
            currNode->endOfWord = true;
            m_size++;
        }
    }
}

bool WordTree::find(std::string word)
{
    // Return false on empty string
    if (!word.length())
    {
        return false;
    }

    auto currNode = m_root;
    for (size_t i = 0; i < word.length(); ++i)
    {
        size_t currIndex = calcLetterIndex(word[i]);
        currNode = currNode->children[currIndex];

        if (!currNode)
        {
            return false;
        }
    }

    if (currNode->endOfWord)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> predictions;

    // No prediction for empty string
    if (!partial.length())
    {
        return predictions;
    }

    // Find partial node
    auto currNode = m_root;
    for (size_t i = 0; i < partial.length(); ++i)
    {
        size_t currIndex = calcLetterIndex(partial[i]);
        currNode = currNode->children[currIndex];

        // Partial is not in tree, exit
        if (!currNode)
        {
            return predictions;
        }
    }

    // BFS for predictions
    std::queue<NodeWithString> q;
    q.emplace(currNode, partial);
    while (predictions.size() < howMany && q.size())
    {
        NodeWithString currNodeWithString = q.front();
        q.pop();

        currNode = currNodeWithString.first;
        auto currPartial = currNodeWithString.second;
        for (size_t i = 0; i < currNode->children.size(); ++i)
        {
            if (currNode->children[i])
            {
                auto newPartial = currPartial + indexToLetter(i);

                // Add prediction
                if (currNode->children[i]->endOfWord)
                {
                    predictions.push_back(newPartial);
                }

                // Add node to queue
                q.emplace(currNode->children[i], newPartial);

                if (q.size() == howMany)
                {
                    break;
                }
            }
        }
    }

    return predictions;
}

std::size_t WordTree::size()
{
    return m_size;
}

std::size_t WordTree::calcLetterIndex(char c)
{
    return static_cast<std::size_t>(c - 'a');
}

char WordTree::indexToLetter(std::size_t i)
{
    return static_cast<char>(i) + 'a';
}