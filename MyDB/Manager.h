#pragma once
#include <string>
#include <fstream>
#include "MyDB.h"

class Manager
{
private:
    MyDB * db = nullptr;
public:
    Manager();
    Manager(int size);
    ~Manager();

    MyDB* getDB();

    void readInputFile(const char * filename);
    void index();
    void insert(const char * src);
    const std::vector<size_t>* select(const char * target);
    void print(const std::vector<size_t>* inList);
};