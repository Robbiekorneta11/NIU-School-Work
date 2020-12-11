//*********************************************
//
// assign12.cpp
// CSCI 241 Assignment 12
// 
// Created By Robi Korneta Z1816167
//
//*********************************************

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include "Shape.h"          // Shape base class
#include "Circle.h"         // Circle derived class
#include "Rectangle.h"      // Rectangle derived class
#include "Triangle.h"       // Triangle derived class

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::vector;
using std::string;

int main() {

	cout << "Printing all shapes..." << endl << endl;

	//Create Vector shapes
	vector<Shape*> shapes; 

	//Initialize vector with shapes
	shapes.push_back(new Circle("Green", 10));
	shapes.push_back(new Rectangle("Red", 8, 6));
	shapes.push_back(new Triangle("Yellow", 8, 4));
	shapes.push_back(new Triangle("Black", 4, 10));
	shapes.push_back(new Circle("Orange", 5));
	shapes.push_back(new Rectangle("Blue", 3, 7));

	//Generically process each element in shapes
	for (size_t i = 0; i < shapes.size(); i++) {

		//Downcast pointers
		Circle* p1 = dynamic_cast<Circle*>(shapes[i]);
		Rectangle* p2 = dynamic_cast<Rectangle*>(shapes[i]);
		Triangle* p3 = dynamic_cast<Triangle*>(shapes[i]);

		if (p1 != nullptr) {

			p1->print();

		}

		if (p2 != nullptr) {

			p2->print();

		}

		if (p3 != nullptr) {

			p3->print();

		}

	}

	cout << endl;
	cout << "Printing only circles..." << endl << endl;

	//Go through and print only circles	
	for (size_t i = 0; i < shapes.size(); i++) {

		//Downcast pointers
		Circle* p = dynamic_cast<Circle*>(shapes[i]);

		if (p != nullptr) {

			p->print();

		}

	}

	//Go through and release memory held by vector
	for (size_t i = 0; i < shapes.size(); i++) {

		delete shapes[i];

	}

	return 0;

}
