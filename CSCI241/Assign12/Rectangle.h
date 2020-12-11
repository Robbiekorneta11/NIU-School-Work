//************************************
//
// Rectangle.h
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include <string>

using namespace std;

class Rectangle : public Shape {

	private:
		int height;				//Height of the Rectangle
		int width;				//Width of the Rectangle

	public:
		Rectangle(const string&, int, int);	//Constructor
		void print();				//Override print
		double get_area();			//Override get_area

};

#endif
