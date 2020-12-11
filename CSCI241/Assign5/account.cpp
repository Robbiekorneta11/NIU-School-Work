//
//  account.cpp
//  CSCI 241 Assignment 5
//
//  Created by Robi Korneta Z1816167
//

#include "account.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

//Creating a default account constructor
account::account() {
    
    strcpy(accountNumber, "None");
    strcpy(customerName, "None");
    accountBalance = 0.00;
    
}
/**
 * Returns the account number
 * 
 * @returns the account number 
 *
 * *********************************************/

char* account::get_account_number() {
    
    return accountNumber;
    
}

/**
 * Returns the balance of an account
 * 
 * @returns the balance 
 *
 * ************************************************/


double account::get_balance() {
    
    return accountBalance;
    
}
/**
 * Adds an amount to the account balance
 * 
 * @params depositAmount the amount to be desposited 
 *
 * **************************************************/

void account::process_deposit(double depositAmount) {
    
    accountBalance = accountBalance + depositAmount;
    
}
/**
 * Subtracts an amount from the account balance
 * 
 * @returns false if the withdrawal amount is greater than
 * the account balance
 * @returns true if the account balance is larger than the
 * withdrawal 
 *
 * *****************/

bool account::process_withdrawal(double withdrawalAmount) {
    
    //Check to see if withdrawal amount is more than account balance
    if (withdrawalAmount > accountBalance) {
        
        return false; //If it is return false
        
    } else {
    
	//Subtract the amount from the account balance
        accountBalance = accountBalance - withdrawalAmount;
        
        return true;
        
    }
    
}
/**
 * Prints the fields
 * *****************/

void account::print() {
    
    cout << "Account Number: " << accountNumber << endl;
    cout << "Name: " << customerName << endl;
    cout << "Balance: $" << accountBalance << endl << endl;
    
}
