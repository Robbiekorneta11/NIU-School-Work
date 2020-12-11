//
//  bank.cpp
//  CSCI 241 Assignment 5
//
//  Created by Robbie Korneta Z1816167
//

#include "bank.h"
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include <cstring>
#include <iomanip>

/**
 * Sorts the account array to get it prepared for
 * binary search
 *
 * @params array An account object that contains account numbers
 * @params n Size of the array
 *
 * *******************************/
void selection_sort(account array[], int n) {

    int i = 0; //Starting index
    int min_index; //Minimum index
    int j; //array elements being checked
    account temp; //Temp array to hold values for swapping
    
    while( i < n - 1) {

	min_index = i; //Set minimum index to i
	j = i + 1; //Increment j to next index

	while( j < n ) {

	    //Check the two account numbers to see which is less
	    if (strcmp(array[j].get_account_number(), array[min_index].get_account_number()) < 0)
		min_index = j;

	    j = j + 1;

	}

	//Swap the elements
	temp = array[i];
	array[i] = array[min_index];
	array[min_index] = temp;
	i = i + 1;

    }

}

/**
 * Searches for the account number to make a transaction
 *
 * @params array the account object to be searched through
 * @params length The length of the array
 * @params search_key The account number to be found
 *
 * @returns mid if the element is found
 * @returns -1 if nothing is found
 * *********************************************************/
int binary_search(account array[], int length, char* search_key) {
    
    int low = 0; //Low index
    int high = length - 1; //High index
    
    while (low <= high) {
        
       int mid = (low + high) / 2; //Calculate mid
        
            //Compare the two account numbers to see if they're equal
	    if (strcmp(search_key, array[mid].get_account_number()) == 0)
                return mid;
        
	//Check to see if the vlaue is less
        if (strcmp(search_key, array[mid].get_account_number()) < 0) {
            
            high = mid - 1; //Subtract from high
            
        } else {
            
            low = mid + 1; //Add from low
            
        }
        
    }
    
    return -1;
    
}

//Initializing the bank object
bank::bank() {
    
    strcpy(bankName, "None");
    validElements = 0;
    
}

/**
 * Read the accounts at the specified bank
 *
 * @params fileToRead The file that contains bank data
 *
 * ****************************************************/

void bank::read_accounts(string fileToRead) {
   	
    ifstream file; //The file object
    
    file.open(fileToRead); //Open the file
    
    if (!file) //If the file fails to open, throw an error
    {
        cerr << "Error - unable to open input file " << fileToRead << endl;
        exit(1);
    }
        
        // Read the next bank object in the file.
    while (file.read((char*) this, sizeof(bank))) {

	validElements++;

    }

    file.close(); //Close the file

    selection_sort(accounts, validElements); //Sort the array
    
}

/**
 * Read the transaction file and do the specified instruction
 * to deduct or add money to the users account
 *
 * @params fileToProcess The file to be read
 *
 * *******************************************************/

void bank::process_transactions(string fileToProcess) {
    
    ifstream file; //File object
    char date[6]; //Date
    char account_number[11]; //Account number
    char type[2]; //Deposit or withdrawal
    double amount; //Amount to be deducted or added
    int element; //The index of the array where the account number was found
    bool successWithdrawal; //Check for successful withdrawal
    
    file.open(fileToProcess); //Open file
    
    if (!file) //Make sure file can be opened
    {
        cerr << "Error - unable to open input file " << fileToProcess << endl;
        exit(1);
    
    }

    cout << "Transaction Report" << endl << endl;
    cout << "Date\t" << "Account\t\t" << "Type\t" << "Amount\t" << "New Balance\t" << endl << endl;

    cout << right << setprecision(2) << fixed;
    
    //Reading data into the files
    while (file >> date) {
        
        file >> account_number;
        file >> type;
        file >> amount;
        
        element = binary_search(accounts, validElements, account_number); //Find the account numbers

        if (element != -1) { //If it is found

	    //If it is a deposit, add money to the account and print out the new balance
	    if (strcmp(type, "D") == 0) {

		accounts[element].process_deposit(amount);

		cout << date << "\t" << account_number << "\t" << type << "\t" << amount << "\t" << accounts[element].get_balance() << endl;

	    }

	    //If it is a withdrawal take money out
	    if (strcmp(type, "W") == 0) {

		successWithdrawal = accounts[element].process_withdrawal(amount);
		
		//If it is not successful then print out the message
		//If it is successful then print out the new account balance
		if (successWithdrawal == false) {

		    cout << date << "\t" << account_number << "\t" << type << "\t" << amount << "\t" << "*** Insufficient funds ***" << endl;

		} else {

		    cout << date << "\t" << account_number << "\t" << type << "\t" << amount << "\t" << accounts[element].get_balance() << endl;

		}

	    }   

        } else {

	    //If an account was not found then print out this message
	    cout << date << "\t" << account_number << "\t" << type << "\t" << amount << "\t" << "*** Invalid account number ***" << endl;

	}


    }
    
    file.close(); //Close the file

    cout << endl;
    
}

//Print out the accounts
void bank::print() {
    
    cout << "Account Listing for " << bankName << endl << endl;

    for (int i = 0; i < validElements - 1; i++) {

	accounts[i].print();

    }
    
}
