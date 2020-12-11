//
//  bank.h
//  BankAccounts
//
//  Created by Robbie Korneta on 2/18/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#ifndef bank_h
#define bank_h

#include "account.h"
#include <string>

using namespace std;

class bank {

private:
    char bankName[31];
    account accounts[20];
    int validElements;

public:
    
    bank();
    void read_accounts(string accountsFile);
    void process_transactions(string transactionFile);
    void print();
    
};

#endif /* bank_h */
