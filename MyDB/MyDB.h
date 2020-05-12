#pragma once
#include <queue>
#include <vector>
#include <memory>

#include "AVLIndexTree.h"
#include "SortIndex.h"

#define DEFAULTSIZE 256

// class AVLIndexTree;

class MyDB {
private:
    size_t size;
    int CHARSIZE;
    bool isIndex = false;
    
    std::vector<std::unique_ptr<char[]>> column;
    AVLIndexTree* rows;
    SortIndex* sortedRows;

    void createIndex();
    std::vector<size_t>* getListByLinear(const char * target);
    std::vector<size_t>* getListByIndex(const char * target);

public:
    MyDB();
    MyDB(int maxL);
    ~MyDB();

    void index();
    void indexBySort();
    void put(const char * src);
    const std::vector<size_t>* findAll(const char * target);
    const std::vector<size_t>* findBySort(const char * target);
    void print(const std::vector<size_t>* inList);
    void printBySort(const std::vector<size_t>* inList);

    size_t getSize();
    size_t getSize() const;
    void setSize(size_t n);
    int getCharSize();
    int getCharSize() const;
    void printTree();
    void printList();
};

