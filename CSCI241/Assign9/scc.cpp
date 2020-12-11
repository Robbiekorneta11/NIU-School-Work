//*****************************************************************************
//
//  scc.cpp
//  CSCI 241 Assignment 9
//  Created by Robi Korneta z1816167
//
//The system timed out on me and when I recovered my file it was all screwed up
//*****************************************************************************

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include "sml.h"
#include "inpost.h"
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::istringstream;
using std::string;

/**
 * 
 * Symbol table entry.
 *
 ********************************************************************/
struct table_entry
{
    int symbol;
    char type;      // 'C' constant, 'L' Simple line number, 'V' variable
    int location;   // Simplesim address
};

/**
 * 
 * Simple compiler.
 *
 ********************************************************************/
class scc
{
public:
    
    static const int MEMORY_SIZE = 100;
    static const int SYMBOL_TABLE_SIZE = 1000;
    
    scc();
    void first_pass();
    void second_pass();
    void print_program() const;

private:
    
    int memory[MEMORY_SIZE];
    int data[MEMORY_SIZE];
    int ndata = 0;
    
    table_entry symbol_table[SYMBOL_TABLE_SIZE];
    int flags[MEMORY_SIZE];
    
    int next_instruction_addr = 0;
    int next_const_or_var_addr = MEMORY_SIZE - 1;
    int next_symbol_table_idx = 0;
};

int main()
{
    scc compiler;

    compiler.first_pass();

    compiler.second_pass();

    compiler.print_program();

    return 0;
}

/**
 * Initializes memory and flags array.
 *
 ********************************************************************/
scc::scc()
{
    // Initialize memory and flags arrays.
    std::fill_n(memory, MEMORY_SIZE, 4444);
    std::fill_n(flags, MEMORY_SIZE, -1);
    next_instruction_addr = 0;
    next_const_or_var_addr = MEMORY_SIZE - 1;
    next_symbol_table_idx = 0;
    ndata = 0;

}

/**
 * Performs first pass of compilation.
 *
 ********************************************************************/
