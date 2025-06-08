// Copyright 2022 NNTU-CS
#include <algorithm>
#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include "tree.h"

PMTree::~PMTree() {
    for (PMTree* branch : branches) {
        delete branch;
    }
}

PMTree::PMTree(std::vector<char> elements) : nodeValue('\0'), branches({}) {
    if (elements.empty()) return;

    for (size_t idx = 0; idx < elements.size(); ++idx) {
        std::vector<char> remainingElements;
        for (size_t j = 0; j < elements.size(); ++j) {
            if (idx != j) {
                remainingElements.push_back(elements[j]);
            }
        }
        PMTree* newBranch = new PMTree(remainingElements);
        newBranch->nodeValue = elements[idx];
        branches.push_back(newBranch);
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> allPerms;

    std::function<void(PMTree*, std::vector<char>)> collectPerms =
        [&](PMTree* currentNode, std::vector<char> currentPerm) {
        if (currentNode->branches.empty()) {
            allPerms.push_back(currentPerm);
            return;
        }

        for (PMTree* branch : currentNode->branches) {
            std::vector<char> nextPerm = currentPerm;
            nextPerm.push_back(branch->nodeValue);
            collectPerms(branch, nextPerm);
        }
    };

    collectPerms(&tree, {});
    return allPerms;
}

std::vector<char> getPerm1(PMTree& tree, int index) {
    std::vector<std::vector<char>> allPerms = getAllPerms(tree);
    if (index <= 0 || index > allPerms.size()) {
        return {};
    }
    return allPerms[index - 1];
}

std::vector<char> getPerm2(PMTree& tree, int index) {
    std::vector<char> resultPerm;
    std::function<bool(PMTree*, int, std::vector<char>&)> findPerm =
        [&](PMTree* node, int remaining, std::vector<char>& perm) -> bool {
        if (node->branches.empty()) {
            return remaining == 1;
        }

        for (PMTree* branch : node->branches) {
            std::function<int(PMTree*)> countPerms =
                [&](PMTree* subTree) -> int {
                if (subTree->branches.empty()) {
                    return 1;
                }
                int total = 0;
                for (PMTree* subBranch : subTree->branches) {
                    total += countPerms(subBranch);
                }
                return total;
            };

            int branchPermCount = countPerms(branch);

            if (remaining <= branchPermCount) {
                perm.push_back(branch->nodeValue);
                if (findPerm(branch, remaining, perm)) {
                    return true;
                }
                return false;
            }
            remaining -= branchPermCount;
        }
        return false;
    };

    if (!findPerm(&tree, index, resultPerm)) {
        return {};
    }
    return resultPerm;
}
