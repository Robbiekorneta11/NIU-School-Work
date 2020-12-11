//************************************
//
// Rectangle.cpp
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#include "Rectangle.h"
#include <iostream>
#include <string>

/**
 * Constructor
 *
 * @param c The color of the shape
 * @param h The height of the rectangle
 * @param w The width of the rectangle
 * **************************************************/
Rectangle::Rectangle(const string& c, int h, int w) : Shape(c), height(h), width(w) {}

/**
 * Print the characteristics of the Rectangle
 * **************************************************/
void Rectangle::print() {

	Shape::print();

	cout << " rectangle, ";
        cout << "height " << height << ", "; 
	cout << "width " << width << ", ";
	cout << "area " << get_area() << endl;

}

/**
 * Calculate the Area of the rectangle
 *
 * @return The area of the rectangle
 * **************************************************/
double Rectangle::get_area() {

	return width * height;

}
