// #include "AVLIndexTree.h"
#include "MyDB.h"

MyDB::MyDB()
    : size(0), CHARSIZE(DEFAULTSIZE) {
    // std::cout << "Construct a MyDB" << std::endl;
}

MyDB::MyDB(int maxL)
    : CHARSIZE(maxL) {
}

MyDB::~MyDB() {
    if (sortedRows != nullptr)
        delete sortedRows;
}

size_t MyDB::getSize() {
    return size;
}

size_t MyDB::getSize() const {
    return size;
}

void MyDB::setSize(size_t n) {
    size = n;
}

int MyDB::getCharSize() {
    return CHARSIZE;
}

int MyDB::getCharSize() const {
    return CHARSIZE;
}

void MyDB::index() {
    isIndex = true;
    sortedRows = new SortIndex(&column);
    if (size > 0) {
        sortedRows->put(size);
    }
}

void MyDB::printList() {
    if (!isIndex)
        return ;
    sortedRows->print();
}

void MyDB::put(const char * src) {
    std::unique_ptr<char[]> s(new char[CHARSIZE]);
    strncpy(s.get(), src, CHARSIZE);
    column.push_back(std::move(s));
    ++size;
}

std::vector<size_t>* MyDB::getListByLinear(const char * target) {
    std::vector<size_t> * tempList = new std::vector<size_t>();
    for (size_t i=0; i<size; ++i) {
        if (strcmp(column.at(i).get(), target) == 0) {
            tempList->push_back(i);
        }
    }
    return tempList;
}

std::vector<size_t>* MyDB::getListByIndex(const char * target) {
    return sortedRows->lookUp(target);
}

const std::vector<size_t>* MyDB::findAll(const char * target) {
    return (isIndex) ? getListByIndex(target) : getListByLinear(target);
}

void MyDB::print(const std::vector<size_t>* inList) {
    if (!inList->empty()) {
        std::cout << "Matched Items at index: " << std::endl;
        for (auto it=inList->cbegin(); it != inList->cend(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No matched items found" << std::endl;
    }
    delete inList;
}