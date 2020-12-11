/**
* CSCI 241 Assignment 1
* 
* Author: Robi Korneta
* ZID: Z1816167
*
* Selection Sort
****************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
* The function selection_sort takes 2
* arguments: array[], and and integer n.
* The function returns nothing.
* The purpose of this function is to sort
* an array using the selection sort method.
* It will then print the array to the
* terminal
*****************************************/

void  selection_sort(int array[], int n) {

	int min; //the minimum element

        for( int i = 0; i < n-1; i++ ) {

		min = i; //Setting minimum element to i

                for( int j = i + 1; j < n; j++) {

			//If the current element is less than
			//the minimum element, then swap them

                        if(array[j] < array[min]) {

                                int temp;
                                temp = array[min];
                                array[min] = array[j];
                                array[j] = temp;

                        }

                }

        }

	int count = 0; //Represents the number of values on a line

        for(int j = 0; j < n; j++) {


                cout << setw(6) << array[j]; //Formatting the output
                count = count + 1; //Going to next value

                if (count == 8){

                        cout << endl; //When we reach 8 values on a line, go to a new line
                        count = 0; //Count is reset

                }

        }

}

int main() {

        string file; //The file the user must enter
        cout << "Please Enter File Name: ";
        cin >> file; //Enter file
        ifstream readFile; //Read File
        readFile.open(file); //Open specified file
        int output; //Output Numbers
        int numbers[1000]; //Array to store them
        int count = 0; //Current index of array

        while (readFile >> output) {

                numbers[count] = output; //Putting values into array
                count = count + 1; //Moving to next element
        }

        readFile.close(); //Close the file
        selection_sort(numbers, count); //Sort the array
        cout << endl;

        return 0;


}


