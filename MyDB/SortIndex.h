#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <thread>
#include <string.h>

#define THREAD_NUM 4

class SortIndex {
private:
    std::vector<std::unique_ptr<char[]>> * column;
    std::vector<size_t> sortedCol;
    size_t size;
    std::thread threads[THREAD_NUM];

    int compare(const size_t left, const size_t right);
    int compare(const size_t dest, const char * target);
    void insert(size_t size);
    void sort();
    void quickSort(size_t start, size_t end);
    void mergeSort(size_t left, size_t right);
    void merge(size_t left, size_t mid, size_t right);
    void insertSort(size_t left, size_t right);
    void swap(size_t left, size_t right);
    size_t binarySearch(const char* target);
public:
    SortIndex(std::vector<std::unique_ptr<char[]>> * v);
    void put(size_t size);
    size_t getSize();
    void setSize(size_t size);
    std::vector<size_t>* lookUp(const char* target);
    void print();
    ~SortIndex();
};

