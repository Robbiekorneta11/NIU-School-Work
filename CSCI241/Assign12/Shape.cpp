//************************************
//
// Shape.cpp
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#include "Shape.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * Constructor
 *
 * @param s The color of the shape
 * **************************************************/
Shape::Shape(const string& s) : color(s) {}

/**
 * Destructor
 * **************************************************/
Shape::~Shape() {}

/**
 * Prints the color
 * **************************************************/
void Shape::print() const {

	cout << color;

}
