/* 	
  Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#ifndef H_NODE
#define H_NODE

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Represents a node in the binary tree
class Node {

    public:
        string response;    // Response of user
        Node *no;           // No node (left)
        Node *yes;          // Yes node (right)
        Node(string r) { response = r; no = NULL; yes = NULL; }
        bool isQuestion();

};

/**
 * Determines if the node
 * is a question
 * 
 * @return true if question
 *         false if not
 * **********************/
bool Node::isQuestion() {

    if (no == NULL && yes == NULL) {

        return false;

    } else {

        return true;

    }

}


#endif