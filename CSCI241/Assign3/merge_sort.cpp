/*******************
*
* merge_sort.cpp
* CSCI Assignment 3
*
* Created by Robi Korneta z1816167
*
*******************/

#include <iostream>
#include <iomanip>

using namespace std;

/**
* Takes an array and merges it to sort the array
*
* @param array An array to be sorted
* @param start The starting point of the array
* @param mid The middle point of the array
* @param end The end point of the array
*
* @return void
*
* @note Utilizes the merge sort algorithm
*************************************************/
void merge(int array[], int start, int mid, int end) {

    int temp[end - start + 1]; //Temp array to hold values
    int i = start; //Starting index for left side
    int j = mid + 1; //Starting index for right side
    int k = 0; //Count of elements

    //Sorting left and right side of array
    while (i <= mid && j <= end) {

        //If the array value at the left side index is
        //less than the array value on the right side
        //Then add the left side value to the temp array
        //Else put the right side value into the temp array
        if (array[i] < array[j]) {

            temp[k] = array[i];
            i = i + 1;

        } else {

            temp[k] = array[j];
            j = j + 1;

        }

        k = k + 1; //Increase the count index

    }

    //Sort through the remaining values in the left side of the array
    while (i <= mid) {

        temp[k] = array[i]; //Add the values to the temp array
        i = i + 1;
        k = k + 1;

    }

    //Go through the remaining values in the right side of the array
    while (j <= end) {

        temp[k] = array[j]; //Insert the values into the temp array
        j = j + 1;
        k = k + 1;

    }

    //Copy the temp array to the array
    for (i = start; i <= end; i++) {

	array[i] = temp[i - start];

    }

}

/**
* Takes an array and sorts it using the merge sort algorithm
*
* @params array Array to be sorted
* @params start Starting index in the array
* @params end Ending index in the array
*
* @returns void
************************************************/
void merge_sort(int array[], int start, int end) {

    int mid; //Middle index in the array

    //Checking to make sure we aren't out of bounds on the index
    if (start < end) {

        mid = (start + end) / 2; //Calculating mid point of array

        merge_sort(array, start, mid); //Recursive call to sort left side
        merge_sort(array, mid + 1, end); //Call to sort right side

        merge(array, start, mid, end); //Merge the two arrays

    }

}

int main() {

    int array[1000]; //Array to hold values
    int n = 0; //First element of array

    //Getting values from input redirection and appending them to array
    while (cin >> array[n]) {

        n++;

    }

    merge_sort(array, 0, n); //Sorting the array

    int i = 0; //First element in array

    //Printing the array
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
