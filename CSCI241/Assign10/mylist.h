//**************************************************************************
//
// mylist.h
// CSCI 241 Assignment 10
//
// Created by Robi Korneta (z1816167)
//
//***************************************************************************


#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

using std::cout;
using std::endl;

//Forward declaring class mylist
template <class T>
class mylist;

//Override std out operator
template <class T>
std::ostream& operator<<(std::ostream&, const mylist<T>&);

//Structure node
template <class T>
struct node {

	T value; //Value of the element
	node<T> *prev; //Pointer to previous node
	node<T> *next; //Pointer to next node

	//Constructor for the node
	node(const T& value, node<T>* prev = nullptr, node<T>* next = nullptr) {

		this->value = value;
		this->prev = prev;
		this->next = next;

	}

};

template <class T>
class mylist
{
	//std must be a friend of mylist to override it
	friend std::ostream& operator<< <>(std::ostream&, const mylist<T>&);

	private:
		node<T> *front_node; //Front node in mylist
		node<T> *back_node; //Back node in mylist
		size_t list_size; //Size of the list

	public:
		mylist();
		~mylist();
		mylist(const mylist<T>&);
		void clear();
		size_t size() const;
		bool empty() const;
		const T& front() const;
		T& front();
		const T& back() const;
		T& back();
		void push_front(const T&);
		void push_back(const T&);
		void pop_front();
		void pop_back();
		void clone(const mylist<T>&);
		mylist<T>& operator=(const mylist<T>&);
		bool operator<(const mylist<T>&) const;
		bool operator==(const mylist<T>&) const;


};

//Initialize all node pointers and list size to 0
template <class T>
mylist<T>::mylist() {
	
	front_node = 0;
	back_node = 0;
	list_size = 0;	
	
};

//Destructor will call clear
template <class T>
mylist<T>::~mylist() {

	clear();

}

//Copy constructor
template <class T>
mylist<T>::mylist(const mylist<T>& x) {

	front_node = nullptr;
	back_node = nullptr;
	list_size = 0;
	clone(x);

}

//Clears the list specified by continuously calling pop until mylist is empty
template <class T>
void mylist<T>::clear() {

	while (empty() == false) {

		pop_front();

	}

}

//Returns the size of the list
template <class T>
size_t mylist<T>::size() const {

	return list_size;

}

//Checks to see if the list is empty
template <class T>
bool mylist<T>::empty() const {

	if (list_size == 0) {

		return true;

	} else {

		return false;

	}

}

//Returns the front element of mylist
//If mylist object is empty, then it will throw an underflow exception
template <class T>
const T& mylist<T>::front() const {

	if (empty()) {

		throw std::underflow_error("underflow exception on call to front()");

	} else {

		return front_node->value;

	}

}

//Returns the front element of mylist
//If mylist object is empty, then it will throw an underflow exception
template <class T>
T& mylist<T>::front() {

	if (empty()) {

		throw std::underflow_error("underflow exception on call to front()");

	} else {

		return front_node->value;

	}

}

//Returns the back element of mylist
//If mylist object is empty, then it will throw an underflow exception
template <class T>
const T& mylist<T>::back() const {

	if (empty()) {

		throw std::underflow_error("underflow exception on call to back()");

	} else {

		return back_node->value;

	}
	
}

//Returns the back element of mylist
//If mylist object is empty, then it will throw an underflow exception
template <class T>
T& mylist<T>::back() {

	if (empty()) {

		throw std::underflow_error("underflow exception on call to back()");

	} else {

		return back_node->value;

	}

}

//The purpose of push front is to push values to the front of the node
//It will take a value and create a new node
//The function will then check to see if the list is empty
//If it is, then it will set the previous node to the new node
//If it is not, then the back node becomes the new node
template <class T>
void mylist<T>::push_front(const T& value) {
	
	node<T> *new_node = nullptr; //Initialize new node
	new_node = new node<T>(value, new_node, new_node); //Construct
	new_node->next = front_node; //Set next value of new node to front node

	if (!empty()) {

		front_node->prev = new_node;
		front_node = new_node;

	} else {

		back_node = new_node;
		front_node = new_node;

	}

	list_size = list_size + 1;

}

//The purpose of push back is to push values to the back of the node
//It will take a value and create a new node
//The function will then check to see if the list is empty
//If it is, then it will set the next node to the new node
//If it is not, then the front node and backnode becomes the new node
template <class T>
void mylist<T>::push_back(const T& value) {

	node<T> *new_node = nullptr; //Initialize new node
	new_node = new node<T>(value, new_node, new_node); //Construct new node
	new_node->prev = back_node; //Set previous value of new node to back node

	if (!empty()) {

		back_node->next = new_node;
		back_node = new_node;

	} else {

		front_node = new_node;
		back_node = new_node;

	}

	list_size = list_size + 1;	

}


