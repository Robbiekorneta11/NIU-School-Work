
//***********************************************
//
// mystack.cpp
// CSCI 241 Assignment 8
//
// Created by Robi Korneta Z1816167
//
//***********************************************

#include "mystack.h"
#include <cstddef>

//Default Constructor

mystack::mystack() {

	stk_size = 0; //Set stack size to 0
	stk_top = nullptr; //Set node to nullptr

}

//Copy constructor

mystack::mystack(const mystack& x) {

	stk_size = x.stk_size; //Copy stack size from parameter

	//If the stack size is 0, then set the node to nullptr
	//Else, set the stack size to the parameter stack size
	//and clone x into the stack
	if (stk_size == 0) {

		stk_top = nullptr;

	} else {

		stk_size = x.stk_size;
		clone(x);

	}

}

//Destructor

mystack::~mystack() {

	clear();

}


/**
 * overloading the = operator to copy the stack provided
 *
 * @params x a mystack object
 *
 * @returns pointer to this
 *
 * ************************************************/
mystack& mystack::operator=(const mystack& x) {
	
	if (this != &x) {

		clear();

		this->stk_size = x.stk_size;

		clone(x);

	}

	return *this;

}

//Return the stack size

size_t mystack::size() const {

	return stk_size;

}


/**
 * Check to see if the stack is empty
 *
 * @returns true if the stack is empty
 * 	    false if the stack is not empty
 * ************************************************/

bool mystack::empty() const {

	if (stk_size == 0) {

		return true;

	} else {

		return false;

	}

}

/**
 * Clears the stack
 * ************************************************/

void mystack::clear() {

	while (empty() == false) {

		pop();

	}

}

//Returns the top value of the stack

const int& mystack::top() const {

	return stk_top->value;

}

/**
 * pushes a new value to the top of the stack
 *
 * @params value the integer value being pushed to the stack
 * ************************************************/

void mystack::push(int value) {

	node *new_node = nullptr; //New node

	new_node = new node(value, new_node); //Load values into node linkage

	new_node->value = value; //Store value into node
	new_node->next = stk_top; //Store top value into nodes

	stk_top = new_node; //Add node to top of stack
	stk_size = stk_size + 1; //Increase stack size

}

/**
 * Pop the top value out of the stack
 * ************************************************/

void mystack::pop() {

	node *delete_node = stk_top;
	stk_top = stk_top->next;
	
	delete delete_node;

	stk_size = stk_size - 1;	

}

/**
 * copies the stack object to another stack
 *
 * @params x a mystack object to be copied
 * ************************************************/

void mystack::clone(const mystack& x) {

	node *last = nullptr; //Last value in node
	node *ptr = x.stk_top; //Pointer
	int ptrValue = ptr->value; //Pointer value

	while( ptr != nullptr ) {

		node *new_node = nullptr;
		new_node = new node(ptrValue, new_node); //Create new node

		//If we reach end of previous node, then that is the new top stack
		if (last == nullptr) {

			stk_top = new_node;

		} else {

			last->next = new_node;

		}

		last = new_node; //Set last to new node
		ptr = ptr->next; //Set pointer to next value

	}

}


