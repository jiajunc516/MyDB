#include <iostream>
#include <memory>
#include <chrono>
#include "MyDB.h"
#include "Manager.h"

#define CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
//在入口函数中包含 _CrtDumpMemoryLeaks();
//即可检测到内存泄露

//定义函数:
inline void EnableMemLeakCheck()
{
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

}

using namespace std;

void printElapsedTimeForRead(Manager* m, void (Manager::*pRead)(const char*), const char* filename) {
	cout << "Start Reading Input..." << endl;
	auto start = chrono::steady_clock::now();
	(m->*pRead)(filename);
	auto end = chrono::steady_clock::now();
	cout << "Read Complete Successfully. Time Elapsed: "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " [ms]" << endl;
}

void printElapsedTimeForIndex(Manager* m, void (Manager::*pIndex)()) {
	cout << "Start Constructing Index..." << endl;
	auto start = chrono::steady_clock::now();
	(m->*pIndex)();
	auto end = chrono::steady_clock::now();
	cout << "Construction Complete Successfully. Time Elapsed: " 
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count() 
		<< " [ms]" << endl;
}

void printElapsedTimeForSelect(Manager* m, const std::vector<size_t>* (Manager::*pSelect)(const char*), const char* target) {
	cout << "Start Searching Target..." << endl;
	auto start = chrono::steady_clock::now();
	const std::vector<size_t>* v = (m->*pSelect)(target);
	auto end = chrono::steady_clock::now();

	cout << "Search Complete Successfully. Time Elapsed: " 
		<< chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
		<< " [ns]" << endl;

	cout << "Start Printing Data:" << endl;
	auto starti = chrono::steady_clock::now();
	m->print(v);
	auto endi = chrono::steady_clock::now();
	cout << "Print Complete. Time Elapsed: " 
		<< chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
		<< " [ns]" << endl;
}

int main() {
	EnableMemLeakCheck();
	// MyDB db;
	// db.put("a");
	// db.put("bc");
	// db.put("defg");
	// db.put("a");
	// db.put("ab");
	// db.put("ba");
	// db.put("bcdg");
	// db.put("bc");
	// db.put("defg");
	// db.put("bcdg");
	// db.put("a");
	// db.index();
	// db.printTree();
	// cout << "----------------" << endl;
	// cout << "Search: a" << endl;
	// db.findAll("a");

	Manager dbms(8);
	// select * from Customers where Country = 'USA';
	// printElapsedTimeForRead(&dbms, &Manager::readInputFile, "Country.txt");
	// printElapsedTimeForIndex(&dbms, &(Manager::index));
	// printElapsedTimeForSelect(&dbms, &(Manager::select), "USA");

	// select * from Orders where OrderLineNumber = '2';
	// dbms.readInputFile("OrderLineNumber.txt");
	// printElapsedTimeForIndex(&dbms, &(Manager::index));
	// printElapsedTimeForSelect(&dbms, &(Manager::select), "2");

	printElapsedTimeForRead(&dbms, &Manager::readInputFile, "RandomString.txt");
	printElapsedTimeForIndex(&dbms, &Manager::index);
	// dbms.getDB()->getRows()->getBalanceTime();
	printElapsedTimeForSelect(&dbms, &Manager::select, "z");
	
	return 0;
}