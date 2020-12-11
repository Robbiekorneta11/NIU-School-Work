
//*****************************************
//
// mystack.h
// CSCI 241 Assignment 8
//
// Created by Robi Korneta Z1816167
//
//*****************************************

#ifndef mystack_h
#define mystack_h

#include <cstddef>

//Creating a node structure

struct node {

	int value;
	node* next;

	node(int value, node* next = nullptr) {

		this->value = value;
		this->next = next;

	}

};

//Declaring private variables and public functions for mystack class

class mystack {

	private:
		node *stk_top;
		size_t stk_size;

	public:
		mystack();
		mystack(const mystack&);
		~mystack();
		mystack& operator=(const mystack&);
		size_t size() const;
		bool empty() const;
		void clear();
		const int& top() const;
		void push(int);
		void pop();
		void clone(const mystack&);

};

#endif
