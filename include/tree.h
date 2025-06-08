// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <string>

class PermutationTree {
 public:
    explicit PermutationTree(std::vector<char> elements);
    ~PermutationTree();
    char nodeValue;
    std::vector<PermutationTree*> branches;
};

std::vector<std::vector<char>> getAllPerms(PermutationTree& tree);
std::vector<char> getPerm1(PermutationTree& tree, int index);
std::vector<char> getPerm2(PermutationTree& tree, int index);

#endif  // INCLUDE_TREE_H_
