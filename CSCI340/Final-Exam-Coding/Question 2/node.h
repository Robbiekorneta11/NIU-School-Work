/* 	
  Robi Korneta
	Z1816167
	CSCI 340 - 1
	
*/

#ifndef H_NODE
#define H_NODE

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Represents node in linked list
struct node {

    int data;
    node *next;
	node *prev;
	node(int x, node* p = nullptr, node* n = nullptr) {

		data = x;
		prev = p;
		next = n;

	}

};

#endif