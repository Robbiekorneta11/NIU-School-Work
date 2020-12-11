//********************************************************
//
//  HW3Cat.cpp
//  CSCI 330 Assignment 3
//
//  Created by Robbie Korneta (z1816167)
//  Written in Xcode Version 11.3.1
//
//********************************************************

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <bitset>

using namespace std;

//********************************************************
//  The purpose of this program is to take file names from
//  the user and print them out to standard output similar
//  to the unix cat function
//
//  @param argc The number of arguments passed
//  @param argv The argument passed
//
//  @return void
//********************************************************

int main(int argc, const char * argv[]) {
    
    int fd[argc];           //Array of file descriptors
    int j = 1;              //Argv index to input into file descriptor
    char buffer[10000];     //Buffer
    ssize_t howmany;        //Number of bytes in file
    
    //**********************************************************
    //  The for loop will populate the file descriptor array and
    //  open each of the files that were specified by the user
    //**********************************************************
    
    for (int i = 0; i < argc - 1; i++) {
        
        int result = strcmp(argv[j], "-");  //The integer result of the comparison
        
        //If the result is 0, then the argument that was passed was a "-"
        if (result == 0) {} else {
        
        fd[i] = open(argv[j], O_RDONLY);    //Populate file descriptor array and open the files
        
            //If the file descriptor is -1, then there was an error opening the file
            if (fd[i] == -1) {
            
                perror("opening file");
            
            }
            
        }
        
        j++;    //Move to next argument
        
    }

    for (int k = 0; k < argc - 1; k++) {
        
        howmany = read(fd[k], &buffer, sizeof(buffer) - 1);  //Read the file into buffer and get the amount of bytes
        cout << howmany << endl;
        
        for (int i = 0; i < howmany - 1; i++) {
            
            cout << bitset<8>(buffer[i]).to_string() << " ";
            
        }
        
        cout << endl;
        //If howmany returns a 1, then there was an issue reading the file
        if (howmany == 1) {
            
            perror("Problem Reading File");
            
        }
        
        printf("%s\n", buffer); //Print the data to standard output
        cout << endl;
        
        close(fd[k]);           //Close the file
        memset(buffer, 0, sizeof(buffer) + 1);  //Clear the buffer
        
    }
    

    
    
    
    return 0;
}
