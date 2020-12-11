//
//  functions.cpp
//  dog
//
//  Created by Robbie Korneta on 2/21/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//


#include "functions.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <bitset>
#include <stdio.h>
#include <climits>

using namespace std;

/**
* Convert the given file into a binary number
*
*
* @param file The file to be read
* @param size The size of the file
*
* @return A string containing the binary value
*
********************************************************************************/

string functions::toBinary(char* file, int size) {

    char buffer[size]; //Creating the buffer
    int fd = open(file, O_RDONLY); //Opening the file
    ssize_t howmany; //Represents the amount of bytes
    string result; //Represents the result

    howmany = read(fd, &buffer, sizeof(buffer)); //Get the number of bytes

    //Check for error
    if (howmany == -1) {

        perror("reading file");
        exit(1);

    } else {

        //Get the binary equivalent of the file
        for( int i = 0; i < howmany - 1; i++ ) {

            result +=  bitset<8>(buffer[i]).to_string();

        }
        
    }

    close(fd); //Close the file

    return result;

}

/**
* Convert the given file into a hexadecimal value
*
*
* @param file The file to be read
* @param size The size of the file
*
********************************************************************************/

void functions::toHex(char* file, int size) {

    
    char buffer[size]; //Create a buffer
    int fd = open(file, O_RDONLY); //Open the file
    ssize_t howmany; //Number of bytes

    howmany = read(fd, &buffer, sizeof(buffer)); //Get number of bytes
 
    if (howmany == -1) {

        perror("reading file");
        exit(1);

    } else {

        //Convert to the hexadecimal value
        for( int i = 0; i < howmany - 1; i++ ) {

            cout << hex << (int)buffer[i];

        }

    }

    cout << endl;
    close(fd); //Close the file

}

/**
* Perform a caesar cipher shift on the given file
*
*
* @param file The file to be read
* @param size The size of the file
 * @param x The amount to be shifted by
*
* @return A string containing the result of the caesar cipher shift
*
********************************************************************************/

string functions::caesarCipher(char* file, int size, int x) {

    char buffer[size]; //Create a buffer
    int fd = open(file, O_RDONLY); //Open the file
    ssize_t howmany; //Number of bytes
    string result = ""; //Result of the shift

    howmany = read(fd, &buffer, sizeof(buffer)); //Get number of bytes

    if (howmany == -1) {

        perror("reading file");
        exit(1);

    } else {

        //Shift the elements of the array
        for (int i = 0; i < howmany - 1; i++) {

                if (isupper(buffer[i]))
                    result += char(int(buffer[i] + x - 65) % 26 + 65);

                else
                    result += char(int(buffer[i] + x - 97) % 26 + 97);
        }

    }

    close(fd); //Close the file

    return result;

}

/**
* Perform a rotation on the given file
*
*
* @param x The file to be read
* @param size The size of the file
 * @param n The amount to be shifted by
*
* @return An int containing the result of the caesar cipher shift
*
********************************************************************************/

int functions::rotation(char* x, int size, int n) {

    char buffer[size]; //Create a buffer
    int fd = open(x, O_RDONLY); //Open the file
    ssize_t howmany; //Amount of bytes
    
    howmany = read(fd, &buffer, sizeof(buffer)); //Get amount of bytes

    if (howmany == -1) {

        perror("reading file");
        exit(1);

    }
    
    //Return the resulting value of the shift
    return (n << howmany)|((unsigned) n >> (-howmany & (sizeof(int) * CHAR_BIT - 1)));

}

