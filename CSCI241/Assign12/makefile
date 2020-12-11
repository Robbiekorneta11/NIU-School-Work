#
# PROGRAM:    Assign12
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
        
# Rule to link object code files to create executable file
assign12: assign12.o Shape.o Circle.o Triangle.o Rectangle.o
	$(CXX) $(CXXFLAGS) -o assign12 $^

# Rules to compile source code file to object code
assign12.o: assign12.cpp Shape.h Circle.h Triangle.h Rectangle.h
Shape.o: Shape.cpp Shape.h
Circle.o: Circle.cpp Circle.h
Triangle.o: Triangle.cpp Triangle.h
Rectangle.o: Rectangle.cpp Rectangle.h

Circle.h: Shape.h
Triangle.h: Shape.h
Rectangle.h: Shape.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f assign12 *.o
