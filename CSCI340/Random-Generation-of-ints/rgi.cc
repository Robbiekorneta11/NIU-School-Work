/*
    Robi Korneta
    Z1816167
    CSCI 340 - 1
    
    I certify that this is my own work and where appropriate an extension
    of the starter code provided for the assignment.
*/

#include "rgi.h"

int HIGH = 10000; //The highest value for random integers
int LOW = 1; //Low value of random integers
int SEED = 1;
int VEC_SIZE = 200;

/*
 * Generate random numbers and store them in a vector
 *
 * @param v - The vector to put the random integers
 * @param vec_size - The amount of integers to put in the vector
 * @param seed - The seed for srand
 *
 */

void genRndNums(vector<int>& v)
{

    srand(SEED); //Initialize random number generator with seed
    int randomInteger = 0; //Variable to hold the random integer
    
    //Loop vec_size times and generate random integers
    for (int i = 0; i < VEC_SIZE; i++) {
        
        randomInteger = (rand() % HIGH) + LOW; //Generate random integer with bounds [1, 10000]
        v.push_back(randomInteger); //Push random integer into the vector
        
    }
    
}

/*
 * Print the contents of the vector
 *
 * @param v - the vector to print the values from
 * @param vec_size - the size of the vector
 *
 */

void printVec(const vector<int>& v)
{
    
    int NO_ITEMS = 12; //Number of integers to put on each line
    int ITEM_W = 5; //Spacing between each integer for output
    int count = 0; //Count to tack when to move to next line
    
    //Loop through the vector and print the value
    for (int i = 0; i < VEC_SIZE; i++) {
        
        cout << setw(ITEM_W) << v[i] << " "; //Print value
        
        count++; //Increment count
        
        //Check to see if we need to move to a new line
        if (count == NO_ITEMS) {
            
            cout << endl; //Print new line
            count = 0; //Reset count
            
        }
        
    }
    
    cout << endl;
    
}

int main()
{
    vector<int> v; //Vector to hold random integers
    genRndNums(v); //Generate random numbers
    sort(v.begin(), v.end()); //Sort the vector in ascending order
    printVec(v); //Print the vector

    return 1; //End program
}


