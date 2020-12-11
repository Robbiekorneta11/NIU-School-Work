//************************************
//
// Triangle.h
// CSCI 241 Assignment 12
// 
// Created by Robi Korneta Z1816167
//
//************************************

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include <string>

using namespace std;

class Triangle : public Shape {

        private:
                int height;				//Height of the triangle
                int base;				//Base of the triangle

        public:
                Triangle(const string&, int, int);	//Constructor
                void print();				//Override print
                double get_area();			//Override get_area

};

#endif


