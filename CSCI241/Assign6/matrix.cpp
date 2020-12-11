
//***********************************************
//
// matrix.cpp
// CSCI 241 Assignment 6
//
// Created by Robi Korneta Z1816167
//
//***********************************************

#include "matrix.h"
#include <iostream>

//Default constructor to set up identity matrix

matrix::matrix() {

	matrixArray[0][0] = 1;
	matrixArray[0][1] = 0;
	matrixArray[1][0] = 0;
	matrixArray[1][1] = 1;

}

//Constructor called to set up an array and convert it to a matrix object

matrix::matrix(int array[2][2]) {

	matrixArray[0][0] = array[0][0];
	matrixArray[0][1] = array[0][1];
	matrixArray[1][0] = array[1][0];
	matrixArray[1][1] = array[1][1];

}

/**
 * Use the << operator to print out the matrix values
 * 
 * @param out The output to standard output
 * @param m   The matrix to be displayed
 *
 * @return The output of the matrix
 * **********************************************************/

std::ostream& operator<<(std::ostream& out, const matrix& m) {

	return out << "[["  << m.matrixArray[0][0] << ", " << m.matrixArray[0][1] << "], [" << m.matrixArray[1][0] << ", " << m.matrixArray[1][1] << "]]";

}

/**
 * Use the * operator to calculate the result of multiplying
 * an integer to a matrix
 *
 * @param left An integer to multiply to the matrix
 * @param m A 2D array of integers in a matrix object
 *
 * @return The result of the multiplication
 *
 * ********************************************************/

matrix operator*(int left, const matrix& m) {

	matrix result; //Matrix to store the result
	
	int a = m.matrixArray[0][0]; //Store the value at (0, 0)
	int b = m.matrixArray[0][1]; //Store the value at (0, 1)
	int c = m.matrixArray[1][0]; //Store the value at (1, 0)
	int d = m.matrixArray[1][1]; //Store the value at (1, 1)

	//Multiply the values by left and store them in the resulting matrix
	result.matrixArray[0][0] = a * left;
	result.matrixArray[0][1] = b * left;
	result.matrixArray[1][0] = c * left;
	result.matrixArray[1][1] = d * left;
	

	return result;	



}

/**
 * Find the determinant of an array
 *
 * @return An integer representing the result
 *****************************************************/

int matrix::determinant() const {

	//Store integer values
	int a = matrixArray[0][0];
	int b = matrixArray[0][1];
	int c = matrixArray[1][0];
	int d = matrixArray[1][1];
	int result = (a * d) - (b * c); //Calculate the result

	return result;

}

/**
 * Use the + operator to add two matrices together
 *
 * @param m A matrix object to add to the default matrix
 *
 * @return The resulting matrix
 * ***********************************************/

matrix matrix::operator+(const matrix& m) const {

	matrix result; //Resulting matrix after addition

	//Add the two arrays together. The first being the default array from main
	//and the second being the matrix array that was passed to the function
	result.matrixArray[0][0] = this->matrixArray[0][0] + m.matrixArray[0][0];
	result.matrixArray[0][1] = this->matrixArray[0][1] + m.matrixArray[0][1];
	result.matrixArray[1][0] = this->matrixArray[1][0] + m.matrixArray[1][0];
	result.matrixArray[1][1] = this->matrixArray[1][1] + m.matrixArray[1][1];

	return result;

}

/**
 * Use the * operator to perform scalar multiplication
 *
 * @param right The integer to multiply to the array
 *
 * @return The resulting matrix
 * *******************************************************/

matrix matrix::operator*(int right) const {

	matrix result; //Matrix to hold the result

	//Multiply the matrix array from main by the value of right
	result.matrixArray[0][0] = this->matrixArray[0][0] * right;
	result.matrixArray[0][1] = this->matrixArray[0][1] * right;
	result.matrixArray[1][0] = this->matrixArray[1][0] * right;
	result.matrixArray[1][1] = this->matrixArray[1][1] * right;

	return result;

}

/**
 * Use the * operator to multiply two matricies
 * together
 *
 * @param m A matrix object to multiply
 *
 * @return The resulting matrix
 * ***************************************************/

matrix matrix::operator*(const matrix& m) const {

	matrix result; //Resulting matrix

	//Multiply the matrix from main by the matrix passed into the
	//variable m
	result.matrixArray[0][0] = this->matrixArray[0][0] * m.matrixArray[0][0] + this->matrixArray[0][1] * m.matrixArray[1][0];
	result.matrixArray[0][1] = this->matrixArray[0][0] * m.matrixArray[0][1] + this->matrixArray[0][1] * m.matrixArray[1][1];
	result.matrixArray[1][0] = this->matrixArray[1][0] * m.matrixArray[0][0] + this->matrixArray[1][1] * m.matrixArray[1][0];
	result.matrixArray[1][1] = this->matrixArray[1][0] * m.matrixArray[0][1] + this->matrixArray[1][1] * m.matrixArray[1][1];

	return result;

}

/**
 * Compare the matrix from main to the matrix passed
 * into the function to see if they are equal
 *
 * @param m A matrix object to compare
 *
 * @return true if they are equal
 * @return false if they are not equal
 * ***************************************************/

bool matrix::operator==(const matrix& m) const {

	//Check to see if each element in the matricies are equal to the others
	if((m.matrixArray[0][0] == this->matrixArray[0][0]) && (m.matrixArray[0][1] == this->matrixArray[0][1]) && (m.matrixArray[1][0] == this->matrixArray[1][0]) && (m.matrixArray[1][1] == this->matrixArray[1][1]))
		return true;
	else
		return false;

}

/**
 * Use the != operator to compare the matrix from
 * main to the matrix passed to the function
 *
 * @param m The matrix to compare
 *
 * @return true if they are not equal
 * @return false if they are equal
 * **************************************************/

bool matrix::operator!=(const matrix& m) const {

	//Check to see if they are equal
	if((m.matrixArray[0][0] == this->matrixArray[0][0]) && (m.matrixArray[0][1] == this->matrixArray[0][1]) && (m.matrixArray[1][0] == this->matrixArray[1][0]) && (m.matrixArray[1][1] == this->matrixArray[1][1]))
                return false;
        else
                return true;
}
