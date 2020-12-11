/* 	
  Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#ifndef H_DOUBLYLINKEDLIST
#define H_DOUBLYLINKEDLIST

#include <iostream>
#include <iomanip>
#include <string>
#include "node.h"

using namespace std;

// Represents a doubly linked list
class DoublyLinkedList {

    public:
        node *frontNode;    // Front node of the list
        node *backNode;     // Back node of the list
        size_t listSize;    // Size of the list
        DoublyLinkedList() { frontNode = NULL; backNode = NULL; listSize = 0; }
        void Insertion(const int&);
        void Deletion();
        void InsertLast(const int&);
        void InsertFirst(const int&);
        void DeleteLast();
        void DeleteFirst();
        void InsertAfter(node*, const int&);
        void Delete(node*);
        void DisplayForward();
        void DisplayBackward();

};

/**
 * Inserts an element at the beginning of the list
 * 
 * @param x -> The data to be inserted
 * ******************************************************/
void DoublyLinkedList::Insertion(const int &x) {

	node *newNode = nullptr;                    // Create new node to hold data
    newNode = new node(x, newNode, newNode);    // ^^^^
    newNode->next = frontNode;                  // Point new node's next pointer at current front node in the list

    // Check to see if list is empty
    if (listSize > 0) {

        frontNode->prev = newNode;  // Point current front node's prev pointer at new front node in the list
        frontNode = newNode;        // Point frontNode at new front node in the list

    } else {

        backNode = newNode;         // Point back node to the new node
        frontNode = newNode;        // Point front node to the new node

    }

    listSize += 1;                  // Increase list size

}

/**
 * Deletes an element at the beginning of a list
 * **********************************************/
void DoublyLinkedList::Deletion() {

    // If list is empty, nothing to delete
    if (listSize == 0) {

        cout << "Error - There are no items in the list\n";

    } else {

        node *delNode = frontNode; // Save address of node to delete in a pointer
        frontNode = delNode->next; // Point front node at the new next node in the list

        if (frontNode == nullptr) {

            backNode = nullptr; // List is empty now
            delete delNode;

        } else {

            frontNode->prev = nullptr; // Set the new front node's prev pointer to nullptr
            delete delNode;

        }

        listSize -= 1; // Decrement list size

    }

}

/**
 * Inserts an element at the end of a list
 * 
 * @param x -> The element to insert
 * ***********************************************/
void DoublyLinkedList::InsertLast(const int &x) {

    node *newNode = nullptr;                    // Create new node
    newNode = new node(x, newNode, newNode);    // ^^^^
    newNode->prev = backNode;                   // Point new node's prev pointer at current last node in the list

    // List is not empty
    if (listSize > 0) {

        backNode->next = newNode;   // Point current back node's next pointer at new last node in the list
        backNode = newNode;         // Point backNode at new last node in the list

    } else {

        frontNode = newNode;        // Point frontNode at new first node in the list
        backNode = newNode;         // Point backNode at new last node in the list

    }

    listSize += 1; // Increase list size

}

/**
 * Inserts an element at the front of a list
 * 
 * @param x -> The element to insert
 * ***********************************************/
void DoublyLinkedList::InsertFirst(const int &x) {

    node *newNode = nullptr;                    // Create new node to hold data
    newNode = new node(x, newNode, newNode);    // ^^^^
    newNode->next = frontNode;                  // Point new node's next pointer at current front node in the list

    // Check to see if list is empty
    if (listSize > 0) {

        frontNode->prev = newNode;  // Point current front node's prev pointer at new front node in the list
        frontNode = newNode;        // Point frontNode at new front node in the list

    } else {

        backNode = newNode;         // Point back node to the new node
        frontNode = newNode;        // Point front node to the new node

    }

    listSize += 1;                  // Increase list size

}

/**
 * Deletes an element at the back of a list
 * **********************************************/
void DoublyLinkedList::DeleteLast() {

    // Check for empty list
    if (listSize == 0) {

        cout << "Error - There are no items in the list\n";

    } else {

        node *delNode = backNode;   // Save address of node to delete in a pointer
        backNode = delNode->prev;   // Point back node at the new prev node in the list

        if (backNode == nullptr) {

            frontNode = nullptr;        // List is empty now
            delete delNode;

        } else {

            backNode->next = nullptr;   // Set the new last node's next pointer to nullptr
            delete delNode;

        }

        listSize -= 1; // Decrease size of list

    }

}

/**
 * Deletes an element at the front of a list
 * **********************************************/
void DoublyLinkedList::DeleteFirst() {

    // If list is empty, nothing to delete
    if (listSize == 0) {

        cout << "Error - There are no items in the list\n";

    } else {

        node *delNode = frontNode; // Save address of node to delete in a pointer
        frontNode = delNode->next; // Point front node at the new next node in the list

        if (frontNode == nullptr) {

            backNode = nullptr; // List is empty now
            delete delNode;

        } else {

            frontNode->prev = nullptr; // Set the new front node's prev pointer to nullptr
            delete delNode;

        }

        listSize -= 1; // Decrement list size

    }

}

/**
 * Inserts an element after the specified node
 * 
 * @param prevNode -> The node to insert the value after
 * @param x        -> The element to insert
 * ****************************************************************/
void DoublyLinkedList::InsertAfter(node *prevNode, const int &x) {

    node *newNode = nullptr;                    // Create new node
    newNode = new node(x, newNode, newNode);    // ^^^^

    newNode->next = prevNode->next;             // Set the new nodes next pointer to the prev nodes next pointer
    prevNode->next = newNode;                   // Set the prev nodes next pointer to the new node
    newNode->prev = prevNode;                   // Set the new nodes prev pointer to the prev node

    // If node is the end of the list
    if (newNode->next != NULL)
        newNode->next->prev = newNode;

}

/**
 * Deletes a specififed node
 * 
 * @param delNode -> pointer to the node to delete
 * **************************************************/
void DoublyLinkedList::Delete(node *delNode) {

    // If the pointer to the previous node is null
    if (delNode->prev == NULL) {

		frontNode = delNode->next;  // Set front node to the pointer to next node
		frontNode->prev = NULL;     // Set front nodes pointer to the previous node to null

	} else if (delNode->next == NULL) { // If pointer to next node is null

		backNode = delNode->prev;   // Set backnode to delnodes prev pointer
		backNode->next = NULL;      // Set backnode next pointer to null

	} else { // Do normal deletion
		
		delNode->prev->next = delNode->next;
		delNode->next->prev = delNode->prev;
        
	}
	
	delete(delNode); 

}

/**
 * Prints the list out in forward traversal
 * *******************************************/
void DoublyLinkedList::DisplayForward() {

    node *n;
    n = frontNode;

    while (n != NULL) {

        cout << setw(5) << left << n->data;
        n = n->next;

    }

    cout << endl;

}

/**
 * Prints the list out in backward traversal
 * *******************************************/
void DoublyLinkedList::DisplayBackward() {

    node *n;
    n = backNode;

    while (n != NULL) {

        cout << setw(5) << left << n->data;
        n = n->prev;

    }

    cout << endl;

}

#endif