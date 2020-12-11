/* 	
  Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

/*
* Resizes the hash table
*
* @param hs -> The size of the hash table to update the vectors
*/
HT::HT(const unsigned &hs) {

  hTable.resize(hs); // Resize the hash table
  pTable.resize(0); // Resize pointer table
  hsize = hs;        // Set hsize to the size specified

}

/*
* Destructor to free memory
*/
HT::~HT() {

  // Loop through hash table
  for (unsigned i = 0; i < hTable.size(); i++) {

    hTable.pop_back(); // Remove value
    pTable.pop_back(); // Remove value

  }

}

/*
* Inserts an Entry object into the hash table and pointer table
*
* @param e -> The entry to be inserted into the hash and pointer table
*/
void HT::insert(const Entry &e) {

  int i = hash(e.key);        // Hash value
  list<Entry> &l = hTable[i]; // The list of entries at that hash value

  // Determine if the entry key is in the list
  list<Entry>::iterator it = find_if(l.begin(), l.end(), [&](const Entry &s) { return s.key == e.key; });

  // This means the entry is not in the hash table already
  if (it == l.cend()) {

    hTable[i].push_back(e); // Insert into table
    cout << " entry = " << i << endl;
    pTable.push_back(&hTable[i].back());     // Insert into pointer table

  } else { // Key was found

    cout << " not inserted - duplicate key!!!\n";

  }

}

/*
* Searches for the given key in the hash table
*
* @param s -> The key to look for
*/
void HT::search(const string &s) {

  int i = hash(s); // Get the hash value
  list<Entry> &l = hTable[i]; // list of values at that hash value

  // Find if key is in the list
  list<Entry>::iterator it = find_if(l.begin(), l.end(), [&](const Entry &e) { return e.key == s; });

  // If it is in the list, then print information
  if (it != l.cend()) {

    cout << " ==> number: " << l.front().num << endl;

  } else { // If not, print that the key is not in the table

    cout << " key " << s << " not in table!!\n";

  }

}

/*
* Prints the hash table
*/
void HT::hTable_print() {

  // Loop through the hash table and get the list of entries
  for (vector<list<Entry>>::iterator it = hTable.begin(); it != hTable.end(); ++it) {

    list<Entry> &l = *it; // The list of entries

    // Loop through the list to get the entries
    for (list<Entry>::iterator it1 = l.begin(); it1 != l.end(); ++it1) {

      int i = hash(it1->key); // Get hash value
      cout << setw(4) << i << ":  " << it1->key << "  -" << setw(6) << it1->num << "  -  " << it1->desc << endl;

    }

    cout << endl;

  }

}

/*
* Compares 2 keys of an entry to sort
*
* @param p -> First entry
* @param q -> Second entry
*/
bool cmp(Entry *p, Entry *q) {

  // If key in location p comes before q, return true
  return (p->key < q->key);

}

/*
* Prints the pointer table
*/
void HT::pTable_print() {

  sort(pTable.begin(), pTable.end(), cmp); // Sort the pointer table

  for (vector<Entry*>::iterator it1 = pTable.begin(); it1 != pTable.end(); ++it1) {

      cout << "   " << (*it1)->key << "  -" << setw(6) << (*it1)->num << "  -  " << (*it1)->desc << "\n";

    }

}