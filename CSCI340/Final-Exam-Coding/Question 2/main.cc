/* 	
  Robi Korneta
	Z1816167
	CSCI 340 - 1
	
    I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/


#include <iostream>
#include <list>

#include "DoublyLinkedList.h"

using namespace std;

int main() {

    DoublyLinkedList l;

    // Inserting values into the list
    cout << "*** Testing Insertion ***\n\n";

    l.Insertion(5);
    l.Insertion(18);
    l.Insertion(2);
    l.Insertion(1);
    l.Insertion(15);
    l.Insertion(24);
    l.Insertion(55);
    l.Insertion(37);
    l.Insertion(67);
    l.Insertion(43);
    l.DisplayForward();

    // Deleting values from the list
    cout << "\n*** Testing Deletion ***\n\n";
    l.Deletion();
    l.Deletion();
    l.Deletion();
    l.DisplayForward();

    // Inserting values at the end of the list
    cout << "\n*** Testing Insert Last ***\n\n";
    l.InsertLast(23);
    l.InsertLast(45);
    l.InsertLast(19);
    l.DisplayForward();

    // Inserting values at the front of the list
    cout << "\n*** Testing Insert First ***\n\n";
    l.InsertFirst(99);
    l.InsertFirst(33);
    l.InsertFirst(74);
    l.DisplayForward();

    // Deleting values from the end of the list
    cout << "\n*** Testing Delete Last ***\n\n";
    l.DeleteLast();
    l.DeleteLast();
    l.DeleteLast();
    l.DisplayForward();

    // Deleting values at the front of the list
    cout << "\n*** Testing Delete First ***\n\n";
    l.DeleteFirst();
    l.DeleteFirst();
    l.DeleteFirst();
    l.DisplayForward();

    // Inserting values after the specified item
    cout << "\n*** Testing Insert After ***\n\n";
    l.InsertAfter(l.frontNode, 22);
    l.DisplayForward();

    // Deleting item specified
    cout << "\n*** Testing Delete ***\n\n";
    l.Delete(l.frontNode);
    l.DisplayForward();

    // Displaying list in forward manner
    cout << "\n*** Testing Display Forward ***\n\n";
    l.DisplayForward();

    // Displaying list in backward manner
    cout << "\n*** Testing Display Backward ***\n\n";
    l.DisplayBackward();

    return 0;

}

