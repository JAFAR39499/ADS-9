// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include "tree.h"

int main() {
    std::vector<char> input1 = {'1', '3', '5', '7'};
    PMTree tree1(input1);

    std::vector<char> result1 = getPerm1(tree1, 1);
    std::vector<char> result2 = getPerm2(tree1, 1);

    std::cout << "Permutation 1 (getPerm1): ";
    for (char c : result1) {
        std::cout << c;
    }
    std::cout << std::endl;

    std::cout << "Permutation 1 (getPerm2): ";
    for (char c : result2) {
        std::cout << c;
    }
    std::cout << std::endl;

    std::vector<char> input2 = {'1', '5', '7', '5'};
    PMTree tree2(input2);

    std::vector<char> result3 = getPerm1(tree2, 2);
    std::vector<char> result4 = getPerm2(tree2, 2);

    std::cout << "Permutation 2 (getPerm1): ";
    for (char c : result3) {
        std::cout << c;
    }
    std::cout << std::endl;

    std::cout << "Permutation 2 (getPerm2): ";
    for (char c : result4) {
        std::cout << c;
    }
    std::cout << std::endl;

    return 0;
}
