// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) return;
    
    root = std::make_shared<TreeNode>('\0');
    buildTree(root, elements);
}

void PMTree::buildTree(std::shared_ptr<TreeNode> node, const std::vector<char>& elements) {
    for (char elem : elements) {
        auto child = std::make_shared<TreeNode>(elem);
        node->children.push_back(child);
        
        std::vector<char> remaining;
        for (char e : elements) {
            if (e != elem) remaining.push_back(e);
        }
        
        if (!remaining.empty()) {
            buildTree(child, remaining);
        }
    }
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    if (!root) return result;
    
    std::vector<char> current;
    for (const auto& child : root->children) {
        getAllPermsHelper(child, current, result);
    }
    return result;
}

void PMTree::getAllPermsHelper(std::shared_ptr<TreeNode> node, std::vector<char>& current,
                             std::vector<std::vector<char>>& result) const {
    current.push_back(node->value);
    
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            getAllPermsHelper(child, current, result);
        }
    }
    
    current.pop_back();
}

int PMTree::factorial(int n) const {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::vector<char> PMTree::getPerm1(int num) const {
    std::vector<char> result;
    if (num < 1 || !root) return result;
    
    int remaining = num - 1;
    for (const auto& child : root->children) {
        if (remaining < 0) break;
        getPermByNumHelper(child, remaining, result);
    }
    
    return result;
}

void PMTree::getPermByNumHelper(std::shared_ptr<TreeNode> node, int& remaining,
                              std::vector<char>& result) const {
    result.push_back(node->value);
    
    if (node->children.empty()) {
        if (remaining == 0) return;
        remaining--;
    } else {
        for (const auto& child : node->children) {
            if (remaining < 0) break;
            getPermByNumHelper(child, remaining, result);
        }
    }
    
    if (remaining >= 0) {
        result.pop_back();
    }
}

int PMTree::countPermutations(std::shared_ptr<TreeNode> node) const {
    if (node->children.empty()) {
        return 1;
    }
    
    int count = 0;
    for (const auto& child : node->children) {
        count += countPermutations(child);
    }
    return count;
}

std::vector<char> PMTree::getPerm2(int num) const {
    std::vector<char> result;
    if (num < 1 || !root) return result;
    
    int total = 0;
    for (const auto& child : root->children) {
        if (getPermByNumFastHelper(child, num - 1, result, total)) {
            return result;
        }
    }
    
    return {};
}

bool PMTree::getPermByNumFastHelper(std::shared_ptr<TreeNode> node, int remaining,
                                  std::vector<char>& result, int& total) const {
    result.push_back(node->value);
    
    if (node->children.empty()) {
        if (total == remaining) {
            return true;
        }
        total++;
    } else {
        for (const auto& child : node->children) {
            if (getPermByNumFastHelper(child, remaining, result, total)) {
                return true;
            }
        }
    }
    
    result.pop_back();
    return false;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPerm1(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPerm2(num);
}
