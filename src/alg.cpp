// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream input_stream(filename);
    if (!input_stream.is_open()) {
        std::cerr << "Error: opening file " << filename << std::endl;
        return;
    }

    std::string current_token = "";
    char single_char;

    while (input_stream.get(single_char)) {
        if (std::isalpha(static_cast<unsigned char>(single_char))) {
            current_token += static_cast<char>(std::tolower(static_cast<unsigned char>(single_char)));
        } else {
            if (!current_token.empty()) {
                tree.insert(current_token);
                current_token.clear();
            }
        }
    }
    if (!current_token.empty()) {
        tree.insert(current_token);
    }
    input_stream.close();
}

void printFreq(BST<std::string>& tree) {
    tree.printSortedByFrequency();
}