void scc::first_pass()
{
    string buffer1, buffer2, command;

    int line_number;
    
    while (getline(cin, buffer1))
    {
        buffer2 = buffer1;
        istringstream ss(buffer1);
        
        ss >> line_number;
        
        // Code to add line number to symbol table
	symbol_table[next_symbol_table_idx].symbol = line_number;
	symbol_table[next_symbol_table_idx].type = 'L';
	symbol_table[next_symbol_table_idx].location = next_instruction_addr;
	next_symbol_table_idx++;
        
        // Extract the command from this statement.
        ss >> command;
      
       	//Check to see if we are out of bounds 	
	if (next_symbol_table_idx > 99) {

		cout << "*** ERROR: ran out of simplesim memory ***" << endl;

		   exit(1);
	} else {

        // Process the command.
        if (command == "input")
        {

	   char symb; //Get variable
	   ss >> symb;

	   int i = 0; //symbol table index
	   int loc = 0; //location of variable
	   bool found = false; //If we found variable in symbol table

	   while (i < next_symbol_table_idx) {

		   //If we found it in the table, then extract the location
		   if (symb == symbol_table[i].symbol && symbol_table[i].type == 'V') {

		   	found = true;
		   	loc = symbol_table[i].location;
		   	break;
		   }

	   	   i++;

	   }

	   //If we didn't find the symbol in the table, then allocate a new slot for it
	   if (found == false) {

		memory[next_const_or_var_addr] = 0;
		symbol_table[next_symbol_table_idx].symbol = symb;
		symbol_table[next_symbol_table_idx].type = 'V';
		symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
		loc = next_const_or_var_addr;
		next_symbol_table_idx++;
		next_const_or_var_addr--;

	   } else {}
 
	   //Read command
	   memory[next_instruction_addr] = READ * 100 + loc;
	   next_instruction_addr++;
            
	}
	//Data command
        else if (command == "data")
        {

	   int num;
	   ss >> num;

	   if (ndata < 99) {

	        data[ndata] = num;
	        ndata++;

	   } else {

		cout << "*** ERROR: too many data lines ***" << endl;
		exit(1);

	   }
            
        }
	//The command let will create a new variable and store it in the location
        else if (command == "let")
        {

		string postfix; //Postfix of buffer
		string infix; //Original buffer
		string var; //Variable
		bool found = false; //If variable was found in table
		int i = 0; //Symbol table index
		size_t j; //index for expression
		int next_stack_idx = 0; //Index of stack
		int postloc; //Postfix location
		int varloc; //Variable location

		ss >> var; //Get the variable

		char var1[var.size() + 1]; //Create char array to be able to read it
		var.copy(var1, var.size() + 1);
		var1[var.size()] = '\0';	
			
		//Check to see if it's in the symbol table
		while (i < next_symbol_table_idx) {

			if (var1[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

				found = true;
				varloc = symbol_table[i].location;
				break;

			}

			i++;

		}

		//Allocate spot for variable in memory and add to symbol table
		if (found == false) {

			memory[next_const_or_var_addr] = 0;
			symbol_table[next_symbol_table_idx].symbol = var1[0];
			symbol_table[next_symbol_table_idx].type = 'V';
			symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
			varloc = next_const_or_var_addr;
			next_const_or_var_addr--;
			next_symbol_table_idx++;
				
		}

		//Go through buffer to find where the equal sign is
		for (j = 0; j < buffer2.length(); j++) {

			if (buffer2[j] == '=') {

				for (size_t k = j + 2; k < buffer2.length(); k++) { 

					infix += buffer2[k]; //Append every element after equal sign to infix	

				}

				break;

			}

		}

		postfix = convert(infix); //Convert infix

		i = 0;

		//Go through postfix expression and evaluate each operator and operand
		for (size_t a = 0; a < postfix.length(); a++) {	

			if (isspace(postfix[a])) {} //Check for whitespace

			else if (islower(postfix[a])) { //Check for variable

				//Check in symbol table for the variable
				while (i < next_symbol_table_idx) {

					if (postfix[a] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

						found = true;
						postloc = symbol_table[i].location;
						break;

					}

					i++;

				}

				if (found == false) {

					memory[next_const_or_var_addr] = 0;
					symbol_table[next_symbol_table_idx].symbol = postfix[a];
					symbol_table[next_symbol_table_idx].type = 'V';
					symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
					postloc = next_const_or_var_addr;
					next_symbol_table_idx++;
					next_const_or_var_addr--;
				
				}

				//Load and store the variable into memory
				memory[next_instruction_addr] = LOAD * 100 + postloc;
				next_instruction_addr++;
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_stack_idx++;
				next_instruction_addr++;	

			} else if (isdigit(postfix[a])) { //Check for a constant

				while (i < next_symbol_table_idx) {

					if (postfix[a] == symbol_table[i].symbol && symbol_table[i].type == 'C') {

						found = true;
						postloc = symbol_table[i].location;
						break;

					}

					i++;

				}

				if (found == false) {

					memory[next_const_or_var_addr] = 0;
					symbol_table[next_symbol_table_idx].symbol = postfix[a];
					symbol_table[next_symbol_table_idx].type = 'C';
					symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
					postloc = next_const_or_var_addr;
					next_symbol_table_idx++;
					next_const_or_var_addr--;
				
				}

				//Push the constant onto the stack
				memory[next_instruction_addr] = LOAD * 100 + postloc;
				next_instruction_addr++;
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_stack_idx++;
				next_instruction_addr++;	



			} else if (postfix[a] == '+') { //Check for + operator

				//First, load the values
				memory[next_instruction_addr] = LOAD * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//Add the values
				memory[next_instruction_addr] = ADD * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//Push value back onto the stack
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_stack_idx++;
				next_instruction_addr++;

			} else if (postfix[a] == '*') {

				//Load the values
				memory[next_instruction_addr] = LOAD * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//Multiply the values
				memory[next_instruction_addr] = MULTIPLY * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//Push value back onto the stack
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_stack_idx++;
				next_instruction_addr++;

			} else if (postfix[a] == '-') {

				//Pop right operand
				memory[next_instruction_addr] = LOAD * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//temporarily store in memory
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -2;
				next_instruction_addr++;

				//Pop left operand
				memory[next_instruction_addr] = LOAD * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//Apply operator
				memory[next_instruction_addr] = SUBTRACT * 100;
				flags[next_instruction_addr] = -2;
				next_instruction_addr++;

				//Push back onto stack
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_stack_idx++;
				next_instruction_addr++;


			} else if (postfix[a] == '/') {

				//Pop right operand
				memory[next_instruction_addr] = LOAD * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//temporarily store in memory
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -2;
				next_instruction_addr++;

				//Pop left operand
				memory[next_instruction_addr] = LOAD * 100;
				next_stack_idx--;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_instruction_addr++;

				//Apply operator
				memory[next_instruction_addr] = DIVIDE * 100;
				flags[next_instruction_addr] = -2;
				next_instruction_addr++;

				//Push back onto stack
				memory[next_instruction_addr] = STORE * 100;
				flags[next_instruction_addr] = -3 - next_stack_idx;
				next_stack_idx++;
				next_instruction_addr++;

			}

		}

		//Get answer off top of the stack
		memory[next_instruction_addr] = LOAD * 100;
		flags[next_instruction_addr] = -3;
		next_instruction_addr++;
		memory[next_instruction_addr] = STORE * 100 + varloc;
		next_instruction_addr++;
            
        }
        else if (command == "if")
        {

		string lop; //Left operand
		string relop; //Relation operator
		string rop; //Right operand
		string g; //goto
		int linenum; //Line number
		int roploc = 0; //Right operand location
		int loploc = 0; //Left operand location
		int lineloc = 0; //Line number location
		bool found = false; //Check to see if anything was found in symbol table
		bool ropIsNum = false; //Check to see if right operand is a number
		bool lopIsNum = false; //Check to see if left operand is a number

		ss >> lop; //Store left operand
		ss >> relop; //Store relation operator
		ss >> rop; //Store right operand
		ss >> g; //Store goto
		ss >> linenum; //Store linenum


		//Convert to char so we can evaluate it
		char lop1[lop.size() + 1];
		lop.copy(lop1, lop.size() + 1);
		lop1[lop.size()] = '\0';	

		char rop1[rop.size() + 1];
		rop.copy(rop1, rop.size() + 1);
		rop1[rop.size()] = '\0';

		if (isdigit(lop1[0]) == 1 || lop1[0] == '-') {
			
			lopIsNum = true; //If left opearnd is a digit

		}
	
		if (isdigit(rop1[0]) == 1 || rop1[0] == '-') {
			
			ropIsNum = true; //If right operand is a digit

		}

		/* For each of the relational operators, we will see if the left and right operands
		 * are numbers. If they are, we will evaluate them as constants.
		 * If the operators are not numbers, and they are variables, we will look for their
		 * location in the symbol table and if they are not there, add it to the symbol table.
		 * Then we will add the operand to the memory stack*/	

		if (relop == ">") {

			int i = 0;

			if (lopIsNum == true) {

				int lopi = atoi(lop1); //Convert to integer since left operand is a number

			while (i < next_symbol_table_idx) {

				if (lopi == symbol_table[i].symbol && symbol_table[i].type == 'C') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lopi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {

			while (i < next_symbol_table_idx) {

				if (lop1[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}


			}
			
			int j = 0;
			found = false;

			if (ropIsNum == true) {

				int ropi = atoi(rop1);

			while (j < next_symbol_table_idx) {

				if (ropi == symbol_table[j].symbol && symbol_table[j].type == 'C') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = ropi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {


			while (j < next_symbol_table_idx) {

				if (rop1[0] == symbol_table[j].symbol && symbol_table[j].type == 'V') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = rop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}


			}

			memory[next_instruction_addr] = LOAD * 100 + roploc;
			next_instruction_addr++;
			memory[next_instruction_addr] = SUBTRACT * 100 + loploc;
			next_instruction_addr++;
			
			int k = 0;
			found = false;

			while (k < next_symbol_table_idx) {

				if (linenum == symbol_table[k].symbol && symbol_table[k].type == 'L') {

					found = true;
					lineloc = symbol_table[k].location;
					break;

				}

				k++;

			}

			if (found == false) {

				flags[next_instruction_addr] = linenum;

			}

			memory[next_instruction_addr] = BRANCHNEG * 100 + lineloc;
			next_instruction_addr++;
			found = false;

		} else if (relop == "<") {

			int i = 0;

			if (lopIsNum == true) {

			int lopi = atoi(lop1);

			while (i < next_symbol_table_idx) {

				if (lopi == symbol_table[i].symbol && symbol_table[i].type == 'C') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lopi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {

			while (i < next_symbol_table_idx) {

				if (lop1[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				

			}
			}

			int j = 0;
		
			if (ropIsNum == true) {	

				int ropi = atoi(rop1);

			while (j < next_symbol_table_idx) {

				if (ropi == symbol_table[j].symbol && symbol_table[j].type == 'C') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = ropi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
			}
			} else {

			while (j < next_symbol_table_idx) {

				if (rop1[0] == symbol_table[j].symbol && symbol_table[j].type == 'V') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = rop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;


			}
			}

			memory[next_instruction_addr] = LOAD * 100 + loploc;
			next_instruction_addr++;
			memory[next_instruction_addr] = SUBTRACT * 100 + roploc;
			next_instruction_addr++;

			int k = 0;
			found = false;

			while (k < next_symbol_table_idx) {

				if (linenum == symbol_table[k].symbol && symbol_table[k].type == 'L') {

					found = true;
					lineloc = symbol_table[k].location;
					break;

				}

				k++;

			}

			if (found == false) {

				flags[next_instruction_addr] = linenum;

			}

			memory[next_instruction_addr] = BRANCHNEG * 100 + lineloc;
			next_instruction_addr++;
			found = false;

		} else if (relop == "==") {

			int i = 0;

			if (lopIsNum == true) {

				int lopi = atoi(lop1);

			while (i < next_symbol_table_idx) {

				if (lopi == symbol_table[i].symbol && symbol_table[i].type == 'C') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lopi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {

			while (i < next_symbol_table_idx) {

				if (lop1[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}


			}

			int j = 0;

			if (ropIsNum == true) {

			int ropi = atoi(rop1);

			while (j < next_symbol_table_idx) {

				if (ropi == symbol_table[j].symbol && symbol_table[j].type == 'C') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = ropi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {

			while (j < next_symbol_table_idx) {

				if (rop1[0] == symbol_table[j].symbol && symbol_table[j].type == 'V') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = rop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}


			}

			memory[next_instruction_addr] = LOAD * 100 + loploc;
			next_instruction_addr++;
			memory[next_instruction_addr] = SUBTRACT * 100 + roploc;
			next_instruction_addr++;
			
			int k = 0;
			found = false;

			while (k < next_symbol_table_idx) {

				if (linenum == symbol_table[k].symbol && symbol_table[k].type == 'L') {

					found = true;
					lineloc = symbol_table[k].location;
					break;

				}

				k++;

			}

			if (found == false) {

				flags[next_instruction_addr] = linenum;

			}

			memory[next_instruction_addr] = BRANCHZERO * 100 + lineloc;
			next_instruction_addr++;
			found = false;


		} else if (relop == ">=") {

			int i = 0;

			if (lopIsNum == true) {

				int lopi = atoi(lop1);

			while (i < next_symbol_table_idx) {

				if (lopi == symbol_table[i].symbol && symbol_table[i].type == 'C') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lopi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {


			while (i < next_symbol_table_idx) {

				if (lop1[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}

			}
			
			int j = 0;

			if (ropIsNum == true) {

				int ropi = atoi(rop1);

			while (j < next_symbol_table_idx) {

				if (ropi == symbol_table[j].symbol && symbol_table[j].type == 'C') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = ropi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {

			while (j < next_symbol_table_idx) {

				if (rop1[0] == symbol_table[j].symbol && symbol_table[j].type == 'V') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = rop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}


			}

			memory[next_instruction_addr] = LOAD * 100 + roploc;
			next_instruction_addr++;
			memory[next_instruction_addr] = SUBTRACT * 100 + loploc;
			next_instruction_addr++;

			int k = 0;
			found = false;

			while (k < next_symbol_table_idx) {

				if (linenum == symbol_table[k].symbol && symbol_table[k].type == 'L') {

					found = true;
					lineloc = symbol_table[k].location;
					break;

				}

				k++;

			}

			if (found == false) {

				flags[next_instruction_addr] = linenum;

			}

			memory[next_instruction_addr] = BRANCHNEG * 100 + lineloc;
			next_instruction_addr++;
			memory[next_instruction_addr] = BRANCHZERO * 100 + lineloc;
			next_instruction_addr++;
			found = false;


		} else if (relop == "<=") {

			int i = 0;

			if (lopIsNum == true) {

				int lopi = atoi(lop1);

				while (i < next_symbol_table_idx) {

					if (lopi == symbol_table[i].symbol && symbol_table[i].type == 'C') {

						found = true;
						loploc = symbol_table[i].location;
						break;

					}

					i++;

				}

				if (found == false) {

					memory[next_const_or_var_addr] = 0;
					symbol_table[next_symbol_table_idx].symbol = lopi;
					symbol_table[next_symbol_table_idx].type = 'C';
					symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
					loploc = next_const_or_var_addr;
					next_symbol_table_idx++;
					next_const_or_var_addr--;
				
				}

			} else {

				while (i < next_symbol_table_idx) {

					if (lop1[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

						found = true;
						loploc = symbol_table[i].location;
						break;

					}

					i++;

				}

				if (found == false) {
				if (lop1[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

					found = true;
					loploc = symbol_table[i].location;
					break;

				}

				i++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = lop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}


			}
			
			int j = 0;

			if (ropIsNum == true) {

				int ropi = atoi(rop1);

			while (j < next_symbol_table_idx) {

				if (ropi == symbol_table[j].symbol && symbol_table[j].type == 'C') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = ropi;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				roploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}
			} else {

			while (j < next_symbol_table_idx) {

				if (rop1[0] == symbol_table[j].symbol && symbol_table[j].type == 'V') {

					found = true;
					roploc = symbol_table[j].location;
					break;

				}

				j++;

			}

			if (found == false) {

				memory[next_const_or_var_addr] = 0;
				symbol_table[next_symbol_table_idx].symbol = rop1[0];
				symbol_table[next_symbol_table_idx].type = 'V';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loploc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;
				
			}


			}

			memory[next_instruction_addr] = LOAD * 100 + loploc;
			next_instruction_addr++;
			memory[next_instruction_addr] = SUBTRACT * 100 + roploc;
			next_instruction_addr++;

			int k = 0;
			found = false;

			while (k < next_symbol_table_idx) {

				if (linenum == symbol_table[k].symbol && symbol_table[k].type == 'L') {

					found = true;
					lineloc = symbol_table[k].location;
					break;

				}

				k++;

			}

			if (found == false) {

				flags[next_instruction_addr] = linenum;

			}

			memory[next_instruction_addr] = BRANCHZERO * 100 + next_instruction_addr + 2;
			next_instruction_addr++;
			memory[next_instruction_addr] = BRANCH * 100 + lineloc;
			next_instruction_addr++;
			found = false;

		}	

            
        }
        else if (command == "goto")
        {
            
		int linenum; //Line number
		ss >> linenum; //Load line number

		int i = 0;
		bool found = false;

		while (i < next_symbol_table_idx) {

			//Check for line number in symbol table
			if (linenum == symbol_table[i].symbol && symbol_table[i].type == 'L') {

				found = true;
				memory[next_instruction_addr] = BRANCH * 100 + symbol_table[i].location;
				next_instruction_addr++;
				break;

			}

			i++;

		}

		if (found == false) {

			//If its not in the symbol table, then we have a forward reference
			memory[next_instruction_addr] = BRANCH * 100;
			flags[next_instruction_addr] = linenum;
			next_instruction_addr++;

		}


        }
        else if (command == "print")
        {

	   	string symb1; //Symbol
	   	ss >> symb1; //Load value into symbol
		char symb2[symb1.size() + 1]; //Convert to char
		symb1.copy(symb2, symb1.size() + 1);
		symb2[symb1.size()] = '\0';	

	   	int i = 0; 
	   	int loc = 0; //Location
	   	bool found = false;

	   	if (isdigit(symb2[0])) {

		   	int symb = stoi(symb1); //Convert to integer

	   		while (i < next_symbol_table_idx) {

				if (symb == symbol_table[i].symbol && symbol_table[i].type == 'C') {

		   			found = true;
		   			loc = symbol_table[i].location;
		   			break;

				}

	   			i++;

	   		}
	   
			//If not found, add to memory and symbol table
			if (found == false) {

				memory[next_const_or_var_addr] = symb;
				symbol_table[next_symbol_table_idx].symbol = symb;
				symbol_table[next_symbol_table_idx].type = 'C';
				symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
				loc = next_const_or_var_addr;
				next_symbol_table_idx++;
				next_const_or_var_addr--;

	   		} else {}

	   	} else {

			char symb[symb1.size() + 1];
			symb1.copy(symb, symb1.size() + 1);
			symb[symb1.size()] = '\0';

	   		while (i < next_symbol_table_idx) {

				if (symb[0] == symbol_table[i].symbol && symbol_table[i].type == 'V') {

		   			found = true;
		   			loc = symbol_table[i].location;
		   			break;

				}

	   			i++;

	   		}

	   	if (found == false) {

			memory[next_const_or_var_addr] = symb[0];
			symbol_table[next_symbol_table_idx].symbol = symb[0];
			symbol_table[next_symbol_table_idx].type = 'V';
			symbol_table[next_symbol_table_idx].location = next_const_or_var_addr;
			loc = next_const_or_var_addr;
			next_symbol_table_idx++;
			next_const_or_var_addr--;

	   	} else {}

	   }

 
	   memory[next_instruction_addr] = WRITE * 100 + loc;
	   next_instruction_addr++;
            
        }
        else if (command == "end")
        {

		//Check to make sure we are in bounds
	   	if (next_instruction_addr < 100) {
           
			memory[next_instruction_addr] = HALT * 100;
	   		next_instruction_addr++;

	   } else {

	   	cout << "*** ERROR: ran out of Simplesim memory ***" << endl;
	   	exit(1);
	   }

        }
        else if (command == "rem")
        {
            // Nothing to do for this instruction.
        }
	}
    }
}

/**
 * Performs second pass of compilation.
 *
 ********************************************************************/
void scc::second_pass()
{
	int j = 0;
	int lineloc; //Line location
	int idx = 0;

	//Loop through flags array
	for (int i = 0; i < 100; i++) {

		if (flags[i] > 0) { //Get forward references and execute the instruction

			while (j < next_symbol_table_idx) {

				if (flags[i] == symbol_table[j].symbol && symbol_table[j].type == 'L') {

					lineloc = symbol_table[j].location;
					memory[i] += lineloc;
					break;	

				}
				
				j++;	

			}

		} else if (flags[i] == -2) { //Represents special right operand memory location

			memory[i] += next_const_or_var_addr;
			next_const_or_var_addr--;

		} else if (flags[i] < -2) { //Represents memory location in stack

			idx = -3 - flags[i];
			memory[i] += next_const_or_var_addr - idx;

		}

	}

}

/**
 * Prints memory and data for the compiled SML program.
 *
 ********************************************************************/
void scc::print_program() const
{
    // Print memory array followed by data array.
    int j = 0;

    while (j < MEMORY_SIZE) {

	
	cout << setfill('0');
        cout << showpos << setw(5) << internal << memory[j] << endl;
        cout << setw(0);
	j++;

    }

    cout << "-" << "99999" << endl;

    cout << noshowpos;

    for (int i = 0; i < ndata; i++) {

	cout << data[i] << endl;

    }
    
}
