//
//  simplesim.cpp
//  CSCI 241 Assignment 4
//
//  Created by Robbie Korneta z1816167
//
//

#include <iostream>
#include <iomanip>
#include "sml.h"
#include "simplesim.h"

using namespace std;

/**
* Initialize the sml program into the Simplesim's memory
*
* @return true if no errors occured
*	  false if error occured
*
******************************************************/

bool simplesim::load_program() {

    int n = 0; //Index of memory array
    bool error_occured = false; //Tracks if an error occured

    for (int i = 0; i < 100; i++) {

	memory[i] = 4444; //Initialize the memory values to 4444

    }

    //Loading standard input file words to memory
    while (cin >> memory[n]) {

	//Check to see if the number of values is outside the bounds
        if (n > 100) {

            cout << "*** ABEND: pgm load: pgm too large ***" << endl << endl;
	    error_occured = true; //Am error occured
	    break;

        } else if (memory[n] == -99999) { //Check to see if the program ended

	    memory[n] = 4444; //Do not load -99999 into memory
	    n++; //Increment n
	    error_occured = false; //no error occured
            break;

        } else if ((memory[n] > 9999 || memory[n] < -9999) && memory[n] != -99999) {
	    //Check to see if word is outside the acceptable vlaues
	    memory[n] = 4444; //Don't load it into memory
            cout << "*** ABEND: pgm load: invalid word ***" << endl << endl;
            error_occured = true; //Error occured
	    break;

        } else {

            n++; //Increment n

        }

    }

    if (error_occured == true) {

	return false; //Go directly to dump

    } else {

	return true; //Go to execute_program()

    }

}

/**
* Executed the instructions given by the word sequence
*
* @returns void
*
*************************************************/

void simplesim::execute_program() {

    int temp; //Temporary variable to hold arithmetic operation
    bool done = false; //Go through while loop

    while (!done)
    {
        // instruction fetch
        if (instruction_counter >= 0 && instruction_counter <= 99) {

            instruction_register = memory[instruction_counter]; //Loading instruction regesiter
            operation_code = instruction_register / 100; //Loding the operation code
            operand = instruction_register % 100; //Loading the operand

        } else {

	    //If the instruction count is outside the allowable bounds
            cout << "*** ABEND: addressability error ***" << endl << endl;
	    return;

        }

        // instruction execute

        switch (operation_code)
        {
	    //If Operation  code is 1, read the memory at operand
            case READ:
	       while (cin >> memory[operand]) {

	       //If the value is inside of bounds, display the read value
	       if (memory[operand] >= -9999 && memory[operand] <= 9999) {

			cout << setfill('0');
			cout << "READ: " << showpos << setw(5) << internal << memory[operand] << endl;

		    } else {

			//If value is outside of bounds, an error occured
			memory[operand] = 0;
			cout << "*** ABEND: illegal input ***" << endl << endl;
			return;

		      }

		operand++; //Increment operand

		}

		instruction_counter++; //Increment counter
		break;

	    //Write the value to standard output
            case WRITE:
                cout << setfill('0');
                cout << showpos << setw(5) << internal << memory[operand] << endl;

		instruction_counter++; //Increment counter
		break;

	    //Store the accumulator value into the memory location at operand
            case STORE:
                memory[operand] = accumulator;

		instruction_counter++;
		break;

	    //Load the value from memory location at operand into accumulator
            case LOAD:
                accumulator = memory[operand];

		instruction_counter++;
		break;

	    //Add the accumulator value and memory value at operand
            case ADD:
                temp = accumulator + memory[operand]; //Temp value to hold result

		//Check to see if temp is less than -9999
		//If it is then it is a bad value and we throw an error message
                if (temp < -9999) {

                    cout << "*** ABEND: underflow ***" << endl << endl;
		    return;

                } else if (temp > 9999) { //If it's greater than 9999 its a bad value

                    cout << "*** ABEND: overflow ***" << endl << endl;
		    return;

                } else { //If it's in between the bounds then set accumulator to temp

                    accumulator = temp;

                }

		instruction_counter++;
		break;

	    //Subtract the value at memory location from accumulator
            case SUBTRACT:
                temp = accumulator - memory[operand]; //Hold result

		//Check for underflow
                if (temp < -9999) {

                    cout << "*** ABEND: underflow ***" << endl << endl;
		    return;

		//Check for overflow
                } else if (temp > 9999) {

                    cout << "*** ABEND: overflow ***" << endl << endl;
		    return;

                } else { //If it's in the bounds, set accumulator to temp

                    accumulator = temp;

                }

		instruction_counter++;
		break;

	    //Multiply the accumulator and memory value
            case MULTIPLY:
                temp = accumulator * memory[operand]; //Hold result

		//Check for underflow
                if (temp < -9999) {

                    cout << "*** ABEND: underflow ***" << endl << endl;
		    return;

                } else if (temp > 9999) { //Check for overflow

                    cout << "*** ABEND: overflow ***" << endl << endl;
		    return;

                } else { //If in the bounds, set accumulator to temp 

                    accumulator = temp;

                }

		instruction_counter++;
		break;

	    //Divide the accumulaor by the value in memory
            case DIVIDE:
		//Check to see if the divisor is 0
                if (memory[operand] == 0) {

                    cout << "*** ABEND: attempted division by 0 ***" << endl << endl;
		    return;

                } else { //If it is not then perform division

                    accumulator = accumulator / memory[operand];

                }

		instruction_counter++;
		break;

	    //Modify value of instruction_counter
            case BRANCH:
                instruction_counter = operand;
		break;

	    //Check to see if accumulator is 0
	    //If it is, then set instruction_counter to the operand
            case BRANCHZERO:
                if (accumulator == 0)
                    instruction_counter = operand;
                else
                    instruction_counter++;

		break;

	    //Check to see if the accumulator is negative
	    //If it is set the counter to the operand value
            case BRANCHNEG:
                if (accumulator < 0)
                    instruction_counter = operand;
                else
                    instruction_counter++;

		break;

	    //Terminate the execution of the program and go to dump
            case HALT:
                cout << "*** Simplesim execution terminated ***" << endl << endl;
                return;

		break;

	    //Default case
            default:
                cout << "*** ABEND: invalid opcode ***" << endl << endl;
                return;

        }

    }

}

