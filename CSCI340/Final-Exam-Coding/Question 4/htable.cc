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

// Hash function
int HT::hash(const string &s) {

  int n = (N2 * N1) * (s[0] - 'A');

  return n % hsize;

}

/*
* Resizes the hash table
*
* @param hs -> The size of the hash table to update the vectors
*/
HT::HT(const unsigned &hs) {

  hTable.resize(hs); // Resize the hash table
  hsize = hs;        // Set hsize to the size specified

}

/*
* Inserts an Entry object into the hash table
*
* @param e -> The entry to be inserted into the hash
*/
void HT::insert(const Entry &e) {

    int i = hash(e.key);
    int count = -1;

    list<Entry> &l = hTable[i]; // The list of entries at that hash value

    // Determine if the entry key is in the list
    list<Entry>::iterator it = find_if(l.begin(), l.end(), [&](const Entry &s) { count++; return s.key == e.key; });

    // This means the entry is not in the hash table already
    if (it == l.cend()) {

        hTable[i].push_back(e); // Insert into table
        ordered.push_back(&hTable[i].back());

    } else { // Key was found

        it->count += 1;

    }

}

/*
* Prints the hash table
*/
void HT::hTable_print() {

    for (vector<Entry*>::iterator it1 = ordered.begin(); it1 != ordered.end(); ++it1) {

        (*it1)->key[0] = toupper((*it1)->key[0]);
        cout << setw(20) << left << (*it1)->key << (*it1)->count << endl;

    }

}