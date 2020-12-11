/* 	Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.

*/

#ifndef H_WORDSCANNER // should not be defined any place else 
#define H_WORDSCANNER // same const value as for ifndef directive

#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void get_words(map<string, int>&);
void print_words(const map<string, int>&);
void clean_entry(const string&, string&);

#endif