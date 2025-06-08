// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <string>

class PMTree {
 public:
    explicit PMTree(std::vector<char> elements);
    ~PMTree();
    char nodeValue;
    std::vector<PMTree*> branches;
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int index);
std::vector<char> getPerm2(PMTree& tree, int index);

#endif  // INCLUDE_TREE_H_
