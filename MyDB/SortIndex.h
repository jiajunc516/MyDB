#pragma once
#include <vector>
#include <memory>
#include <iostream>

class SortIndex {
private:
    std::vector<std::unique_ptr<char[]>> * column;
    std::vector<size_t> sortedCol;

    int compare(const size_t left, const size_t right);
    int compare(const size_t dest, const char * target);
    void insert(size_t size);
    void sort();
    void quickSort(int start, int end);
    size_t binarySearch(const char* target);
public:
    SortIndex(std::vector<std::unique_ptr<char[]>> * v);
    void put(size_t size);
    std::vector<size_t>* lookUp(const char* target);
    void print();
    ~SortIndex();
};