/**
*
* Print out the values of the accumulator, instruction_counter,
* instruction_register, operation_code, and operand
*
* @return void
*
***************************************************************/

void simplesim::dump() const {

    int f = 0; //Memory index

    //Print out values in formatted way
    cout << "REGISTERS:" << endl;
    cout << setfill('0');
    cout << "accumulator:\t\t" << showpos << setw(5) << internal << accumulator << endl;
    cout << "instruction_counter:\t"  << noshowpos << setw(2) << instruction_counter << endl;
    cout << "instruction_register:\t" << showpos << setw(5) << instruction_register << endl;
    cout << "operation_code:\t\t"  << noshowpos << setw(2) << operation_code << endl;
    cout << "operand:\t\t"  << setw(2) << operand << endl << endl;
    cout << setfill(' ');

    cout << "MEMORY:" << endl;

    //Print out top row 0-9
    for(int i = 0; i < 10; i++) {

	cout << noshowpos; //Get rid of plus/negative sign

        if( i == 0 ) {

            cout << setw(8) << i;

        } else {

            cout << setw(6) << i;

        }

    }

    cout << endl;

    int k = 0; //Total count of values being printed

    //Printing out the values of memory
    while(k < 110) {

	cout << noshowpos;
	cout << setfill(' ');

        if(k == 0) {

            cout << setw(2) << internal << 0;

        } else if(k == 11) {

            cout << endl;
            cout << setw(2) << internal << 10;

        } else if(k == 22) {

            cout << endl;
            cout << setw(2) << internal << 20;

        } else if(k == 33) {

            cout << endl;
	    cout << setw(2) << internal << 30;

        } else if(k == 44) {

            cout << endl;
            cout << setw(2) << internal << 40;

        } else if(k == 55) {

            cout << endl;
            cout << setw(2) << internal << 50;

        } else if(k == 66) {

            cout << endl;
            cout << setw(2) << internal << 60;

        } else if(k == 77) {

            cout << endl;
            cout << setw(2) << internal << 70;

        } else if(k == 88) {

            cout << endl;
            cout << setw(2) << internal << 80;

        } else if(k == 99) {

            cout << endl;
            cout << setw(2) << internal << 90;

        } else {

	    cout << setfill('0');
            cout << " " << showpos << setw(5) << internal << memory[f];
            cout << setw(0);
            f++;
        }

        k++;

    }

    cout << endl;

}
