// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PermutationTree {
 private:
    struct Node {
        char value;
        std::vector<std::unique_ptr<Node>> children;
        explicit Node(char v) : value(v) {}
    };

    std::unique_ptr<Node> root;
    void buildTree(Node* parent, const std::vector<char>& elements);
    void collectPermutations(Node* node, std::vector<char>& current,
                           std::vector<std::vector<char>>& result) const;
    int countPermutations(Node* node) const;
    bool findPermutation(Node* node, int remaining, std::vector<char>& path) const;

 public:
    explicit PermutationTree(const std::vector<char>& elements);
    std::vector<std::vector<char>> getAllPermutations() const;
    std::vector<char> getPermutationByIndexSlow(int index) const;
    std::vector<char> getPermutationByIndexFast(int index) const;
};

#endif  // INCLUDE_TREE_H_
