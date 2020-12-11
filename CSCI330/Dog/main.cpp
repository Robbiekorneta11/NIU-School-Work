//*************************************
//
// main.cpp
// CSCI 241 Assignment 4
//
// Created by Robi Korneta Z1816167
//
//*************************************

#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "functions.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    functions theFunction = functions(); //Functions object to call the methods
    int opt; //Optional parameters count
    int fd1; //File Descriptor
    int shiftAmount = 0; //The amount we want to shift
    int rotateAmount = 0; //The amount we want to rotate
    int rotation; //The value returned by the call to rotation
    int size = 2048; //Size of the buffer
    int numOfBytes = 2048; //Amount of bytes to be read
    int i = 1; //Index of argv
    ssize_t howmanyDefault; //how many bytes are in the buffer
    ssize_t howmany; //How many bytes are in the buffer
    string bin; //The return binary string
    string caesar; //The returned caesar cipher string
    bool sflagused = false; //Check for size flage
    bool nflagused = false; //Check for nflag
    bool cflagused = false; //Check for caesar flag
    bool rflagused = false; //Check for rotation flag
    bool xflagused = false; //Check for hex flag
    bool bflagused = false; //Check for binary flag
    char* bufferDefault[2048]; //Default buffer
    char optstring[] = "sncrxb"; //Possible values for optional parameters
    // Each step of this loop handles one optional parameter
    while((opt = getopt(argc, argv, optstring)) != -1) { // end when -1 returned
    
        switch(opt) {
            case 's': //S will change size of buffer
               size = atoi(argv[i + 1]); //Converting to int
               i = i + 2; //Incrementing index by 2
               sflagused = true; //Setting s flag to true
               break;

            case 'n': //n will change the number of bytes read
               numOfBytes = atoi(argv[i + 1]); //Converting to integer
               i = i + 2; //Incrementing index by 2
               nflagused = true; //Setting n flag to true
               break;

                case 'c': //c will apply a caesar cipher
                   shiftAmount = atoi(argv[i + 1]); //Converting to int
                   i = i + 2; //Incrementing index by 2
                   cflagused = true; //Setting c flag to true
                   break;

                case 'r': //r will apply a rotation
                   rotateAmount = atoi(argv[i + 1]); //Converting to int
                   rflagused = true; //Setting r flag to true
                   i = i + 2; //Incrementing index by 2
                   break;

                case 'x': //x will output that data in hex format
                   i = i + 1; //increment index by 1
                   xflagused = true; //Set x flag to true
                   break;

                case 'b': //b will output the data in binary format
                   i = i + 1; //Increment index by 1
                   bflagused = true; //Set b flag to true
                   break;

                default:
                   break;
                 
                     }
                 }

        //Check to see if any of the flags were set
        //If none of them were, then just open and print the file to standard output
        //If only the n flag was set then we will print out the file with the specified number of bytes
        //If both the caesar flag and rotation flag were set, throw an error message
        //If both the binary flag and hexadecimal flag were set, then throw an error message
        //If none of this is the case, make the appropriate calls to the specified functions based on the flag that was called
        if (sflagused == false && nflagused == false && cflagused == false && rflagused == false && xflagused == false && bflagused == false) {

                fd1 = open(argv[1], O_RDONLY); //Open file
                howmanyDefault = read(fd1, bufferDefault, numOfBytes - 1); //Read amount of bytes

                //Account for error
                if (howmanyDefault == -1) {

                    perror("reading file");
                    exit(1);

                }

                write(STDOUT_FILENO, bufferDefault, 2047); //Write to standard output

                } else if (sflagused == false && nflagused == true && cflagused == false && rflagused == false && xflagused == false && bflagused == false) {
                
                     fd1 = open(argv[1], O_RDONLY); //Open file
                     howmanyDefault = read(fd1, bufferDefault, numOfBytes - 1); //Read amount of bytes

                     if (howmanyDefault == -1) {

                         perror("reading file");
                         exit(1);

                     }

                     write(STDOUT_FILENO, bufferDefault, numOfBytes - 1); //Write to stdout
                
                 } else if (rflagused == true && cflagused == true) {
                         
                     cerr << "You cannot apply a rotation and caesar cipher to the same file" << endl;
                     exit(1);
                         
                 } else if (bflagused == true && xflagused == true) {
                       
                       cerr << "Cannot convert to both hexadecimal and binary" << endl;
                       exit(1);
                       
                 } else {

                     char* buffer[size]; //Declare buffer
                     int fd = open(argv[argc - 1], O_RDONLY); //Open file
                 
                     howmany = read(fd, buffer, numOfBytes); //Get amount of bytes
                         
                     if (howmany == -1) {

                             perror("reading file");
                             exit(1);

                    }
                     
                    if (cflagused == true) {
                     
                        caesar = theFunction.caesarCipher(argv[argc - 1], numOfBytes, shiftAmount); //Calling the caesar shift
                        char cstr[caesar.size() + 1]; //Creating a char array
                        strcpy(cstr, caesar.c_str()); //Copying the data into the char value

                        write(STDOUT_FILENO, cstr, sizeof(cstr) - 1); //Writing to stdout
                        cout << endl;

                    }

                    if (rflagused == true) {
                     
                        rotation = theFunction.rotation(argv[argc - 1], numOfBytes, rotateAmount); //Calling rotation function
                             
                        cout << rotation << endl;
                                 
                    }

                    if (xflagused == true) {
                                 
                        theFunction.toHex(argv[argc - 1], numOfBytes); //Converting to hex
                                 
                    }

                    if (bflagused == true) {
                                 
                        bin = theFunction.toBinary(argv[argc - 1], numOfBytes); //Calling binary function
                        char binstr[bin.size() + 1]; //Declaring char value
                        strcpy(binstr, bin.c_str()); //Copying data into char value

                        write(STDOUT_FILENO, binstr, sizeof(binstr) - 1); //Writing to stdout
                        cout << endl;
                                 
                    }
                                 
                }

        return 0;

}

                     
