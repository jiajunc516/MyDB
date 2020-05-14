#include "SortIndex.h"

SortIndex::SortIndex(std::vector<std::unique_ptr<char[]>> * v)
    : column(v) {
}

SortIndex::~SortIndex() {
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
    sortedCol.resize(size);
    setSize(size);
    for (size_t i=0; i<size; ++i) {
        sortedCol.at(i) = i;
    }
}

void SortIndex::sort() {
    // quickSort(0, column->size()-1);
    mergeSort(0, size-1);
}

void SortIndex::mergeSort(size_t left, size_t right) {
    if (right - left < 8) {
        insertSort(left, right);
        return ;
    }
    size_t m = (left + right) / 2;
    mergeSort(left, m);
    mergeSort(m+1, right);
    merge(left, m, right);
}

void SortIndex::merge(size_t left, size_t mid, size_t right) {
    size_t len = right - left + 1;
    size_t* arr = new size_t[len];
    size_t i = left, j = mid+1, k = 0;
    while (i <= mid && j <= right) {
        if (compare(sortedCol.at(i), sortedCol.at(j)) <= 0) {
            arr[k++] = sortedCol.at(i++);
        }
        else {
            arr[k++] = sortedCol.at(j++);
        }
    }
    while (i <= mid) {
        arr[k++] = sortedCol.at(i++);
    }
    while (j <= right) {
        arr[k++] = sortedCol.at(j++);
    }
    
    for (size_t x=0; x < len; ++x) {
        sortedCol.at(left+x) = arr[x];
    }
    delete arr;
}

void SortIndex::insertSort(size_t left, size_t right) {
    for (size_t i = left; i <= right; ++i) {
        for (size_t j = i; j > left; --j) {
            if (compare(sortedCol.at(j-1), sortedCol.at(j)) > 0) {
                swap(j-1, j);
            }
        }
    }
}

void SortIndex::quickSort(size_t start, size_t end) {
    if (start >= end)
        return ;
    size_t l = start, r = end;
    size_t pivot = sortedCol[(l + r) / 2];
    while (l <= r) {
        while (compare(sortedCol.at(l), pivot) < 0 && l <= r) {
            ++l;
        }
        while (compare(sortedCol.at(r), pivot) > 0 && l <= r) {
            --r;
        }
        if (l <= r) {
            swap(l++, r--);
        }
    }
    quickSort(start, r);
    quickSort(l, end);
}

void SortIndex::swap(size_t left, size_t right) {
    size_t temp = sortedCol.at(left);
    sortedCol.at(left) = sortedCol.at(right);
    sortedCol.at(right) = temp;
}

void SortIndex::put(size_t size) {
    insert(size);
    sort();
}

size_t SortIndex::binarySearch(const char* target) {
    size_t left = 0, right = size-1;
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
    int n = size;
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
    for (size_t i = 0; i < size; ++i) {
        std::cout << column->at(sortedCol.at(i)).get() << " ";
    }
    std::cout << std::endl;
}