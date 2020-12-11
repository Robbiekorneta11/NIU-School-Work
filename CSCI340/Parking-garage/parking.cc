/* 	Robi Korneta
	Z1816167
	CSCI 340 - 1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.

*/

#include <string>
#include <vector>
#include "parking.h"

using namespace std;

int idNum = 1;      //Id of the car
vector<CAR> cars2;  //Vector to keep track of cars for the id num

int main()
{

    string line;            //Input file line
    char act;               //Arrival or departure
    string lp;              //License plate
    bool found = false;     //Check to see if car alrready exists
    deque<CAR> D;           //Deque to hold the cars
    stack<CAR> S;           //Stack to temporarily hold cars that are being moved

    //Get the line from the input file
    while (getline(cin, line))
    {

        found = false; //Set found to false

        get_input_vals(line, act, lp); //Get the input values

        CAR car; //Create a car object

        for (size_t i = 0; i < cars2.size(); i++)
        {

            CAR c = cars2.at(i); //Get the car object at i

            if (c.lp == lp) //Check to see if the license plates matches
            {

                found = true; //Set found to true
                car = c; //Copy c to car
                break;
            }
        }

        if (!found) //If the car license plate is not found
        {

            car.id = idNum; //Set the car id
            car.lp = lp; //Set the car license plate
            car.no_mv = 0; //Set the move numbers
            cars2.push_back(car); //Push car into the vector
            idNum++; //Increment id num
        }

        //Check to see if the is an arrival or departure
        switch (act)
        {
        case 'D':
            departure(lp, D, S);
            break;

        case 'A':
            arrival(car, D);
            break;

        //Invalid
        default:
            cout << "'" << act << "': invalid action! " << endl
                 << endl;
            break;
        }
    }

    return 0;
}

/*
*   Get the values from the line of the file
*
*   @param line - the line from the file
*   @param act  - arrival or departure
*   @param lp   - the license plate
*/

void get_input_vals(const string &line, char &act, string &lp)
{

    CAR car; //Car object
    int c = 1; //Check for the count of :

    lp = ""; //Reset license plate

    for (size_t i = 0; i < line.length(); i++)
    {

        char x = line[i]; //The current character

        if (x == ':') //Check for :
        {

            c += 1;
        }
        else
        {

            switch (c)
            {
            case 1:
                act = line[i];
                break;
            case 2:
                lp += line[i];
                break;

            default:
                cout << "Done" << endl;
                break;
            }
        }
    }
}

/*
*   Handle a car arriving at the parking garage
*
*   @param car - the car arriving
*   @param D   - the deque to insert the car into
*/

void arrival(const CAR &car, deque<CAR> &D)
{

    if (D.size() <= 10) //Check to make sure the garage isn't full
    {

        D.push_back(car); //Push car into deque
        cout << "Car " << car.id << " with license plate "
             << "\"" << car.lp << "\""
             << " has arrived." << endl;
    }
    else
    {

        cout << "the garage is full!" << endl;
    }

    cout << endl;
}

/*
*   Handle departures of cars
*
*   @param lp - the license plate of the car
*   @param D  - the deque of cars
*   @param S  - The temp stack to hold the moving cars
*/

void departure(const string &lp, deque<CAR> &D, stack<CAR> &S)
{

    deque<CAR>::iterator it = D.begin(); //Create iterator

    bool found = false; //Check to make sure the car is in the garage

    while (it != D.end())
    {

        CAR c = D.front(); //The front car
        c.no_mv++; //Incremenet the cars number of times it has been moved

        if (c.lp == lp)
        {

            D.pop_front(); //Remove from the deque
            found = true; //Found the car
            if (c.no_mv > 1) {

                cout << "Car " << c.id << " with license plate \"" << lp 
                << "\" has departed," << "\n\tcar was moved " << c.no_mv 
                << " times in the garage" << endl << endl; 

            } else {

                cout << "Car " << c.id << " with license plate \"" << lp 
                << "\" has departed," << "\n\tcar was moved " << c.no_mv 
                << " time in the garage" << endl << endl; 

            }
            
            break;
        }
        else
        {

            S.push(c); //Push into temp stack
            D.pop_front(); //Remove from deque
        }

        it++;
    }

    if (!found) //If the car wasn't in the parking garage
    {

        cout << "No car with license plate "
             << "\"" << lp << "\" is in the garage" << endl
             << endl;
    }

    while (!S.empty()) //Put cars back into deque
    {

        CAR c = S.top();
        S.pop();
        D.push_front(c);
    }
}
