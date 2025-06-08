// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
 private:
    struct TreeNode {
        char val;
        std::vector<std::unique_ptr<TreeNode>> next;
        explicit TreeNode(char v) : val(v) {}
    };
    
    std::unique_ptr<TreeNode> head;
    void construct(TreeNode* node, const std::vector<char>& elems);
    void gatherAll(TreeNode* node, std::vector<char>& path,
                 std::vector<std::vector<char>>& storage) const;
    int calcCount(TreeNode* node) const;
    bool locatePerm(TreeNode* node, int target, std::vector<char>& result) const;

 public:
    explicit PMTree(std::vector<char> input);
    ~PMTree() = default;
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
