#pragma once
#include <queue>
#include <vector>
#include <memory>
#include <chrono>
#include <string.h>

#include "TreeNode.h"

class AVLIndexTree {
private:
    bool collide = false;
    // std::chrono::duration<int64_t, std::nano> balanceTime;
    TreeNode * root = nullptr;
    std::vector<std::unique_ptr<char[]>> * column = nullptr;
    
    void deleteTree();
    int height(TreeNode* node);
    int height_diff(TreeNode* node);
    int compare(const size_t left, const size_t right);
    int compare(const size_t dest, const char * target);
    int compareChar(const char* left, const char* right);

    TreeNode * RR_rotate(TreeNode* parent);
    TreeNode * RL_rotate(TreeNode* parent);
    TreeNode * LL_rotate(TreeNode* parent);
    TreeNode * LR_rotate(TreeNode* parent);
    TreeNode * insert(const size_t index, TreeNode* node);
    TreeNode * balance(TreeNode* node);

public:
    AVLIndexTree(std::vector<std::unique_ptr<char[]>> * v);
    ~AVLIndexTree();

    void put(const size_t index);
    std::vector<size_t>* lookUp(const char * target);
    // void getBalanceTime();
    void print();
};