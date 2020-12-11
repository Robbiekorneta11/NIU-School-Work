/*******************************************
*
* quick_sort.cpp
* CSCI 241 Assignment 3
*
* Created by Robi Korneta Z1816167
*
*******************************************/

#include <iostream>
#include <iomanip>

using namespace std;

/**
* Split the array into two sub arrays and sort the array
*
* @params array The array to be sorted
* @params start The starting index of the array
* @params end The ending index of the array
*
* @returns pivot_index The pivot index of the array
************************************************/
int partition(int array[], int start, int end) {

    int mid = (start + end)/2; //The middle index
    int scan; //The value that is being checked
    int temp; //Temporary holding variable
    int pivot_index; //The pivot index that is being compared
    int pivot_value;

    temp = array[start]; //Putting the first value of the array into temp
    array[start] = array[mid]; //Swapping the middle value and start value
    array[mid] = temp;
    pivot_index = start; //Getting the pivot index
    pivot_value = array[start]; //Getting the pivot value
    scan = start + 1; //Getting the value to be checked

    //Looping through the array until the scan index is greater than end index
    while (scan <= end) {

        //If the value at the scan index is less than the pivot value
	//then the values will be swapped
        if (array[scan] < pivot_value) {

            pivot_index = pivot_index + 1; //Change the pivot index
            temp = array[pivot_index]; //Swap the values
            array[pivot_index] = array[scan];
            array[scan] = temp;

        }

        scan = scan + 1; //Move ot next value

    }

    temp = array[start]; //Swap the two small subarrays
    array[start] = array[pivot_index];
    array[pivot_index] = temp;

    return pivot_index; //Return the pivot index

}

/**
* Recursive function to sort an array
*
* @params array The array to be sorted
* @params start The starting index of the array
* @params end The ending index of the array
*
* @returns void
**************************************************/
void quick_sort(int array[], int start, int end) {

    int pivot_point; //The returned value of the call to partition

    //Making sure we don't go out of bounds in the array
    if (start < end) {

        pivot_point = partition(array, start, end); //Loading pivot_index
        quick_sort(array, start, pivot_point - 1); //Recusrsive call to sort
        quick_sort(array, pivot_point + 1, end); //Recursive call to sort next element

    }

}

int main(int argc, const char * argv[]) {

    int array[1000]; //Array to be populated
    int n = 0; //Starting number of values

    //Appending values into array
    while (cin >> array[n]) {

        n++;

    }

    quick_sort(array, 0, n); //Sorting the array

    int i = 0; //Starting index for printing

    //Printing values
    for (i = 0; i < n; i++) {

        cout << setw(8) << array[i];

        if ((i + 1) % 8 == 0) {

            cout << endl;

        } else {

            cout << "  ";

        }

    }

    if (i % 8 != 0) {

        cout << endl;

    }

    return 0;
}
