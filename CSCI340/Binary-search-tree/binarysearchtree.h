/* 	
    Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

// include other header files (if any)
#include "node.h"
#include "binarytree.h"
#include <iostream>

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

// put statements in header file
template <typename T>
class BinarySearchTree : public BinaryTree<T> {

public:
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x

private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
    void getPred(Node<T> *, Node<T> *&, const T &); // Gets the predecessor of the node

};
// Public function to insert a node into bst
template <typename T>
void BinarySearchTree<T>::Insert(const T &x) {

    _Insert(this->root, x);

}

// Public function to find a value in a bst
template <typename T>
bool BinarySearchTree<T>::Search(const T &x) const {

    bool result = _Search(this->root, x);

    return result;

}

// Public function to remove a node from the tree
template <typename T>
bool BinarySearchTree<T>::Remove(const T &x) {

    bool result = Search(x); // Figure out if the key exists in the bst

    // If it exists, then remove from the bst
    if (result) {

        _Remove(this->root, x);
        return true;

    } else {

        return false;

    }

}

/*
*   Inserts a value into the bst
*
*   @param ptr -> A pointer to the node being looked at
*   @param x   -> The value to be inserted into the bst
*/
template <typename T>
void BinarySearchTree<T>::_Insert(Node<T> *&ptr, const T &x) {

    if (ptr == NULL) { // Check for null pointer

        ptr = new Node<T>(x); // Create new node from default constructor

    } else if (x < ptr->data) { // Check if value is less than current node

        _Insert(ptr->left, x); // Recursion to insert value

    } else if (x > ptr->data) { // Check if value is greater than current node

        _Insert(ptr->right, x); // Recursion to insert value

    }

}

/*
*   Finds the specified value in the bst
*
*   @param ptr -> A pointer to the node being looked at
*   @param x   -> The value to find in the bst
*
*   @return true if the value is found
*/
template <typename T>
bool BinarySearchTree<T>::_Search(Node<T> *ptr, const T &x) const {

    if (ptr == NULL) { // Check for end of tree

        return false;

    } else if (ptr->data == x) { // Found the key

        return true;

    } else if (x < ptr->data) { // Binary search to look in left subtree

        return _Search(ptr->left, x);

    } else if (x > ptr->data) { // Binary search to look in right sub tree

        return _Search(ptr->right, x);

    } else {

        return false;

    }

}

/*
*   Gets the predeccesor of the value in the tree
*
*   @param ptr  -> A pointer to the node being looked at
*   @param pred -> A pointer to the value of the predeccesor
*   @param x    -> The value that we need to find the predeccesor of
*/
template <typename T>
void BinarySearchTree<T>::getPred(Node<T> *ptr, Node<T> *&pred, const T &x) {

    if (ptr == NULL) { // Check for end of tree

        pred = NULL;
        return;

    }

    // Check to see if value in the tree is equal to the value
    if (ptr->data == x) {

        // Look into left subtree
        if (ptr->left != NULL) {

            pred = ptr->left; // Go to left subtree

            // Go down into the right most leaf to get predecessor
            while (pred->right != NULL) {

                pred = pred->right;

            }

        }

    }

    return;

}

/*
*   Removes a value from the bst
*
*   @param ptr -> A pointer to the node being looked at
*   @param x   -> The value to be removed
*/
template <typename T>
void BinarySearchTree<T>::_Remove(Node<T> *&ptr, const T &x) {

    if (ptr == NULL) { // Check for end of tree

        return;

    } else if (x < ptr->data) { // Check for value being less than the current node

        _Remove(ptr->left, x); // Recursion to pin point the value in the bst

    } else if (x > ptr->data) { // Check for value being greater than the current node

        _Remove(ptr->right, x); // Recursion to pinpoint the value in the bst

    } else { // Found the value

        // This means the subtree has two children
        if (ptr->left != NULL && ptr->right != NULL) {

            Node<T> *pred = NULL; // Node to hold predeccesor
            pred = ptr->left; // Go to the left subtree
            pred = pred->right; // Go to the right subtree of the left subtree
            getPred(ptr, pred, x); // Get the predeccesor
            ptr->data = pred->data; // Set the nodes data to the predeccesors data
            _Remove(ptr->left, pred->data); // Remove the node

        } else if (_Leaf(ptr) == true) { // If value is a leaf

            delete ptr; // Delete the leaf
            ptr = NULL;
            return;

        } else {

            if (ptr->left == NULL) { // Only has right child

                Node<T> *temp = ptr;
                ptr = ptr->right;
                delete temp; // Remove node
                return;

            }

            if (ptr->right == NULL) { // Only has left child

                Node<T> *temp = ptr;
                ptr = ptr->left;
                delete temp; // Remove node
                return;

            }

        }

    }

}

/*
*   Checks to see if a node is a leaf
*
*   @param node -> A pointer to the node being looked at
*
*   @return true if the node is a leaf
*/
template <typename T>
bool BinarySearchTree<T>::_Leaf(Node<T> *node) const {

    if (node->left == NULL && node->right == NULL) {

        return true;

    } else {

        return false;

    }

}

#endif // End of BINARYSEARCHTREE_H_