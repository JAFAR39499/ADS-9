// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>

PMTree::PMTree(std::vector<char> input) {
    head = std::make_unique<TreeNode>('\0');
    construct(head.get(), input);
}

void PMTree::construct(TreeNode* node, const std::vector<char>& elems) {
    if (elems.empty()) return;

    for (size_t i = 0; i < elems.size(); ++i) {
        std::vector<char> rest;
        for (size_t j = 0; j < elems.size(); ++j) {
            if (j != i) rest.push_back(elems[j]);
        }
        
        auto child = std::make_unique<TreeNode>(elems[i]);
        construct(child.get(), rest);
        node->next.push_back(std::move(child));
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> collection;
    std::vector<char> current;
    tree.gatherAll(tree.head.get(), current, collection);
    return collection;
}

void PMTree::gatherAll(TreeNode* node, std::vector<char>& path,
                     std::vector<std::vector<char>>& storage) const {
    if (node->val != '\0') {
        path.push_back(node->val);
    }

    if (node->next.empty()) {
        storage.push_back(path);
    } else {
        for (const auto& child : node->next) {
            gatherAll(child.get(), path, storage);
        }
    }

    if (node->val != '\0') {
        path.pop_back();
    }
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    if (num <= 0 || num > static_cast<int>(all.size())) {
        return {};
    }
    return all[num - 1];
}

int PMTree::calcCount(TreeNode* node) const {
    if (node->next.empty()) return 1;
    
    int total = 0;
    for (const auto& child : node->next) {
        total += calcCount(child.get());
    }
    return total;
}

bool PMTree::locatePerm(TreeNode* node, int target, std::vector<char>& result) const {
    if (node->val != '\0') {
        result.push_back(node->val);
    }

    if (node->next.empty()) {
        return target == 1;
    }

    for (const auto& child : node->next) {
        int cnt = calcCount(child.get());
        if (target <= cnt) {
            return locatePerm(child.get(), target, result);
        }
        target -= cnt;
    }

    if (node->val != '\0') {
        result.pop_back();
    }
    return false;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> res;
    if (tree.locatePerm(tree.head.get(), num, res)) {
        return res;
    }
    return {};
}
