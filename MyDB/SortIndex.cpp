#include "SortIndex.h"

SortIndex::SortIndex(std::vector<std::unique_ptr<char[]>> * v)
    : column(v) {
}

SortIndex::~SortIndex() {}

int SortIndex::compare(const size_t left, const size_t right) {
    return strcmp(column->at(left).get(), column->at(right).get());
}

int SortIndex::compare(const size_t dest, const char * target) {
    return strcmp(column->at(dest).get(), target);
}

void SortIndex::insert(size_t size) {
    for (size_t i=0; i<size; ++i) {
        sortedCol.push_back(i);
    }
}

void SortIndex::sort() {
    quickSort(0, column->size()-1);
}

void SortIndex::quickSort(int start, int end) {
    if (start >= end)
        return ;
    int l = start, r = end;
    size_t pivot = sortedCol.at((l + r) / 2);
    while (l <= r) {
        while (compare(sortedCol.at(l), pivot) < 0 && l <= r) {
            ++l;
        }
        while (compare(sortedCol.at(r), pivot) > 0 && l <= r) {
            --r;
        }
        if (l <= r) {
            size_t temp = sortedCol.at(l);
            sortedCol.at(l) = sortedCol.at(r);
            sortedCol.at(r) = temp;
            ++l;
            --r;
        }
    }
    quickSort(start, r);
    quickSort(l, end);
}

void SortIndex::put(size_t size) {
    insert(size);
    sort();
}

size_t SortIndex::binarySearch(const char* target) {
    size_t left = 0, right = sortedCol.size()-1;
    while (left < right) {
        size_t mid = (left + right) / 2;
        int cmp = compare(sortedCol.at(mid), target);
        if (cmp > 0) {
            right = mid;
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}

std::vector<size_t>* SortIndex::lookUp(const char* target) {
    size_t index = binarySearch(target);
    std::vector<size_t> * outList = new std::vector<size_t>();
    if (index == -1) {
        return outList;
    }
    int start = index, end = index;
    int n = sortedCol.size();
    while (start >= 0 && compare(sortedCol.at(start), sortedCol.at(index)) == 0) {
        --start;
    }
    while (end < n && compare(sortedCol.at(end), sortedCol.at(index)) == 0) {
        ++end;
    }
    for (int i = start+1; i<end; ++i) {
        outList->push_back(sortedCol.at(i));
    }
    return outList;
}

void SortIndex::print() {
    for (auto it=sortedCol.cbegin(); it != sortedCol.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}