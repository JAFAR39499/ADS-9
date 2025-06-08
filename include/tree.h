#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>
#include <algorithm>

struct TreeNode {
    char value;
    std::vector<std::shared_ptr<TreeNode>> children;
    TreeNode(char val) : value(val) {}
};

class PMTree {
 private:
    std::shared_ptr<TreeNode> root;
    void buildTree(std::shared_ptr<TreeNode> node, std::vector<char> elements);
    void getAllPermsHelper(std::shared_ptr<TreeNode> node, std::vector<char>& current,
                         std::vector<std::vector<char>>& result) const;
    void getPermByNumHelper(std::shared_ptr<TreeNode> node, int& remaining, 
                          std::vector<char>& result) const;
    bool getPermByNumFastHelper(std::shared_ptr<TreeNode> node, int remaining,
                              std::vector<char>& result, int& total) const;

 public:
    explicit PMTree(const std::vector<char>& elements);
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPerm1(int num) const;
    std::vector<char> getPerm2(int num) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
