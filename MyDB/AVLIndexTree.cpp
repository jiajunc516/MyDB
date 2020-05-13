#include "AVLIndexTree.h"

void AVLIndexTree::deleteTree() {
    std::queue<TreeNode*> queue;
    if (root != nullptr)
        queue.push(root);
    while (!queue.empty()) {
        TreeNode* t = queue.front();
        if (t->hasLeft())
            queue.push(t->getLeft());
        if (t->hasRight())
            queue.push(t->getRight());
        delete t;
        queue.pop();
    }
}

AVLIndexTree::AVLIndexTree(std::vector<std::unique_ptr<char[]>> * v) 
    : column(v) {
    // balanceTime(0);
}

AVLIndexTree::~AVLIndexTree() {
    deleteTree();
}

int AVLIndexTree::height(TreeNode* node) {
    if (node == nullptr)
        return 0;
    return node->getHeight();
}
int AVLIndexTree::height_diff(TreeNode* node) {
    return height(node->getLeft()) - height(node->getRight());
}

int AVLIndexTree::compare(const size_t left, const size_t right) {
    return compareChar(column->at(left).get(), column->at(right).get());
}

int AVLIndexTree::compare(const size_t dest, const char * target) {
    return compareChar(column->at(dest).get(), target);
}

int AVLIndexTree::compareChar(const char* left, const char* right) {
    // Manual Compare
    // int i = 0, j = 0;
    // while (left[i] != '\0' && right[j] != '\0') {
    //     if (left[i] != right[j])
    //         return left[i] - right[j];
    //     ++i;
    //     ++j;
    // }
    // if (left[i] != '\0')
    //     return 1;
    // if (right[j] != '\0')
    //     return -1;
    // return 0;

    // Build-in compare
    // std::cout << "Comparing: " << left << ", " << right << std::endl;
    return strcmp(left, right);
}

void AVLIndexTree::put(const size_t index) {
    collide = false;
    root = insert(index, root);
}

TreeNode * AVLIndexTree::insert(const size_t index, TreeNode* node) {
    if (node == nullptr)
        return new TreeNode(index);
    int cmp = compare(index, node->front());
    if (cmp < 0) {
        node->setLeft(insert(index, node->getLeft()));
    }
    else if (cmp > 0) {
        node->setRight(insert(index, node->getRight()));
    }
    else {
        collide = true;
        node->push_back(index);
        return node;
    }
    if (!collide) {
        node->updateHeight();
        node = balance(node);
    }
    return node;
}

TreeNode * AVLIndexTree::balance(TreeNode* node) {
    // auto start = std::chrono::steady_clock::now();
    int h_dif = height_diff(node);
    if (h_dif > 1) {
        if (height_diff(node->getLeft()) > 0)
            node = LL_rotate(node);
        else
            node = LR_rotate(node);
    }
    else if (h_dif < -1) {
        if (height_diff(node->getRight()) < 0)
            node = RR_rotate(node);
        else
            node = RL_rotate(node);
    }
    // auto end = std::chrono::steady_clock::now();
    // balanceTime += (end - start);
    return node;
}

TreeNode * AVLIndexTree::RR_rotate(TreeNode* parent) {
    //  y             
    //   |             x
    //    x     ->   /   |
    //     |        z    y   
    //      z
    TreeNode* right = parent->getRight();
    parent->setRight(right->getLeft());
    right->setLeft(parent);
    //Update Height
    parent->updateHeight();
    right->updateHeight();
    return right;
}

TreeNode * AVLIndexTree::RL_rotate(TreeNode* parent) {
    //   y       
    //    |             z
    //     x    ->    /   |
    //    /          x    y   
    //  z
    TreeNode* right = parent->getRight();
    parent->setRight(LL_rotate(right));
    return RR_rotate(parent);
}

TreeNode * AVLIndexTree::LL_rotate(TreeNode* parent) {
    //          y       
    //        /           x
    //      x      ->   /   |
    //    /            z    y   
    //  z
    TreeNode* left = parent->getLeft();
    parent->setLeft(left->getRight());
    left->setRight(parent);
    // Update Height
    parent->updateHeight();
    left->updateHeight();
    return left;
}

TreeNode * AVLIndexTree::LR_rotate(TreeNode* parent) {
    //       y       
    //     /           z
    //   x      ->   /   |
    //    |         x    y   
    //     z
    TreeNode* left = parent->getLeft();
    parent->setLeft(RR_rotate(left));
    return LL_rotate(parent);
}

std::vector<size_t>* AVLIndexTree::lookUp(const char * target) {
    TreeNode* node = root;
    while (node != nullptr) {
        int cmp = compare(node->front(), target);
        if (cmp < 0)
            node = node->getRight();
        else if (cmp > 0)
            node = node->getLeft();
        else
            return node->getIndexList();
    }
    return new std::vector<size_t>();
}

void AVLIndexTree::print() {
    // std::cout << "Called: AVLIndexTree::print()" << std::endl;
    std::queue<TreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        size_t size = queue.size();
        for (size_t i=0; i<size; ++i) {
            TreeNode* node = queue.front();
            queue.pop();
            if (node->hasLeft())
                queue.push(node->getLeft());
            if (node->hasRight())
                queue.push(node->getRight());
            node->printList();
        }
        std::cout << std::endl;
    }
    // std::cout << "End AVLIndexTree::print()" << std::endl;
}

// void AVLIndexTree::getBalanceTime() {
//     std::cout << "Balance Time: " 
// 		<< std::chrono::duration_cast<std::chrono::milliseconds>(balanceTime).count() 
// 		<< " [ms]" << std::endl;
// }