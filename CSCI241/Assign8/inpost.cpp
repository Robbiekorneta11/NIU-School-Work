
//********************************************
//
// inpost.cpp
// CSCI 241 Assignment 8
//
// Created by Robi Korneta Z1816167
//
//********************************************

#include <iostream>
#include <cctype>
#include "inpost.h"
#include "mystack.h"
#include <assert.h>
#include <string>

using namespace std;

int getOptScore(char);
int getOptScore1(char);


/**
 * Convert an infix string to a postfix
 *
 * @params infix the string to be converted
 *
 * @returns postfix the string that was fixed
 *
 * ************************************************/

string convert(const string& infix) {

	mystack opstack; //Opstack to hold operators
	string postfix; //Resulting string
	int length = infix.length(); //Length of infix
	int opscore; //Score of the operator

	//Loop through string
	for (int i = 0; i < length; i++) {

		//Check for space
		if (isspace(infix[i]) != 0 ) {


		} else if (isdigit(infix[i])) { //Check to see if digit

			postfix += infix[i]; //Append to postfix
			
			//If the next element is not a digit, then add a space
			if (!isdigit(infix[i + 1])) {

				postfix += " ";

			}

		} else if (islower(infix[i])) { //If the element is a letter

			postfix += infix[i]; //Append the letter to postfix
			postfix += " "; //Add a space
		
		} else if (infix[i] == ')') { //If the element is a )
		       
			while (opstack.top() != '(') {

				postfix += opstack.top(); //Add the top value to postfix
				postfix += " "; //Add a space
				opstack.pop(); //Remove value from stack

			}

			opstack.pop(); //Pop top value from stack
		
		} else {

			opscore = getOptScore(infix[i]); //Get the opscore

			//If the opstack is empty or the opscore is larger than the opscore at
			//the top of the stack
			if (opstack.empty() || opscore > getOptScore1(opstack.top())) {

				opstack.push(infix[i]); //Push value onto stack

			} else {

				//While the stack is not empty and the opscore is less than
				//the opscore of the top stack
				while (!opstack.empty() && opscore < getOptScore1(opstack.top())) {

					postfix += opstack.top(); //Append top value of opstack
					postfix += " ";
					opstack.pop(); //Pop value

				}

				opstack.push(infix[i]); //Push value into opstack
				
			}

		}

	}

	//Push the remaining elements into the stack
	while (opstack.empty() == false) {

		postfix += opstack.top();
		postfix += " ";
		opstack.pop();

	}

	return postfix;

}


/**
 * Calculate the operator score
 *
 * @params op the operator passed into the function
 *
 * @returns the opscore
 *
 * ************************************************/

int getOptScore(char op) {

	int opscore;
	
	switch(op) {

		case '~':
	      	opscore = 6;
		break;

		case '^':
	      	opscore = 6;
		break;

		case '*':
	      	opscore = 3;
		break;

		case '/':
	      	opscore = 3;
		break;

		case '+':
	      	opscore = 1;
		break;

		case '-':
	     	opscore = 1;
		break;

		case '(':
	      	opscore = 100;
		break;

		default:
		cerr << "Invalid Operator: " << op << endl;
		assert(0 && "illegal operator");
	      	opscore = -1;

	}

	return opscore;

}


/**
 * Compare the opscore of the stack to the opscore of the current
 * element in the infix string
 *
 * @params op The operator passed into the function
 *
 * @returns opscore the opscore result
 * ************************************************/

int getOptScore1(char op) {

	int opscore;
	
	switch(op) {

		case '~':
	      	opscore = 5;
		break;

		case '^':
	      	opscore = 5;
		break;

		case '*':
	      	opscore = 4;
		break;

		case '/':
	      	opscore = 4;
		break;

		case '+':
	      	opscore = 2;
		break;

		case '-':
	     	opscore = 2;
		break;

		case '(':
	      	opscore = 0;
		break;

		default:
		cerr << "Invalid Operator: " << op << endl;
		assert(0 && "illegal operator");
	      	opscore = -1;

	}

	return opscore;

}
