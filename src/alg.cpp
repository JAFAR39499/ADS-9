// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>

PermutationTree::PermutationTree(const std::vector<char>& elements) {
    root = std::make_unique<Node>('\0');
    buildTree(root.get(), elements);
}

void PermutationTree::buildTree(Node* parent, const std::vector<char>& elements) {
    if (elements.empty()) return;

    for (size_t i = 0; i < elements.size(); ++i) {
        std::vector<char> remaining;
        for (size_t j = 0; j < elements.size(); ++j) {
            if (j != i) remaining.push_back(elements[j]);
        }
        
        auto child = std::make_unique<Node>(elements[i]);
        buildTree(child.get(), remaining);
        parent->children.push_back(std::move(child));
    }
}

std::vector<std::vector<char>> PermutationTree::getAllPermutations() const {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    collectPermutations(root.get(), current, result);
    return result;
}

void PermutationTree::collectPermutations(Node* node, std::vector<char>& current,
                                       std::vector<std::vector<char>>& result) const {
    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPermutations(child.get(), current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<char> PermutationTree::getPermutationByIndexSlow(int index) const {
    auto all = getAllPermutations();
    if (index <= 0 || index > static_cast<int>(all.size())) {
        return {};
    }
    return all[index - 1];
}

int PermutationTree::countPermutations(Node* node) const {
    if (node->children.empty()) return 1;
    
    int count = 0;
    for (const auto& child : node->children) {
        count += countPermutations(child.get());
    }
    return count;
}

bool PermutationTree::findPermutation(Node* node, int remaining, 
                                    std::vector<char>& path) const {
    if (node->value != '\0') {
        path.push_back(node->value);
    }

    if (node->children.empty()) {
        return remaining == 1;
    }

    for (const auto& child : node->children) {
        int childCount = countPermutations(child.get());
        if (remaining <= childCount) {
            return findPermutation(child.get(), remaining, path);
        }
        remaining -= childCount;
    }

    if (node->value != '\0') {
        path.pop_back();
    }
    return false;
}

std::vector<char> PermutationTree::getPermutationByIndexFast(int index) const {
    std::vector<char> result;
    if (findPermutation(root.get(), index, result)) {
        return result;
    }
    return {};
}
