/* 	Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.

*/

#ifndef H_WORDSCANNER // should not be defined any place else 
#define H_WORDSCANNER // same const value as for ifndef directive

#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>

using namespace std;

typedef struct 
{ 
    int id;         // id starts at 1
    string lp;      // license plate of car
    int no_mv;      // number times the car has been moved
}CAR;

void get_input_vals(const string&, char&, string&);
void arrival(const CAR&, deque<CAR>&);
void departure(const string&, deque<CAR>&, stack<CAR>&);

#endif