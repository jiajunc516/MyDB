#include "SortIndex.h"

SortIndex::SortIndex(std::vector<std::unique_ptr<char[]>> * v)
    : column(v) {
}

SortIndex::~SortIndex() {
    if (sortedCol != nullptr) {
        delete sortedCol;
    }
}

size_t SortIndex::getSize() {
    return size;
}

void SortIndex::setSize(size_t size) {
    this->size = size;
}

int SortIndex::compare(const size_t left, const size_t right) {
    return strcmp(column->at(left).get(), column->at(right).get());
}

int SortIndex::compare(const size_t dest, const char * target) {
    return strcmp(column->at(dest).get(), target);
}

void SortIndex::insert(size_t size) {
    this->sortedCol = new size_t[size];
    setSize(size);
    for (size_t i=0; i<size; ++i) {
        this->sortedCol[i] = i;
    }
}

void SortIndex::sort() {
    // quickSort(0, column->size()-1);
    mergeSort(0, size-1);
}

void SortIndex::mergeSort(int left, int right) {
    if (right - left < 8) {
        insertSort(left, right);
        return ;
    }
    int m = (left + right) / 2;
    mergeSort(left, m);
    mergeSort(m+1, right);
    merge(left, m, right);
}

void SortIndex::merge(int left, int mid, int right) {
    int len = right - left + 1;
    size_t* arr = new size_t[len];
    int i = left, j = mid+1, k = 0;
    while (i <= mid && j <= right) {
        if (compare(sortedCol[i], sortedCol[j]) <= 0) {
            arr[k++] = sortedCol[i++];
        }
        else {
            arr[k++] = sortedCol[j++];
        }
    }
    while (i <= mid) {
        arr[k++] = sortedCol[i++];
    }
    while (j <= right) {
        arr[k++] = sortedCol[j++];
    }
    
    for (int x=0; x < len; ++x) {
        sortedCol[left+x] = arr[x];
    }
    delete arr;
}

void SortIndex::insertSort(int left, int right) {
    for (int i = left; i <= right; ++i) {
        for (int j = i; j > left; --j) {
            if (compare(sortedCol[j-1], sortedCol[j]) > 0) {
                size_t temp = sortedCol[j-1];
                sortedCol[j-1] = sortedCol[j];
                sortedCol[j] = temp;
            }
        }
    }
}

void SortIndex::quickSort(int start, int end) {
    if (start >= end)
        return ;
    int l = start, r = end;
    size_t pivot = sortedCol[(l + r) / 2];
    while (l <= r) {
        while (compare(sortedCol[l], pivot) < 0 && l <= r) {
            ++l;
        }
        while (compare(sortedCol[r], pivot) > 0 && l <= r) {
            --r;
        }
        if (l <= r) {
            size_t temp = sortedCol[l];
            sortedCol[l] = sortedCol[r];
            sortedCol[r] = temp;
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
    size_t left = 0, right = size-1;
    while (left < right) {
        size_t mid = (left + right) / 2;
        int cmp = compare(sortedCol[mid], target);
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
    int n = size;
    while (start >= 0 && compare(sortedCol[start], sortedCol[index]) == 0) {
        --start;
    }
    while (end < n && compare(sortedCol[end], sortedCol[index]) == 0) {
        ++end;
    }
    for (int i = start+1; i<end; ++i) {
        outList->push_back(sortedCol[i]);
    }
    return outList;
}

void SortIndex::print() {
    for (size_t i = 0; i < size; ++i) {
        std::cout << column->at(sortedCol[i]).get() << " ";
    }
    std::cout << std::endl;
}