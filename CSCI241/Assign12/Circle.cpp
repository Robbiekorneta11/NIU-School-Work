//************************************
//
// Circle.cpp
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#include "Circle.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * Constructor
 *
 * @param s The color of the shap
 * @param r The radius of the circle
 * **************************************************/
Circle::Circle(const string& c, int r) : Shape(c), radius(r) {}

/**
 * Prints the characteristics of the Circle
 * **************************************************/
void Circle::print() {

	Shape::print();

	cout << " circle, "; 
	cout << "radius " << radius << ", ";
	cout << "area " << get_area() << endl;	

}

/**
 * Calculates the area of the circle
 *
 * @return The area of the circle
 * **************************************************/
double Circle::get_area() {

	return 3.14159 * radius * radius;

}
