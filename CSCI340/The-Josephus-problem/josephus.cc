/* 	Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include "josephus.h"

int main() {

    args in;            // Arguments being stored from stdin
    list<string> L;     // List of people in the circle 
    unsigned cnt = 0;   // Count of removals
    int j = 0;          // Position of M^th person from the position i

    init_vals(L, in);   // Call to initial args

    cout << "Initial group of people" << endl;
    cout << "-----------------------" << endl;

    print_list(L, cnt); // First print of the list

    // Loop through the list until we have 1 element left
    while (L.size() > 1) {

        // Loop until user specified k is reached
        // Erase the value at j
        for (unsigned int k = 0; k < in.K; k++) {

            int i = j;                              // Set i to j
            j = (i + (in.M - 1)) % L.size();        // Calculate j
            list<string>::iterator p = L.begin();   // Set p to beginning of list
            advance(p, j);                          // Convert j to iterator
            L.erase(p);                             // Remove p from the list
            cnt++;                                  // Increment count of removed elements

            if (L.size() == 1) { // If size of the list is 1, then we are done

                break;

            }

        }

        print_list(L, cnt); // Print the list

    }

    return 0;

}

/*
*   Initialize the values from stdin and generate the list
*
*   @param L  - The list to insert the input values in
*   @param in - The variable to hold the stdin values
*/

void init_vals(list<string> &L, args &in) {

    cout << "Number of people? ";
    cin >> in.N;
    cout << in.N << endl;
    cout << "Index for elimination? ";
    cin >> in.M;
    cout << in.M << endl;
    cout << "Index for printing? ";
    cin >> in.K;
    cout << in.K << endl;
    cout << endl;

    L.resize(in.N); // Set size of list to number of people

    generate(L.begin(), L.end(), SEQ(in.N)); // Generate list

}

/*
*   Prints the list of people remaining along with number of removals
*
*   @param L   - The list of people remaining
*   @param cnt - The count of removed people
*/

void print_list(const list<string> &L, const unsigned &cnt) {

    int N = 0; // Number of people printed on a line
    
    // Check to see if this is not the first time print_list
    // is being called
    if (cnt > 0 && cnt < 10) {

        cout << "After eliminating " << cnt << "th person" << endl;
        cout << "----------------------------" << endl;

    }

    if (cnt > 10) {

        cout << "After eliminating " << cnt << "th person" << endl;
        cout << "-----------------------------" << endl;

    }

    // Loop through the list and print out the respective person
    for (list<string>::const_iterator i = L.begin(); i != L.end(); i++) {

        cout << *i << " ";
        N++;

        if (N == 12) {

            cout << endl;
            N = 0;

        }

    }

    cout << endl << endl;

}