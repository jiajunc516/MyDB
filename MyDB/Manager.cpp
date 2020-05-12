#include "Manager.h"

Manager::Manager() {
    db = new MyDB();
}

Manager::Manager(int size) {
    db = new MyDB(size);
}

Manager::~Manager() {
    delete db;
}

void Manager::readInputFile(const char * filename) {
    std::ifstream inputFile(filename);
    std::string data;
    while (std::getline(inputFile, data)) {
        db->put(data.c_str());
    }
}

void Manager::index() {
    db->index();
}

void Manager::indexBySort() {
    db->indexBySort();
}

void Manager::insert(const char * src) {
    db->put(src);
}

const std::vector<size_t>* Manager::select(const char * target) {
    return db->findAll(target);
}

const std::vector<size_t>* Manager::selectBySort(const char * target) {
    return db->findBySort(target);
}

void Manager::print(const std::vector<size_t>* inList) {
    db->print(inList);
}

void Manager::printBySort(const std::vector<size_t>* inList) {
    db->printBySort(inList);
}

MyDB* Manager::getDB() {
    return db;
}