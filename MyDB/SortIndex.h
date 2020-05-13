#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <string.h>

class SortIndex {
private:
    std::vector<std::unique_ptr<char[]>> * column;
    size_t * sortedCol = nullptr;
    size_t size;

    int compare(const size_t left, const size_t right);
    int compare(const size_t dest, const char * target);
    void insert(size_t size);
    void sort();
    void quickSort(int start, int end);
    void mergeSort(int left, int right);
    void merge(int left, int mid, int right);
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

