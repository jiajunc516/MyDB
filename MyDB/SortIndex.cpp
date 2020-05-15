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
    auto start = std::chrono::steady_clock::now();
    int i = strcmp(column->at(left).get(), column->at(right).get());
    auto end = std::chrono::steady_clock::now();
    balanceTime += (end - start);
    return i;
}

int SortIndex::compare(const size_t dest, const char * target) {
    auto start = std::chrono::steady_clock::now();
    int i = strcmp(column->at(dest).get(), target);
    auto end = std::chrono::steady_clock::now();
    balanceTime += (end - start);
    return i;
}

void SortIndex::insert(size_t size) {
    this->sortedCol = new size_t[size];
    setSize(size);
    for (size_t i=0; i<size; ++i) {
        this->sortedCol[i] = i;
    }
}

void SortIndex::sort() {
    quickSort(0, column->size()-1);
    //mergeSort(0, size-1);
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
    for (int i = left+1; i <= right; ++i) {
        if (compare(sortedCol[i], sortedCol[i-1]) < 0) {
            for (int j = left; j < i; ++j) {
                if (compare(sortedCol[j], sortedCol[i]) > 0) {
                    swap(i, j);
                }
            }
        }
    }
}

int SortIndex::pickFromThree(int l, int r) {
    int temp[3] = {l, (l+r)/2, r};
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2-i; ++j) {
            if (compare(sortedCol[temp[j]], sortedCol[temp[j+1]]) > 0) {
                int t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }
        }
    }
    return temp[1];
}

void SortIndex::quickSort(int start, int end) {
    if (end - start < 9) {
        insertSort(start, end);
        return ;
    }
    int l = start, r = end;
    size_t pivot = sortedCol[pickFromThree(start, end)];
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
    auto start = std::chrono::steady_clock::now();
    sort();
    auto end = std::chrono::steady_clock::now();
    std::cout << "Sort takes time: " 
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
		<< " [ms]" << std::endl;
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

void SortIndex::swap(int l, int r) {
    size_t temp = sortedCol[l];
    sortedCol[l] = sortedCol[r];
    sortedCol[r] = temp;
}

void SortIndex::print() {
    for (size_t i = 0; i < size; ++i) {
        std::cout << column->at(sortedCol[i]).get() << " ";
    }
    std::cout << std::endl;
}

void SortIndex::getBalanceTime() {
    std::cout << "Compare Time: " 
		<< std::chrono::duration_cast<std::chrono::milliseconds>(balanceTime).count() 
		<< " [ms]" << std::endl;
}