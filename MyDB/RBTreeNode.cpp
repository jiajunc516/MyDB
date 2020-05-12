#include "RBTreeNode.h"

RBTreeNode::RBTreeNode(int index)
    : color(red) {
    indexList.push_back(index);
}

RBTreeNode::RBTreeNode(int index, Color r) 
    : color(r) {
    indexList.push_back(index);
}

RBTreeNode::~RBTreeNode() {}

bool RBTreeNode::hasLeft() {
    return left != nullptr;
}

bool RBTreeNode::hasRight() {
    return right != nullptr;
}

RBTreeNode * RBTreeNode::getParent() {
    return parent;
}

RBTreeNode * RBTreeNode::getLeft() {
    return left;
}

RBTreeNode * RBTreeNode::getRight() {
    return right;
}

void RBTreeNode::setParent(RBTreeNode* node) {
    parent = node;
}

void RBTreeNode::setLeft(RBTreeNode* node) {
    left = node;
}

void RBTreeNode::setRight(RBTreeNode* node) {
    right = node;
}

Color RBTreeNode::getColor() {
    return color;
}

void RBTreeNode::setColor(Color c) {
    color = c;
}

bool RBTreeNode::isRed() {
    return color == red;
}
bool RBTreeNode::isBlack() {
    return color == black;
}

void RBTreeNode::push_back(int x) {
    indexList.push_back(x);
}

int RBTreeNode::front() {
    return indexList.front();
}

void RBTreeNode::printList() {
    for (auto it=indexList.cbegin(); it != indexList.cend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "| ";
}