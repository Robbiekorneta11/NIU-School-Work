#ifndef H_ENTRY
#define H_ENTRY

#include <string>
using namespace std;

#define ID_SZ   3   // size of key
#define ITEM_SZ 24  // max size for item description
#define TBL_SZ  31  // default size for hash table

// entry in hash table

struct Entry {

  string key;   // key
  int count;

  // constructor
  Entry(const string& k = "", int c = 1) : key(k), count(c) {}

};

#endif