// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Node {
 public:
    T word;
    int quantity;
    Node* left_node;
    Node* right_node;

    explicit Node(T value)
        : word(value), quantity(1), left_node(nullptr), right_node(nullptr) {}
};

template <typename T>
class BST {
 private:
    Node<T>* root_node;

    void insertNode(Node<T>*& current, T value) {
        if (!current) {
            current = new Node<T>(value);
        } else if (value == current->word) {
            current->quantity++;
        } else if (value < current->word) {
            insertNode(current->left_node, value);
        } else {
            insertNode(current->right_node, value);
        }
    }

    int calculateDepth(Node<T>* current) const {
        if (!current) return -1;
        int left_depth = calculateDepth(current->left_node);
        int right_depth = calculateDepth(current->right_node);
        return 1 + (left_depth > right_depth ? left_depth : right_depth);
    }

    int searchWord(Node<T>* current, T value) const {
        if (!current) return 0;
        if (value == current->word) return current->quantity;
        return (value < current->word) ? searchWord(current->left_node, value)
                                       : searchWord(current->right_node, value);
    }

    void collectNodes(Node<T>* current, std::vector<Node<T>*>& elements) const {
        if (!current) return;
        collectNodes(current->left_node, elements);
        elements.push_back(current);
        collectNodes(current->right_node, elements);
    }

    void destroyTree(Node<T>* current) {
        if (current) {
            destroyTree(current->left_node);
            destroyTree(current->right_node);
            delete current;
        }
    }

 public:
    BST() : root_node(nullptr) {}
    ~BST() { destroyTree(root_node); }

    void insert(T value) { insertNode(root_node, value); }
    int search(T value) const { return searchWord(root_node, value); }
    int depth() const { return calculateDepth(root_node); }

    void printSortedByFrequency() {
        std::vector<Node<T>*> elements;
        collectNodes(root_node, elements);

        std::sort(elements.begin(), elements.end(),
            [](const Node<T>* first, const Node<T>* second) {
                if (first->quantity != second->quantity) {
                    return first->quantity > second->quantity;
                }
                return first->word < second->word;
            });

        std::ofstream out_file("freq.txt");
        for (const auto& node : elements) {
            std::cout << node->word << ": " << node->quantity << "\n";
            if (out_file.is_open()) {
                out_file << node->word << ": " << node->quantity << "\n";
            }
        }
    }
};

#endif  // INCLUDE_BST_H_
