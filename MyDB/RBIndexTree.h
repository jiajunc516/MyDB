#pragma once
#include <queue>
#include <vector>
#include <memory>

#include "RBTreeNode.h"

class RBIndexTree {
private:
    RBTreeNode * root;
    std::vector<std::unique_ptr<char[]>> * column;

    void deleteTree();
    int compare(const int left, const int right);

    RBTreeNode * insert(const int index, RBTreeNode * node);
    void balance(RBTreeNode * son, RBTreeNode * parent);
    void RotateR(RBTreeNode * node);
    void RotateL(RBTreeNode * node);
public:
    RBIndexTree(std::vector<std::unique_ptr<char[]>> * v);
    ~RBIndexTree();

    void put(const int index);
    void print();
};

