//************************************
//
// Triangle.cpp
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#include "Triangle.h"
#include <iostream>
#include <string>

/**
 * Constructor
 *
 * @param c The color of the shape
 * @param h The height of the triangle
 * @param b The base of the triangle
 * **************************************************/
Triangle::Triangle(const string& c, int h, int b) : Shape(c), height(h), base(b) {}

/**
 * Print the characteristics of the triangle
 * **************************************************/
void Triangle::print() {

        Shape::print();

        cout << " triangle, "; 
	cout << "height " << height << ", "; 
	cout << "base " << base << ", ";
        cout << "area " << get_area() << endl;

}

/**
 * Calculate the area of the triangle
 *
 * @return The area of the triangle
 * **************************************************/
double Triangle::get_area() {

        return 0.5 * height * base;

}

