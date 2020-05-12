#pragma once
#include <list>
#include <iostream>

enum Color {red, black};

class RBTreeNode {
private:
    std::list<int> indexList;
    Color color;
    RBTreeNode * parent;
    RBTreeNode * left;
    RBTreeNode * right;

public:
    RBTreeNode(int index);
    RBTreeNode(int index, Color r);
    ~RBTreeNode();
    
    bool hasLeft();
    bool hasRight();
    RBTreeNode * getParent();
    RBTreeNode * getLeft();
    RBTreeNode * getRight();
    void setParent(RBTreeNode * node);
    void setLeft(RBTreeNode * node);
    void setRight(RBTreeNode * node);
    Color getColor();
    void setColor(Color c);
    void push_back(int x);
    int front();
    bool isRed();
    bool isBlack();
    void printList();
};

