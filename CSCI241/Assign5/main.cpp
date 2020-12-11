//
//  main.cpp
//  BankAccounts
//
//  Created by Robbie Korneta on 2/18/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#include <iostream>
#include "bank.h"
#include "account.h"

int main(int argc, const char * argv[]) {
    
    bank theBank = bank(); //Creating a bank object
    cout << endl; 
    theBank.read_accounts("accounts"); //Calling read accounts
    theBank.print();
    theBank.process_transactions("transactions.txt"); //Processing the transactions
    theBank.print();    
    
    return 0;
}

