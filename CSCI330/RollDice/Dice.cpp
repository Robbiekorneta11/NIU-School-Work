//
//  dice.cpp
//  rollDice
//
//  Created by Robbie Korneta on 3/18/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#include "Dice.h"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void experiment(int array[], int n, int r) { // n is the # of dice, r is the # of rolls
    
    int max = 6 * n;
    int sum = 0;
    
    for (int i = 0; i < max; i++) {
        
        array[i] = 0;
        
    }
    
    for (int p = 0; p < r; p++) {

        for (int q = 0; q < n; q++) {

            sum = sum + RollDie();
            
        }
        
        array[p] = sum;
        
        sum = 0;
        
    }
    
}

void Output(int array[], int r, string outputFile) {

    int a = 1;
    ofstream file;
    file.open(outputFile);
    cout << endl << "Results:" << endl;
    
    for (int i = 0; i < r; i++) {
        
        file << a << ", " << array[i] << endl;
        cout << a << ", " << array[i] << endl;
        a++;
        
    }
    
    file.close();
    
}

int RollDie() {
    
    static random_device rd;
    static default_random_engine engine(rd());
    static uniform_int_distribution<int> uniform_dist(1, 6);

    return uniform_dist(engine);
}


