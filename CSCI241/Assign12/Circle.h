//************************************
//
// Circle.h
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include "Shape.h"

using namespace std;

class Circle : public Shape {

	private:
		int radius;			//Radius of the circle

	public:
		Circle() = default;		//Default constructor
		Circle(const string&, int);	//Constructor
		void print();			//Override print
		double get_area();		//Override get_area

};

#endif
