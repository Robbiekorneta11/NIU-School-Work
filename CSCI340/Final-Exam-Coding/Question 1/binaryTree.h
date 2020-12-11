/* 	
    Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#ifndef H_BINARYTREE
#define H_BINARYTREE

#include <string>
#include "node.h"

// Represents a binary tree to be created from user input
class BinaryTree {

    public:
        Node *root;                         // Root of tree
        BinaryTree(string, string, string); // Constructor
        void BeginQuestions();

    private:
        void _BeginQuestions(Node*);

};

/**
 * Constructs a node to place in a binary tree
 * 
 * @param q -> The question
 * @param y -> The answer of the animal to no
 * @param n -> The answer of the animal to yes
 * ***************************************************/
BinaryTree::BinaryTree(string q, string y, string n) {

    root = new Node(q);         // Create root node
    root->no = new Node(n);     // Create the answer for the no node
    root->yes = new Node(y);    // Create the answer for the yes node

}

/**
 * Public accessor method to begin
 * the game
 * ********************************/
void BinaryTree::BeginQuestions() {

    _BeginQuestions(this->root);

}

/**
 * Begins asking questions to build the 
 * binary tree and guess the users' animal
 * 
 * @param ptr -> The pointer to the current node
 * ******************************************/
void BinaryTree::_BeginQuestions(Node *ptr) {

    // Check to make sure the node is a question
    if (ptr->isQuestion()) {

        string yOrN;                    // Holds the user input of the question
        cout << ptr->response << " ";   // Prompt for user input
        getline(cin, yOrN);             // ^^^

        // If use answers yes, move to the right node of the subtree
        // else, move to the left node of the subtree
        if (yOrN == "y")
            _BeginQuestions(ptr->yes);
        else
            _BeginQuestions(ptr->no);

    } else { // If not a question, guess and answer based on the current node

        string yOrN;
        cout << "Were you thinking of a " << ptr->response << "? ";
        getline(cin, yOrN);

        // If program guessed right
        if (yOrN == "y")
            cout << "Great!\n";
        else { // Prgoram did not guess right

            string userAnswer;      // Users' answer to the question
            string userQuestion;    // Question that the user inputs
            string correct;         // Whether or not the user provided answer
                                    // is the correct answer to the question

            // Get the answer and have user input a new question
            cout << "Doh! What was the animal? ";
            getline(cin, userAnswer);
            cout << "What question separates " << userAnswer << " from " << ptr->response << "? ";
            getline(cin, userQuestion);
            cout << "What is the correct answer for this animal? ";
            getline(cin, correct);

            // Set up new nodes in binary tree
            if (correct == "y") {

                ptr->no = new Node(ptr->response);
                ptr->yes = new Node(userAnswer);

            } else {

                ptr->yes = new Node(ptr->response);
                ptr->no = new Node(userAnswer);

            }

            ptr->response = userQuestion; // Update answer node with the question

        }

    }

}

#endif // End of H_BINARYTREE