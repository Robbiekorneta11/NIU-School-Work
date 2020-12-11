/* 	Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.

*/

#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <ctype.h>
#include <locale>
#include "wordscanner.h"

using namespace std;

int inWords;  //Num of input words
int outWords; //Num of outputted words

int main() {

    map<string, int> m; //Map to hold words

    get_words(m);

    print_words(m);

}

/*
* Get the words from the input stream and append them to the map
*
* @param m the map to insert elements in
* 
*/

void get_words(map<string, int>& m) {

    string before = ""; //Before word
    string after = ""; //After word

    //Read input into variable before
    while (cin >> before) {

        clean_entry(before, after); //Clean the word to remove non alphanumeric characters

        if (after.length() > 0) {

            m[after]++; //Add to map
            inWords++; //Increase the amount of input words

        }

        after = "";

    }

}

/*
* Prints the contents of the map
*
* @param m the map to print
*/

void print_words(const map<string, int>& m) {

    int c = 0; //Count to see when to create new line

    for (auto it=m.cbegin(); it!=m.cend(); ++it) {

        outWords++; //Increase amount of outwords

        cout << setw(16) << internal << left << it->first << ": " << it->second << "\t";

        c++;

        if (c == 3) {

            cout << endl;
            c = 0;

        }

    }

    cout << endl;

    cout << "no of words in input stream  : " << inWords << endl;
    cout << "no of words in output stream : " << outWords << endl;

}

/*
* Remove all non alphanumeric characters from the word
*
* @param x The word to be cleaned
* @param y The resulting word after all non alphanumeric characters
*/

void clean_entry(const string& x, string& y) {

    for (size_t j = 0; j < x.length(); j++) { //Loop through word

        if (isalnum(x[j])) { //Check to see if the character is alphanumeric

            char z = tolower(x[j]); //Convert to lowercase
            y += z; //Add character to new string

        } else {

            if (j > 0) {

                break;

            }

        }

    }

}