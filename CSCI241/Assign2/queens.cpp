/*********************************
*
* queens.cpp
*
* CSCI Assignment 2
*
* Created by Robi Korneta Z1816167
*
**********************************/

#include <iostream>

using namespace std;

/**
 * This function is used to print the chessboard when it has been
 * populated with queens
 *
 * @param board[][] is a 2D array and represents the chessboard to be printed
 *
 * @return Nothing
 *
 ********************************************************************************/

void printBoard(int board[8][8]) {

	for( int i = 0; i < 8; i++ ) {

		for( int j = 0; j < 8; j++ )

			cout << board[i][j] << " ";

		 cout << endl;

	}
}

/**
 * The function isValid is used to check if the queen that is currently being
 * placed is in a valid spot on the board
 *
 * @param board[8][8] represents the chessboard 2D array
 * @param row represents the row of the chessboard
 * @param col represents the column of the chessboard
 *
 * @return false if there is a queen to the left or diagonal of the queen
 * that is trying to be placed. It will return true if none of these are the case
 *
 ********************************************************************************/

bool isValid(int board[8][8], int row, int col) {

	for( int i = 0; i < col; i++ ) //check if there is a queen to the left

		if( board[row][i] )

			return false;

	for( int i = row, j = col; i >= 0 && j >= 0; i--, j-- )

		if(board[i][j]) //check if there is a queen diagonally to the left

			return false;

	for( int i = row, j = col; j >= 0 && i < 8; i++, j--)

		if( board[i][j] ) //check if there is queen lower diagonally to the left

			return false;

	return true;

}

/**
 * This function will place the queens in the chessboard and validate it
 *
 * @param board[8][8] represents the chessboard
 * @param col represents the current column
 *
 * @return true if all 8 queens are placed or if the queen spots are valid
 * false if no possible order is found
 ********************************************************************************/

bool place_queens(int board[8][8], int col) {

	if (col >= 8) //When all 8 queens are placed

		return true;

	for( int i = 0; i < 8; i++) { //In each row check to make sure queen placement is valid

		if ( isValid( board, i, col ) ) {

			board[i][col] = 1; //If it is valid then place the queen at i, col

			if ( place_queens(board, col + 1)) //Recursive call for the next columns

				return true;

			board[i][col] = 0; //When no place is vacant remove that queen

		}
	}

	return false; //When no possible order is found

}

int main() {

	int board[8][8]; //Chessboard

	for( int i = 0; i < 8; i++ )

	for( int j = 0; j < 8; j++ )

	board[i][j] = 0; //Populating the chessboard with all 0s

	place_queens(board, 0); //Placing the queens into the chessboard

	printBoard(board); //Print the chessboard

	return 0;

}
