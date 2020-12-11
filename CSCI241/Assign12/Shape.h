//************************************
//
// Shape.h
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>

using namespace std;

class Shape {

	private:
		
		string color; 			//Color of the shape

	public:
		
		Shape() = default; 		//Default Constructor
		Shape(const string&); 		//Set up the color
		virtual ~Shape(); 		//Virtual - Destructor
		virtual void print() const; 	//Virtual - Print the shape color
		virtual double get_area() = 0;  //Pure Virtual - Get the area of the shape

};

#endif
