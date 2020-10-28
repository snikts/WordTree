#include <array>
#include <iostream>
#include <vector>

class TreeNode
{

  public:
    TreeNode();
    bool endOfWord;
    bool discovered;
    char letter;

    std::array<std::shared_ptr<TreeNode>, 26> children;
};

class WordTree
{

  public:
    WordTree();
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size();
    std::shared_ptr<TreeNode> root;
    long numWords;
    long numNodes;

  private:
    int dfs(std::shared_ptr<TreeNode> currentNode);
};
