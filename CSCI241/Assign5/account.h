//
//  account.h
//  BankAccounts
//
//  Created by Robbie Korneta on 2/18/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#ifndef account_h
#define account_h

class account {

private:
    char accountNumber[11];
    char customerName[21];
    double accountBalance;

public:
    
    account();
    char* get_account_number();
    double get_balance();
    void process_deposit(double);
    bool process_withdrawal(double);
    void print();
    
};

#endif /* account_h */
