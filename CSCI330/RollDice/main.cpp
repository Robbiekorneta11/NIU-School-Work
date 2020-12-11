//
//  main.cpp
//  rollDice
//
//  Created by Robbie Korneta on 3/18/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Dice.h"
#include <random>

using namespace std;

int main() {
    
    int n, r;

    cout << "How many dice will you roll?" << endl;
    cin >> n;
    cout << "How many times will you roll them?" << endl;
    cin >> r;
    
    int* array1 = new int[n];

    experiment(array1, n, r);
    Output(array1, r, "output.txt");
    
}
