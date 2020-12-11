
//******************************************************************
//
// eval.cpp
// CSCI 241 Assignment 8
//
// Created by Robi Korneta Z1816167
//
//*******************************************************************


#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include "mystack.h"
#include <assert.h>
#include <cmath>

using std::string;
using std::stringstream;

/**
 * Evaluate the postfix string and return its result
 *
 * @param postfix The string being passed into the function
 *
 * @return an integer representing the result
 * *************************************************************/

int evaluate(const string& postfix) {

	string tok; //Token value
	stringstream ss(postfix); //String stream being read in
	mystack s; //Stack object

	while (ss >> tok) {

		char t0 = tok.at(0); //Variable to detect if it is a digit, operator, or letter

		//If it is a digit, then push the value into the stack
		if (isdigit(t0)) {

			s.push(std::stoi(tok));	

		} else if (islower(t0)) { //If it is a letter, push it into the stack

			s.push(t0-'a');	

		} else if (t0 == '~') { //If the ~ operator, turn the value negative
		       
			int i = s.top(); //Get the value
			s.pop(); //Pop it off the top
			s.push(-i); //Turn the value negative
		
		} else {

			int right = s.top(); //Right side of the expression
			s.pop(); //Pop to remove value
			int left = s.top(); //Left side of expression
			s.pop(); //Pop to remove valu
			
			//In this switch statement, we will check for the operators
			//If we get a matching operator, then we will perform the
			//Specified math function
			switch(t0) {

				case '+':
					s.push(left + right);
					break;
				case '-':
					s.push(left - right);
					break;
				case '*':
					s.push(left * right);
					break;
				case '/':
					if (right == 0) {

						s.push(0);
						std::cout << "*** Division by 0 ***" << std::endl;

					} else {

						s.push(left / right);

					}
					break;
				case '^':
					s.push(pow(left, right));
					break;
				default:
					std::cerr << "Error " << t0 << std::endl;
					assert(0 && "illegal operator");

			}

		}

	}

	return s.top();

}
