
#include <iostream>
#include <ctype.h>
#include "inpost.h"
#include "mystack.h"
#include <cstring>

using namespace std;

string inpost::convert(const string& infix) {

	mystack opstack;
	string postfix;
	int length = infix.length();
	opstack.push('N');

	for( int i = 0; i < length; i++ ) {

		if (isspace(infix[i])) {

		} else if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z')) {

			postfix += infix[i];


		} else if (infix[i] == '(') {

			opstack.push('(');
		
		} else if (opstack.top() != 'N' && infix[i] == ')') {

			while( opstack.top() != '(' ) {

				char op = opstack.top();
				opstack.pop();
				postfix += op;

			}

			if (opstack.top() == '(') {

				//char op = opstack.top();
				opstack.pop();

			}

		} else {

			int opscore;
			int topscore;

			if (infix[i] == '~' || infix[i] == '^')
				opscore = 3;
			else if (infix[i] == '*' || infix[i] == '/')
				opscore = 2;
			else if (infix[i] == '+' || infix[i] == '-')
				opscore = 1;
			else
				opscore = 0; //Error

			if (opstack.top() == '~' || opstack.top() == '^')
				topscore = 3;
			else if (opstack.top() == '*' || opstack.top() == '/')
				topscore = 2;
			else if (opstack.top() == '+' || opstack.top() == '-')
				topscore = 1;
			else
				topscore = 0; //Error

			while( opstack.top() != 'N' && opscore <= topscore) {

				char op = opstack.top();
				opstack.pop();
				postfix += op;

			}

			opstack.push(infix[i]);

		}

	}

	while( opstack.top() != 'N' ) {

		char op = opstack.top();
		opstack.pop();
		postfix += op;

	}

	return postfix;

}
