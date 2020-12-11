
//***********************************
//
// matrix.h
// CSCI Assignment 6 
// 
// Created by Robi Korneta Z1816167
//
// **********************************

#ifndef matrix_h
#define matrix_h

#include <iostream>

class matrix {

	//This function will be called to print out the matrix
	friend std::ostream& operator<<(std::ostream&, const matrix&);
	//This will be called to multiply an integer to a matrix
	friend matrix operator*(int, const matrix&);

private:
	
	int matrixArray[2][2]; //Array to hold values

public:

        matrix(); //Default constructor
	matrix(int[2][2]); //Constructor to create new array of type matrix
	int determinant() const; //Calculate the determinant
	matrix operator+(const matrix&) const; //Add matrices
	matrix operator*(int) const; //Multiply matrix by integer
	matrix operator*(const matrix&) const; //Multiply matrix by matrix
	bool operator==(const matrix&) const; //Compare matricies to see if they are equal
	bool operator!=(const matrix&) const; //Compare matricies to see if they are not equal

};

#endif

