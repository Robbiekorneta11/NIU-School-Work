/********************************
*
* TowersOfHanoi.epp
* CSCI 241 Assignment 2
*
* Created by Robi Korneta Z1816167
*
**********************************/

#include <iostream>

using namespace std;

/**
 * The function move is to move a certain amount of disks from one peg to
 * another using a temporary peg to avoid stacking a larger disk on top of
 * a smaller disk.
 *
 * @param n_disks This represents the number of disks to be moved
 * @param src_peg The peg where the disks start
 * @param dest_peg The peg where all the disks are to be moved to
 * @param temp_peg The temporary holding peg
 *
 * @return This function is void and returns no values
 *
 * @note You can customize the function in main to have the user select
 * which pegs to move the disks between
 ********************************************************************************/

void move(int n_disks, int src_peg, int dest_peg, int temp_peg) {

	//Check to see if the number of disks is above 0
	//Then the function will use recursion to format
	//the output to display each move
        if ( n_disks >= 1 ) {

		move(n_disks - 1, src_peg, temp_peg, dest_peg);
                cout << n_disks << " " << src_peg << "->" << dest_peg << endl;
		move(n_disks - 1, temp_peg, dest_peg, src_peg);

        }

}


int main(int argc, char* argv[]) {

	int num; //The number of disks specified by the user
	num = atoi(argv[1]); //Convert char to int

	//The user must input a valid number
	if ( argc >= 1  ) {

		move(num, 1, 2, 3); //Call the function move

	} else {

		cout << "You must enter the number of disks!" << endl;

	}

	return 0;

}
