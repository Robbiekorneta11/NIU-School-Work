/*
    Robi Korneta
    Z1816167
    CSCI 340 - 1
    
    I certify that this is my own work and where appropriate an extension
    of the starter code provided for the assignment.
*/

#include "matrix.h"

/*
*
* Open the file into the ifstream object
*
* @param is1 -> variable to hold first file
* @param is2 -> variable to hold second file
*
*/

void open_files(ifstream &is1, ifstream &is2) {

    is1.open(FILE1); //Open file
    is2.open(FILE2);

}

/*
*
* Read the data from the file
*
* @param is -> variable that holds the file contents
* @param m  -> vector to put the file contents into a 2D array
*
*/

void read_data(ifstream &is, vector <vector <int>> &m) {

    if (is.is_open()) { //Check to make sure file is open

        int val; //Hold the value of the specific integer in the file
        int r = m.size(); //Number of rows
        int c = m[0].size(); //Number of columns

        //Loop through the file to get the values
        for (int i = 0; i < r; i++) {

            for (int j = 0; j < c; j++) {

                is >> val; //Put integer from file into val

                m[i][j] = val; //Set the 2D vector value to the value from the file

            }

        }
        
    } else {

        cout << "File is not open yet" << endl; //File is not open yet

    }

}

/*
*
* Multiply the two matrices together
*
* @param A -> The first matrix
* @param B -> The second matrix
* @param C -> The matrix that will hold the result
*
*/

void gen_data(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C) {

    int aRows = A.size(); //Amount of rows in the first matrix
    int aColumns = A[0].size(); //Amount of columns in the first matrix
    int bColumns = B[0].size(); //Amount of columns in the second matrix

    for (int i = 0; i < aRows; i++) {

        for (int j = 0; j < bColumns; j++) {

            for (int k = 0; k < aColumns; k++) {

                C[i][j] += A[i][k] * B[k][j]; //Perform matrix multiplication

            }

        }

    }

}

/*
*
* Print the contents of the vector
*
* @param m -> The matrix to be displayed
*
*/

void print_data(const vector<vector<int>> &m) {

    int r = m.size(); //Amount of rows in the matrix
    int c = m[0].size(); //Amount of columns in the matrix
    cout << r << " x " << c << endl; //Print rows x columns
    cout << "----------------------------------------------------------------------" << endl;

    for (int i = 0; i < r; i++) {

        for (int j = 0; j < c; j++) {

            cout << setw(ITEM_W) << m[i][j]; //Print the value in the matrix

        }

        cout << endl; 

    }
    
}
