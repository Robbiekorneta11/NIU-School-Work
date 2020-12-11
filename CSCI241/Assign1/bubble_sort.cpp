/**
* CSCI 241 Assignment 1
* 
* Author: Robi Korneta
* ZID: Z1816167
*
* Bubble Sort
****************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
* The function bubble_sort takes 2
* arguments: array[], and and integer n.
* The function returns nothing.
* The purpose of this function is to sort
* an array using the bubble sort method.
* It will then print the array to the
* terminal
*****************************************/

void  bubble_sort(int array[], int n) {

        int i = 1; //Represents 2nd index

        bool swapped; //Variable to check if the values were swapped

        for( i = 1; i < n; i++ ) {

		swapped = false; //Array is not swapped

                for( int j = 1; j < (n - i) + 1; j++) {

			//If array of the previous element is larger than the current
			//Elemenet, swap the twp elements

                        if(array[j - 1] > array[j]) {

                                int temp;
                                temp = array[j - 1];
                                array[j - 1] = array[j];
                                array[j] = temp;
                                swapped = true;

                        }

                }

	if (swapped == false){

		break;

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
        bubble_sort(numbers, count); //Sort the array
        cout << endl;

        return 0;

}