//The purpose of pop front is to pop the front value off the node
//The function will check to see if the list is empty
//If the list is empty, then it will throw an underflow error
//If it is not empty, then the function sets the delete node to the front node
template <class T>
void mylist<T>::pop_front() {

	if (list_size == 0) {

		throw std::underflow_error("underflow exception on call to pop_front()");

	} else {

		node<T>* del_node = front_node; //Set delete node to front node
		front_node = del_node->next; //Set front node to the next delete node

		//If the front node is nullptr, then we set back node to null ptr and delete delnode
		if (front_node == nullptr) {

			back_node = nullptr;
			delete del_node;	

		} else {

			front_node->prev = nullptr; //Set the previous front node to nullptr
			delete del_node; //Remove the previous front node

		}	

		list_size = list_size - 1; //Decrease list size

	}


}

//The purpose of pop back is to pop the back value off the node
//The function will check to see if the list is empty
//If the list is empty, then it will throw an underflow error
//If it is not empty, then the function sets the delete node to the back node
template <class T>
void mylist<T>::pop_back() {

	if (list_size == 0) {

		throw std::underflow_error("underflow exception on call to pop_back()");

	} else {

		node<T>* del_node = back_node; //Create temp node to delete
		back_node = del_node->prev; //Set back node to the previous value
	
		//If back node is nullptr, then make front node null ptr
		if (back_node == nullptr) {

			front_node = nullptr;
			delete del_node;

		} else {

			back_node->next = nullptr; //If not, then set next node to null ptr
			delete del_node; //Delete the node

		}

		list_size = list_size - 1;

	}	


	
}

//Overload the = operator
template <class T>
mylist<T>& mylist<T>::operator=(const mylist<T>& x) {

	//If it is not equal already, then clone it
	if (this != &x) {

		clear();
		clone(x);

	}

	return *this;

}

//Overload the == operator
//Return the boolean value of the comparison
template <class T>
bool mylist<T>::operator==(const mylist<T>& rhs) const {

	node<T> *ptr = rhs.front_node; //Pointer to rhs
	node<T> *ptr1 = this->front_node; //Pointer to this
	
	bool areEqual = false; //Check to see if they are equal
	size_t s = rhs.list_size; //Get size of rhs
	size_t s1 = this->list_size; //Get size of this

	//If the sizes are not equal, then this automatically means the two lists are not equal
	if (s != s1) {

		return false;

	}

	//Iterate through the lists
	while (ptr != nullptr) {

		//Compare the two values
		if (ptr->value == ptr1->value) {

			areEqual = true;

		} else {

			//If one value is not equal, then the lists are not equal
			areEqual = false;
			break;

		}

		ptr = ptr->next; //Move to next pointer
		ptr1 = ptr1->next;

	}

	//If the sizes and all the values are equal
	if (s == s1 && areEqual) {

		return true;

	} else {

		return false;

	}

}

//Overload < operator
//It will check to see if the argument is less than the list
//Pointed to by this
//It will return true of false
template <class T>
bool mylist<T>::operator<(const mylist<T>& rhs) const {

	node<T> *ptr = rhs.front_node; //argument list
	node<T> *ptr1 = this->front_node; //this list

	size_t s = rhs.list_size; //size of argument list
	size_t s1 = this->list_size; //size of this list

	bool a = false; //Resulting value of the function

	//To avoid segmentation fault, find which list is smaller
	if (s < s1) {

		//Loop through the lists
		while (ptr != nullptr) {

			//Check to see if rhs is greater than this
			if (ptr->value > ptr1->value) {

				a = true; //If it is set it to true
				break; //Break out of loop because this is less than rhs

			} else if (ptr->value == ptr1->value) {

				a = false; //If they are equal, then move to next element

			} else {

				a = false; //Otherwise rhs is less than this

			}

			ptr = ptr->next; //Move to next node
			ptr1 = ptr1->next;

		}

	} else {

		//Do the same as above, but s1 is less than s
		while (ptr1 != nullptr) {

			if (ptr->value > ptr1->value) {

				a = true;
				break;	

			} else if (ptr->value == ptr1->value) {

				a = false;

			} else {

				a = false;

			}

			ptr = ptr->next;
			ptr1 = ptr1->next;

		}


	}

	return a;

}

//Overload the std out operator to print out the list values
template <class T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {

	node<T> *ptr = obj.front_node; //Get the argument node

	//Iterate through list and display the values
	while (ptr != nullptr) {

		os << ptr->value;
		os << " ";
		ptr = ptr->next;

	}
		
	return os;

}

//Clone one list with another
template <class T>
void mylist<T>::clone(const mylist<T>& x) {

        node<T> *ptr = x.front_node; //Pointer

        while( ptr != nullptr ) {

                push_back(ptr->value);
                ptr = ptr->next; //Set pointer to next value

        }

}


#endif
