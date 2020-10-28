#include "WordTree.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

TreeNode::TreeNode()
{
    endOfWord = false;
    letter = '0';
}

WordTree::WordTree()
{
    root = std::make_shared<TreeNode>();
    numWords = 0;
    numNodes = 0;
}

void WordTree::add(std::string word)
{
    if (!word.empty())
    {
        if (!find(word))
        {
            numWords = numWords + 1;
        }
        auto currentNode = root; // starting at the top of the tree
        for (int i = 0; i < word.size(); ++i)
        {                                   // look at each letter of the word
            int currentChar = word[i] - 97; // convert the current letter to a number 1-26
            if (currentNode->children[currentChar] != nullptr)
            {                                                     // if the letter exists
                currentNode = currentNode->children[currentChar]; // make the new current node that one
            }
            else
            {                                                                      // if the letter node does not exist
                currentNode->children[currentChar] = std::make_shared<TreeNode>(); // create the node
                currentNode->children[currentChar]->letter = word[i];
                currentNode = currentNode->children[currentChar]; // make that node our current node
            }
        }
        currentNode->endOfWord = true; // once we have reached the end of the word,
                                       // mark the current node as the end of the word
    }
}

bool WordTree::find(std::string word)
{
    bool found = false;      // by default, the word is not found
    auto currentNode = root; // starting at the top of the tree
    for (int i = 0; i < word.size(); ++i)
    {                                   // look at each letter of the word
        int currentChar = word[i] - 97; // convert the current letter to a number 1-26
        if ((currentNode)->children[currentChar] != nullptr)
        {                                                     // if the letter exists
            currentNode = currentNode->children[currentChar]; // make the new current node that one
        }
    }
    if (currentNode->endOfWord && currentNode->letter==word.back())
    {
        found = true;
    }
    return found;
}

std::size_t WordTree::size()
{
    return numWords;
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> words;
    if (!partial.empty())
    {

        auto currentNode = root;                   // starting with the root
        for (int i = 0; i < partial.length(); ++i) // for each letter of the word
        {
            int currentChar = partial[i] - 97;                 // convert that letter to a number
            if (currentNode->children[currentChar] != nullptr) // and if that letter exists in the child array
            {
                currentNode = currentNode->children[currentChar]; // make that letter child node the new current node
            }
        }
        std::queue<std::shared_ptr<TreeNode>> nodes;
        std::queue<std::string> wordsSoFar;
        std::string word = partial;
        nodes.push(currentNode);
        wordsSoFar.push(word);
        while (!nodes.empty()) // while there are still letters to look through
        {
            auto node = nodes.front(); // take the first node on the queue
            nodes.pop();
            std::string currentWord = wordsSoFar.front();
            wordsSoFar.pop();
            if (node->endOfWord) // if the node exists and is the end of the word
            {
                if (currentWord != partial)
                {
                    words.push_back(currentWord);
                }
                //add the word to the list here
                if (words.size() >= howMany)
                {          // if there are the amount of words wanted
                    break; // we can stop searching
                }
            }
            for (int i = 0; i < node->children.size(); ++i) // for each child in the node's children list
            {
                if (node->children[i] != nullptr)
                {
                    nodes.push(node->children[i]); // add the child to the queue
                    char currentChar = static_cast<char>(i + 97);
                    std::string aWord = currentWord + currentChar;
                    wordsSoFar.push(aWord);
                }
            }
        }
    }
    return words; // return the list of words predicted
}