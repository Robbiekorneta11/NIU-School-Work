/**
* CSCI 241 Assignment 1
* 
* Author: Robi Korneta
* ZID: Z1816167
*
* Insertion Sort
****************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

/**
* The function inserition_sort takes 2
* arguments: array[], and and integer n.
* The function returns nothing.
* The purpose of this function is to sort
* an array using the insertion sort method.
* It will then print the array to the
* terminal
*****************************************/

void insertion_sort(int array[], int n) {

	int num; //Represents the current index  value
	int j; //Represents the element one before the current index

        for( int i = 1; i < n; i++ ) {

		num = array[i]; //Storing the current index value into num
		j = i - 1; //Storing the index before the current index into j

                while( j >= 0 && array[j] > num ) {

                        array[j + 1] = array[j]; //Swapping the two element values
			j = j - 1; //Going back to previous index

                }

		array[j + 1] = num; //Storing num in the next array index of j

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
        insertion_sort(numbers, count); //Sort the array
        cout << endl;

        return 0;


}

