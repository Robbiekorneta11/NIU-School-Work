#include "entry.h"

#ifndef H_HASH_TABLE
#define H_HASH_TABLE

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

// class for hash table

class HT {
 public:
  HT(const unsigned& = TBL_SZ);  // constructor

  void insert(const Entry&);   // inserts item in hash table

  void hTable_print();  // prints hash table entries

 private:
  unsigned hsize;  // size of hash table

  vector<list<Entry>> hTable;  // hash table
  vector<Entry*> ordered;

  int hash(const string&);  // hash function
};

#endif