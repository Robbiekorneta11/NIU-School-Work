//
//  main.cpp
//  Assignment5
//
//  Created by Robbie Korneta on 3/26/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>


using namespace std;

/* I could not get this to work in the loop/repeat itself */

int main(int argc, const char * argv[]) {
    
    char buf[1024]; //Buffer to hold user input from first line
    char buf1[1024]; //Buffer to hold user input from second line
    char *command1[1024]; //First line commands
    char *command2[1024]; //Second line commands
    bool done = false; //Check to see if we are done
    
    while (done != true) {
        
        cout << "command1? ";
        fgets(buf, 1024, stdin); //Get the first line text
        
        //Check to see if quit was the first command
        if (buf[0] == 'q' && buf[1] == 'u' && buf[2] == 'i' && buf[3] == 't')
            exit(1);
       
        command1[0] = strtok(buf, "\n"); //Tokenize the first line commands
        command1[1] = strtok(NULL, "\n");
        
        cout << "command2? ";
        fgets(buf1, 1024, stdin); //Get second line commands
        
        //Check to see it command was quit
        if (buf1[0] == 'q' && buf1[1] == 'u' && buf1[2] == 'i' && buf1[3] == 't')
            exit(1);
        
        command2[0] = strtok(buf1, "\n"); //Tokenize the second line commands
        command2[1] = strtok(NULL, "\n");
        
        int pipefd[2]; //Pipe file descriptor
        int rs; //Status
        
        rs = pipe(pipefd); //Create pipe
        
        if (rs < 0) { //Check for failure
            
            perror("pipe");
            exit(EXIT_FAILURE);
            
        }
        
        rs = fork(); //Create fork
        
        if (rs < 0) { //Check for failure
            
            perror("fork");
            exit(EXIT_FAILURE);
            
        }
        
        if (rs == 0) { //On success
            
            close(pipefd[0]); //Close read end of pipe
            close(1); //Close stdout
            dup(pipefd[1]); //Duplicate write end into standard output
            close(pipefd[1]); //Close write end of pipe
            
            rs = execvp(command1[0], command1); //Execute command
            
            if (rs < 0) { //Check for error
                
                perror("execvp");
                exit(EXIT_FAILURE);
                
            }
            
        } else {
            
            close(pipefd[1]); //Close write end of pipe
            close(0); //Close stdin
            dup(pipefd[0]); //Duplicate read end into standard input
            close(pipefd[0]); //Close read end of pipe
            
            rs = fork(); //Create a new fork
            
            if (rs < 0) { //Check for error
                
                perror("fork");
                exit(EXIT_FAILURE);
                
            }
            
            if (rs == 0) { //On success
                
                rs = execvp(command2[0], command2); //Execute second command
                
                if (rs < 0) { //Failure
                    
                    perror("execvp");
                    exit(EXIT_FAILURE);
                    
                }
                
            } else {
                
                wait(&rs); //Wait for parent process to terminate
                done = true; //Done
                
            }
            
        }
        
    }
    
    return 0;
}
