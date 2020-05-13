#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

// Abandon IndexNdoe. Use std::vector instead.

// struct IndexNode {
//     int index;
//     IndexNode * next;
//     IndexNode * prev;
//     IndexNode(int i, IndexNode * next = nullptr, IndexNode * prev = nullptr);
// };

class TreeNode {
private:
    // IndexNode * head;
    // IndexNode * tail;
    std::vector<size_t> indexList;
    int height;
    TreeNode * left = nullptr;
    TreeNode * right = nullptr;

    // void initIndexList();
    // void deleteIndexList();
public:
    TreeNode(size_t index);
    ~TreeNode();

    bool hasLeft();
    bool hasRight();
    TreeNode * getLeft();
    TreeNode * getRight();
    void setLeft(TreeNode * node);
    void setRight(TreeNode * node);
    int getHeight();
    void setHeight(int h);
    void updateHeight();
    size_t front();
    void push_back(size_t x);
    void pop_back();
    std::vector<size_t> * getIndexList();
    void printList();
};