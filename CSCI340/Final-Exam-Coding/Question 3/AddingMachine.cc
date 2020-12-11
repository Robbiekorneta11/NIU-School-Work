/* 	
  Robi Korneta
	Z1816167
	CSCI 340 - 1
	
    I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {

    string inputValue;  // Value that the user inputs
    char operation;     // Operation to execute
    int value;          // Value of the input
    int totalValue = 0; // Total sum of the values
    stack<int> values;  // Stack to hold history of the total value

    value = 0;                      // Set value to 0
    values.push(value);             // Push value onto stack
    cout << "=> " << value << endl; // Print original value

    // Loop until done
    while (1) {

        cin >> inputValue; // Get input value

        // Check to see if user sepcified undo or clear
        if (inputValue == "U") {

            values.pop();                           // Revert to the previous value
            totalValue = values.top();              // Reset the total vlaue to previous total value
            cout << "=> " << totalValue << endl;    // Print total value

        } else if (inputValue == "C") { // Clear

            totalValue = 0; // Reset total value
            
            // Remove all values from stack
            while (!values.empty()) {

                values.pop();

            }

            values.push(totalValue);                // Push total value back onto stack
            cout << "=> " << totalValue << endl;    // Print total value

        } else {    // User inputted a number

            value = stoi(inputValue, nullptr, 10);  // Convert to integer

            cin >> operation;                       // Get the operation to execute

            // Determine which operation was specified and do appropriate math
            // Push the updated total number onto the stack
            switch (operation) {

                case '+':
                    totalValue += value;
                    cout << "=> " << totalValue << endl;
                    values.push(totalValue); 
                    break;

                case '-':
                    totalValue -= value;
                    cout << "=> " << totalValue << endl;
                    values.push(totalValue); 
                    break;

                case '*':
                    totalValue *= value;
                    cout << "=> " << totalValue << endl;
                    values.push(totalValue); 
                    break;

                case '/':
                    totalValue /= value;
                    cout << "=> " << totalValue << endl;
                    values.push(totalValue); 
                    break;

                case 'U':
                    values.pop();
                    totalValue = values.top();
                    cout << "=> " << totalValue << endl; 
                    break;

                case 'C':
                    totalValue = 0;
            
                    while (!values.empty()) {

                        values.pop();

                    }

                    values.push(totalValue);
                    break;

                default:
                    cout << "Not a valid operation\n";

            }

        }

    }

    return 0;

}