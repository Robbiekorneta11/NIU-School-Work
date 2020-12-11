/* 	Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.

*/

#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

/*
*	Sieve will execute the Sieve of Eratosthenes algorithm
*
*	@param s -> The set of numbers which to find prime numbers
*	@param n -> The upper bound of the set
*/

void sieve(set<int>& s, int n) {

	//Put values into the set, based on the user input
	for (int i = 2; i <= n; i++) {

		s.insert(i);

	}

	//Sieve algorithm
	//First, starting at 2, loop and make sure m is found
	//in the set
	for (int m = 2; m * m <= n; m++) {

		if (*s.find(m) != n) { //If it is found

			for (int k = m; k <= n; k++) {

				s.erase(m * k); //Remove the non prime numbers

			}

		}

	}
  
}

int NO_ITEMS = 16; //Number of items per row
int ITEM_W = 5; //Item width

/*
*	This will print the set of prime numbers
*
*	@param s -> The set of prime numbers to print
*/

void print_primes(const set<int>& s) {

	int count = 0; //Count of elements in the row

	//Loop through set until we reach the end of the set
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {

		cout << setw(ITEM_W) << *it; //Print value
		count++; //Inrement count

		//If count of elements is equal to our specified elements
		//per row, move to a new line
		if (count == NO_ITEMS) {

			cout << endl; //New line
			count = 0; //Reset count

		}

	}

	cout << endl;

}

int main() {

	int n; //Upper bound of set
	set<int> s; //Set to hold values

	cout << "Upper limit for the set of primes: ";
	cin >> n; //Get input from user
	cout << endl;

	sieve(s, n); //Call sieve function
	print_primes(s); //Print prime numbers
	
	return 0;

}
