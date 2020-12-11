
#include <iostream>
#include <cstring>
#include "mystack.h"

mystack::mystack() {

	stackSize = 0;
	stackCapacity = 0;
	stackArray = nullptr;	

}

mystack::mystack(const mystack& x) {

	stackSize = x.stackSize;
	stackCapacity = x.stackCapacity;

	if (stackCapacity == 0) {

		stackArray = nullptr;

	} else {

		stackArray = x.stackArray;

	}

}

mystack::~mystack() {

	delete[] stackArray;

}

mystack& mystack::operator=(const mystack& x) {	
	
	this->stackSize = x.stackSize;
	this->stackCapacity = x.stackCapacity;
	this->stackArray = x.stackArray;

	return *this;

}

size_t mystack::capacity() const {

	return stackCapacity;

}

size_t mystack::size() const {

	return stackSize;

}

bool mystack::empty() const {

	if (stackSize == 0) {

		return true;

	} else {

		return false;

	}

}

void mystack::clear() {

	stackSize = 0;

}

void mystack::reserve(size_t n) {

	if (n < stackSize || n == stackCapacity) {

		return;

	}

	stackCapacity = n;
	char* temp;

	temp = new char[stackCapacity];

	memcpy(temp, stackArray, sizeof(stackCapacity));

	delete[] stackArray;

	stackArray = temp;

}

const char& mystack::top() const {

	return stackArray[stackSize - 1];

}

void mystack::push(char value) {

	if (stackSize == stackCapacity) {

		if (stackCapacity == 0) {
		
			reserve(1);

		} else {

			reserve(stackCapacity * 2);

		}

	}

	stackArray[stackSize] = value;
	stackSize = stackSize + 1;

}

void mystack::pop() {

	stackSize = stackSize - 1;

}
