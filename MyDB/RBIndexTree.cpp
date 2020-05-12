#include "RBIndexTree.h"

void RBIndexTree::deleteTree() {
    std::queue<RBTreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        RBTreeNode* t = queue.front();
        if (t->hasLeft())
            queue.push(t->getLeft());
        if (t->hasRight())
            queue.push(t->getRight());
        delete t;
        queue.pop();
    }
}

RBIndexTree::RBIndexTree(std::vector<std::unique_ptr<char[]>> * v)
    : column(v) {
}

RBIndexTree::~RBIndexTree() {
    deleteTree();
}

void RBIndexTree::print() {
    std::queue<RBTreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        int size = queue.size();
        for (int i=0; i<size; ++i) {
            RBTreeNode* node = queue.front();
            queue.pop();
            if (node->hasLeft())
                queue.push(node->getLeft());
            if (node->hasRight())
                queue.push(node->getRight());
            node->printList();
        }
        std::cout << std::endl;
    }
}

int RBIndexTree::compare(const int left, const int right) {
    return strcmp(column->at(left).get(), column->at(right).get());
}

void RBIndexTree::put(const int index) {
    root = insert(index, root);
}

RBTreeNode * RBIndexTree::insert(const int index, RBTreeNode* node) {
    if (node == nullptr) {
        return new RBTreeNode(index, black);
    }

    RBTreeNode* curr = node;
    RBTreeNode* parent = curr->getParent();
    bool isleft;

    while (curr) {
        int cmp = compare(index, curr->front());
        if (cmp < 0) {
            parent = curr;
            curr = curr->getLeft();
            isleft = true;
        }
        else if (cmp > 0) {
            parent = curr;
            curr = curr->getRight();
            isleft = false;
        }
        else {
            curr->push_back(index);
            return node;
        }
    }
    
    curr = new RBTreeNode(index);
    if (isleft) {
        parent->setLeft(curr);
        curr->setParent(parent);
    }
    else {
        parent->setRight(curr);
        curr->setParent(parent);
    }

    balance(curr, parent);
    node->setColor(black);
    return node;
}

void RBIndexTree::balance(RBTreeNode * son, RBTreeNode * parent) {
    while (parent && parent->isRed()) {
        RBTreeNode* gParent = parent->getParent();
        
        // Left subtree
        if (parent == gParent->getLeft()) {
            RBTreeNode* uncle = gParent->getRight();
            // Uncle exists And uncle is red
            if (uncle != nullptr && uncle->isRed()) {
                parent->setColor(black);
                uncle->setColor(black);
                gParent->setColor(red);
                son = gParent;
                parent = son->getParent();
            }
            else { // Uncle does not exist Or Uncle is black

            }
        }
    }
}

void RBIndexTree::RotateR(RBTreeNode * node) {

}

void RBIndexTree::RotateL(RBTreeNode * node) {

}