/* 	Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "htable.h"

using namespace std;

void removePunctuation(const string& k, string& r) {

    for (size_t j = 0; j < k.length(); j++) { //Loop through word

        if (isalnum(k[j])) { //Check to see if the character is alphanumeric

            char x = tolower(k[j]); //Convert to lowercase
            r += x; //Add character to new string

        } else {

            if (j > 0) {

                break;

            }

        }

    }

}

int main() {

    string input;
    string formattedWord;
    Entry e;
    HT h;

    while (cin >> input) {

        removePunctuation(input, formattedWord);
        cout << "Formatted word: " << formattedWord << endl;
        e.key = formattedWord;
        h.insert(e);
        formattedWord = "";
        
    }

    h.hTable_print();

    return 0;

}