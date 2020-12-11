/* 	
    Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "binaryTree.h"

using namespace std;

void InitiateGame();
void ContinueGame(BinaryTree*);

int main() {

    string yesOrNo;

    cout << "\nShall we play a game? ";
    cin >> yesOrNo;

    if (yesOrNo == "y") {

        InitiateGame();

    } else if (yesOrNo == "n") {

        cout << "Bye!\n";

    } else {

        cout << "Invalid Response!\n";

    }

    return 0;

}

/**
 * Begins the guessing game
 * ************************/
void InitiateGame() {

    string computerAnswer;  // Computer answer to the question
    string userResponse;    // Users responses to the promts
    string userAnimal;      // User entered animal
    string userQuestion;    // User entered question
    string correct;         // Whether or not the users animal is the
                            // correct answer to the question

    computerAnswer = "elephant"; // Default answer

    // Guess the animal they were thinking
    cout << "Were you thinking of a " << computerAnswer << "? ";
    cin.ignore();
    getline(cin, userResponse);

    // If yes, prompt to play another game
    if (userResponse == "y") {

        cout << "Great!\n\n";
        cout << "Shall we play a game? ";
        userResponse = "";
        getline(cin, userResponse);

        if (userResponse == "y") {

            InitiateGame(); // Reinitiate the game

        } else if (userResponse == "n") {

            cout << "Bye!\n\n";

        } else {

            cout << "Invalid Response!\n\n";

        }

    } else { // Guess was wrong

        // Prompt user to enter info to build program AI
        cout << "Doh! What was the animal? ";
        getline(cin, userAnimal);
        cout << "What question separates " << userAnimal << " from " << computerAnswer << "? ";
        getline(cin, userQuestion);
        cout << "What is the correct answer for this animal? ";
        getline(cin, correct);

        // If the new user supplied question is correct for their animal
        // they were thinking of, the no node is the programs guess and
        // the yes node is the users animal
        if (correct == "y") {

            BinaryTree *bt = new BinaryTree(userQuestion, userAnimal, computerAnswer);
            bt->root->no = new Node(computerAnswer);
            bt->root->yes = new Node(userAnimal);
            ContinueGame(bt);

        } else { // Opposite of above

            BinaryTree *bt = new BinaryTree(userQuestion, userAnimal, computerAnswer);
            bt->root->yes = new Node(computerAnswer);
            bt->root->no = new Node(userAnimal);
            ContinueGame(bt);

        }

    }

}

/**
 * Loops the prompts to ask questions
 * 
 * @param bt -> The binary tree to insert nodes
 * *********************************************/
void ContinueGame(BinaryTree *bt) {

    string userResponse = "";

    cout << "\nShall we play a game? ";
    getline(cin, userResponse);

    if (userResponse == "y") {

        bt->BeginQuestions();
        ContinueGame(bt);

    } else {

        cout << "Bye!\n\n";

    }

}