//
//  simplesim.h
//  CSCI 241 Assignment 4
//
//  Created by Robbie Korneta Z1816167
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#ifndef simplesim_h
#define simplesim_h

class simplesim
{
private:

    int memory[100]; //Array of integers
    int accumulator{0}; //Accumulator register
    int instruction_counter{0}; //Instruction counter register
    int instruction_register{0}; //Instruction register
    int operation_code{0}; //Operation code register
    int operand{0}; //Operand register

public:

    simplesim() = default; //Default constructor
    bool load_program(); //Function for loading program
    void execute_program(); //Function for executing program
    void dump() const; //Function for printing program


};

#endif /* simplesim_h */
