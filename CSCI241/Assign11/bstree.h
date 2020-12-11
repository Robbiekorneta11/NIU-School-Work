//***************************************
//
// bstree.h
// CSCI 241 Assignment 11
//
// Created by Robi Korneta z1816167
//
//***************************************

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stack>
#include <queue>

using std::cout;
using std::endl;

//Constructing node
template<class K, class V>
struct node {

	K key;
	V value;		
	node<K, V> *left;
	node<K, V> *right;

	node(const K& key = K(), const V& value = V(), node<K, V>* left = nullptr, node<K, V>* right = nullptr) {

		this->key = key;
		this->value = value;
		this->left = left;
		this->right = right;

	}

};

//Class bstree represents  a binary search tree
template<class K, class V>
class bstree {

	private:
		node<K, V> *root; //Root node
		size_t t_size; //Size of tree

	public:
		bstree();
		~bstree();
		bstree(const bstree<K, V>&);
		bstree<K, V>& operator=(const bstree<K, V>&);
		void clear();
		size_t size() const;
		size_t height() const;
		bool empty() const;
		const K& min() const;
		const K& max() const;
		bool insert(const K&, const V&);
		bool remove(const K&);
		const node<K, V>* find(const K&) const;
		void preorder() const;
		void inorder() const;
		void postorder() const;
		void level_order() const;
		void destroy(const node<K, V>*);
		node<K, V>* clone(const node<K, V>*);

};

//Constructor to initialize bstree values to 0
template<class K, class V>
bstree<K, V>::bstree() {

	root = nullptr;
	t_size = 0;

}

//Deconstructor
template<class K, class V>
bstree<K, V>::~bstree() {

	clear();

}

//Copy constructor
template<class K, class V>
bstree<K, V>::bstree(const bstree<K, V>& x) {

	t_size = x.t_size;
	root = clone(x.root);

}

//Copy assignment function
template<class K, class V>
bstree<K, V>& bstree<K, V>::operator=(const bstree<K, V>& x) {

	//Check to see if it is not equal to x
	if (this != &x) {

		clear(); //Clear the bstree
		t_size = x.t_size; //Set sizes equal to each other
		root = clone(x.root); //Clone

	}

	return *this;

}

// This will clear the bstree that calls it
// It takes no parameters and returns nothing
template<class K, class V>
void bstree<K, V>::clear() {

	destroy(root); //Destroy the root
	root = nullptr; //Set root to nullptr
	t_size = 0; //Set size to 0

}

//Returns the size of the bstree
template<class K, class V>
size_t bstree<K, V>::size() const {

	return t_size;

}

//Returns the height of the bstree
template<class K, class V>
size_t bstree<K, V>::height() const {

	//If the bstree is empty, then its height is 0
	if (empty()) {

		return 0;

	}
	
	std::queue<node<K, V>*> q; //Create an empty queue

	q.push(root); //Put root into the queue
	size_t height = 0; //Initialize height

	//In this while loop, we will go through each node until
	//There are no nodes left
	while(1) {

		int nodecount = q.size(); //Node count is equal to the size of the q

		if (nodecount == 0) { //When node count is 0, then the height will be returned

			return height;

		}

		height++; //Increment height

		while (nodecount > 0) {

			node<K, V> *p = q.front(); //Set the pointer node to the front queue
			q.pop(); //Pop front node off
			if (p->left != nullptr) {

				q.push(p->left); //Put the next node into the queue

			}

			if (p->right != nullptr) {

				q.push(p->right);

			}

			nodecount--; //Decrement node count

		}

	}

}

//This function will check to see if the bstree if empty
//Takes no parameters
//Returns true if the tree size is 0
//Returns false if the tree size is not 0
template<class K, class V>
bool bstree<K, V>::empty() const {

	if (t_size == 0) {

		return true;

	} else {

		return false;

	}

}

//This function will find the minimum key in the tree
//Takes no parameters
//Returns the minimum key
template<class K, class V>
const K& bstree<K, V>::min() const {

	node<K, V>* p = root; //Pointer to root node

	while (p->left != nullptr) {

		p = p->left; //Loop through to find the smallest element

	}

	return p->key; //Return the smallest key

}

//This function will find the maximum key in the tree
//Takes no parameters
//Returns the maximum key
template<class K, class V>
const K& bstree<K, V>::max() const {

	node<K, V> *p = root; //Pointer to root node

	while (p->right != nullptr) {

		p = p->right; //Loop through to find max element

	}

	return p->key; //Return max key

}

//This function will insert a a key and value into the bstree
//Parameter key is the key to insert
//Parameter value is the value to insert
//Returns true when it is successful
//Returns false if the key already exists
template<class K, class V>
bool bstree<K, V>::insert(const K& key, const V& value) {

	node<K, V> *p = root; //Pointer to root node
	node<K, V> *parent = nullptr; //Set up parent node pointer

	while (p != nullptr && key != p->key) {

		parent = p; //Set parent to p

		//Check to see if the key already exists
		if (key < p->key) {

			p = p->left;

		} else {

			p = p->right;

		}

	}

	//If the pointer already exists return false
	if (p != nullptr) {

		return false;

	}

	node<K, V> *new_node = nullptr; //Set up new node
	new_node = new node<K, V>(key, value, new_node, new_node);

	if (parent == nullptr) {

		root = new_node; //If there is no parent, then new node is root node

	} else {

		//Put new node key into left subtree if new node key value is less than parent
		if (new_node->key < parent->key) {
		
			parent->left = new_node;

		} else {

			parent->right = new_node;

		}
	}

	t_size = t_size + 1; //Increment tree size

	return true; //Return true because insertion was successful

}

