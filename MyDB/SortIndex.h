#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <string.h>

class SortIndex {
private:
    std::vector<std::unique_ptr<char[]>> * column;
    size_t * sortedCol = nullptr;
    size_t size;
    std::chrono::duration<int64_t, std::nano> balanceTime;

    int compare(const size_t left, const size_t right);
    int compare(const size_t dest, const char * target);
    int pickFromThree(int l, int r);
    void insert(size_t size);
    void sort();
    void quickSort(int start, int end);
    void mergeSort(int left, int right);
    void merge(int left, int mid, int right);
    void insertSort(int left, int right);
    void swap(int l, int r);
    size_t binarySearch(const char* target);
public:
    SortIndex(std::vector<std::unique_ptr<char[]>> * v);
    void put(size_t size);
    size_t getSize();
    void setSize(size_t size);
    std::vector<size_t>* lookUp(const char* target);
    void print();
    void getBalanceTime();
    ~SortIndex();
};

