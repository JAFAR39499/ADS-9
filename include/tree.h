// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

struct TreeNode {
    char value;
    std::vector<std::shared_ptr<TreeNode>> children;
    TreeNode(char v) : value(v) {}
};

class PMTree {
 private:
    std::shared_ptr<TreeNode> root;
    void buildTree(std::shared_ptr<TreeNode> node, const std::vector<char>& elements);
    void getAllPermsHelper(std::shared_ptr<TreeNode> node, std::vector<char>& current,
                         std::vector<std::vector<char>>& result) const;
    void getPermHelper1(std::shared_ptr<TreeNode> node, std::vector<char>& current,
                      int& target, int& currentNum, std::vector<char>& result) const;
    bool getPermHelper2(std::shared_ptr<TreeNode> node, std::vector<char>& current,
                      int& remaining, std::vector<char>& result) const;
    int factorial(int n) const;

 public:
    explicit PMTree(const std::vector<char>& elements);
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPerm1(int num) const;
    std::vector<char> getPerm2(int num) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