//Remove will remove the specified key from the tree
//Parameter key is the key to remove
//Returns true if successful
//Returns false if failure
template<class K, class V>
bool bstree<K, V>::remove(const K& key) {

	node<K, V> *p = root; //Pointer to root node
	node<K, V> *parent = nullptr; //Point to parent node
	node<K, V> *replace = nullptr; //Pointer to replacment node
	node<K, V> *replace_parent = nullptr; //Pointer to the parent replacement node

	//Search for the key to remove
	while (p != nullptr && key != p->key) {

		parent = p; //Parent is p now

		if (key < p->key) {

			p = p->left;

		} else {

			p = p->right;

		}

	}

	//If node was not found then it failed
	if (p == nullptr) {

		return false;

	}

	//Replace p with right child if p does not have a left child
	if (p->left == nullptr) {

		replace = p->right;

	} else if (p->right == nullptr) {

		replace = p->left; //Replace p with left child if no right child

	} else {

		//If p has 2 children
		replace_parent = p;
		replace = p->left;

		//Go all the way to the right
		while (replace->right != nullptr) {

			replace_parent = replace;
			replace = replace->right;

		}

		//If we went all the way to the right, then make the replacement
		//node's left child the right child of its parent
		//Then make the left child of p the replacement's left child
		if (replace_parent != p) {

			replace_parent->right = replace->left;
			replace->left = p->left;

		}

		replace->right = p->right;

	}

	//Connect replacement node to parent node
	if (parent == nullptr) {

		root = replace;

	} else {

		if (p->key < parent->key) {

			parent->left = replace;

		} else {

			parent->right = replace;

		}

	}

	delete p; //Delete the node
	t_size = t_size - 1; //Decrement size

	return true; //Success

}

//find the specified key in the tree
//Param key is the key to find
//Returns the pointer to root
template<class K, class V>
const node<K, V>* bstree<K, V>::find(const K& key) const {

	node<K, V> *p = root;

	//Search for the matching key
	while (p != nullptr && key != p->key) {

		if (key < p->key) {

			p = p->left;

		} else {

			p = p->right;

		}

	}

	return p; //Either returns nullptr if the key is not found or the node where the key found

}

//Perform a preorder traversal on the bstree
template<class K, class V>
void bstree<K, V>::preorder() const {

	node<K, V> *p = root; //Point to root node
	std::stack<node<K, V>* > s; //Create a new stack

	//Go all the way to the left
	while (p != nullptr || !s.empty()) {

		while (p != nullptr) {

			cout << p->key << ": " << p->value << endl; //Print the key and value
			s.push(p); //Push pointer onto the stack
			p = p->left; //Traverse the nodes left subtree

		}

		p = s.top(); //Backtrack one level
		s.pop(); //Pop top off the stack

		p = p->right; //Traverse right subtree

	}

}

//Perform an inorder traversal on the bstree
template<class K, class V>
void bstree<K, V>::inorder() const {

	node<K, V> *p = root; //Pointer to root node
	std::stack<node<K, V>* > s; //New stack

	while (p != nullptr || !s.empty()) {

		//Go all the way to the left
		while (p != nullptr) {

			//Traverse node's left subtree
			s.push(p);
			p = p->left;

		}

		p = s.top(); //Backtrack one level
		s.pop(); //Pop top off the stack

		cout << p->key << ": " << p->value << endl; //Print out key and value

		p = p->right; //Traverse node right subtree

	}


}

//Perform a postorder traversal on the bstree
template<class K, class V>
void bstree<K, V>::postorder() const {

	node<K, V> *last_visited = nullptr; //last visited node
	node<K, V> *p = root; //Pointer to root
	std::stack<node<K, V>*> s; //New stack

	while (p != nullptr && last_visited != root) {

		//Go all the way to the left
		while (p != nullptr && p != last_visited) {

			//Traverse left subtree
			s.push(p);
			p = p->left;

		}

		p = s.top(); //Backtrack one level
		s.pop(); //Pop off the top

		if (p->right == nullptr || p->right == last_visited) {

			cout << p->key << ": " << p->value << endl; //Print key and value
			last_visited = p; //Set last visited to current node

		} else {

			s.push(p); //Otherwise, traverse node's right subtree
			p = p->right;

		}

	}


}

//Perform a level order traversal on the bstree
template<class K, class V>
void bstree<K, V>::level_order() const {

	std::queue<node<K, V>*> q; //set up queue
	node<K, V> *p = nullptr; //Pointer to node

	//If tree is empty, return
	if (root == nullptr) {

		return;

	}

	q.push(root);

	while (!q.empty()) {

		//Remove front item from queue and visit it
		p = q.front();
		q.pop();

		cout << p->key << ": " << p->value << endl;

		//Insert left child of p into queue
		if (p->left != nullptr)
			q.push(p->left);

		//Insert right child of p into queue
		if (p->right != nullptr)
			q.push(p->right);

	}

}

//Recursively deletes the nodes of a bstree object
template<class K, class V>
void bstree<K, V>::destroy(const node<K, V>* p) {

	if (p != nullptr) {

		destroy(p->left); //Recursion
		destroy(p->right);

		delete p; //Delete node pointed to by p
	}

}

//Revursively copies the nodes of a bstree object
template<class K, class V>
node<K, V>* bstree<K, V>::clone(const node<K, V>* p) {

	if (p != nullptr) {

		//Make copy of the node pointed to by p
		node<K, V> *new_node = nullptr;
		new_node = new node<K, V>(p->key, p->value, new_node, new_node);

		new_node->key = p->key;
		new_node->value = p->value;

		new_node->left = clone(p->left); //Recursively copy
		new_node->right = clone(p->right);

		return new_node;

	} else {

		return nullptr;

	}

}

#endif
