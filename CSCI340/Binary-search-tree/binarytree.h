/* 	
    Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#ifndef H_BINARYTREE
#define H_BINARYTREE

#include "node.h"
#include <algorithm>

typedef enum {left_side, right_side } SIDE;

SIDE rnd() { 

    return rand()%2 ? right_side : left_side;

}// End of rnd()

template <typename T> class BinaryTree {

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

//Default constructor to initialize binary tree
template <class T>
BinaryTree <T>::BinaryTree() {

    root = nullptr;

}

//Public function to call private function to get size of binary tree
//Returns the size of the tree
template <class T>
unsigned BinaryTree <T>::getSize() const {

    return _getSize(root);

}

//Public function to call private function to get height of binary tree
//Returns the height of the tree
template <class T>
unsigned BinaryTree <T>::getHeight() const {

    return _getHeight(root);

}

//Public function to call private function to insert a node into the tree
//@param x -> the value to insert into the tree
template <class T>
void BinaryTree <T>::Insert(const T &x) {

    _Insert(root, x);

}

//Public function to call private function to do an inorder traversal of a binary tree
//@param print -> calls print function to stdout
template <class T>
void BinaryTree <T>::Inorder(void (*print)(const T&)) {

    _Inorder(root, print);

}

/*
*   Function to calculate the size of the binary tree
*
*   @param n -> The current node being looked at
*   
*   Returns the size of the binary tree
*/
template <class T>
unsigned BinaryTree <T>::_getSize(Node<T> *n) const {

    if (n == NULL) { //Check for bottom most node

        return 0;

    } else {

        //Increment the size of the tree and move to the next node
        return(_getSize(n->left) + 1 + _getSize(n->right));

    }

}

/*
*   Function to calculate the height of the binary tree
*
*   @param n -> The current node being looked at
*   
*   Returns the height of the binary tree
*/

template <class T>
unsigned BinaryTree <T>::_getHeight(Node<T> *n) const {

    if (n == NULL) { //Check for empty tree

        return 0;

    } else {

         //Compute depth of each subtree
        int lh = _getHeight(n->left);
        int rh = _getHeight(n->right);

        //Use the larger one
        if (lh > rh) {

            return(lh + 1);

        } else {

            return(rh + 1);

        }

    }

}

/*
*   Function to insert a node into a binary tree
*
*   @param ptr -> Pointer to the root node
*   @param x   -> The value to insert into the tree
*
*/

template <class T>
void BinaryTree <T>::_Insert(Node<T>* &ptr, const T &x) {

    if (ptr == NULL) { // If empty tree, new node will be the root of the tree with value x

        ptr = new Node<T>(x);
        

    } else {

        SIDE s = rnd(); //Randomly select a side

        if (s == left_side) { //If left side is selected, insert new value into left side of tree

            _Insert(ptr->left, x);

        } else if (s == right_side) { //If right side is selected, insert new value into right side of tree

            _Insert(ptr->right, x); 

        }

    }

}

/*
*   Function to perform an inorder traversal on a binary tree
*
*   @param ptr   -> Pointer to the current node
*   @param print -> Call function to print values to stdout
*
*/

template <class T>
void BinaryTree <T>::_Inorder(Node<T> *ptr, void (*print)(const T&)) {

    if (ptr != NULL) {

        _Inorder(ptr->left, print);  //Traverse left subtree
        print(ptr->data);            //Print data
        _Inorder(ptr->right, print); //Traverse right subtree

    }

}

#endif // End of H_BINARYTREE
