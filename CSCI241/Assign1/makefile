#
# PROGRAM:    Assignment 1
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#

# Compiler variables
CXXFLAGS = -Wall -Werror -std=c++11

# Rules to link object code files to create executable file
all: bubble_sort insertion_sort selection_sort

bubble_sort: bubble_sort.o
	g++ $(CXXFLAGS) -o bubble_sort bubble_sort.o

insertion_sort: insertion_sort.o
	g++ $(CXXFLAGS) -o insertion_sort insertion_sort.o

selection_sort: selection_sort.o
	g++ $(CXXFLAGS) -o selection_sort selection_sort.o

# Rules to compile source code files to object code
bubble_sort.o: bubble_sort.cpp
	g++ $(CXXFLAGS) -c bubble_sort.cpp

insertion_sort.o: insertion_sort.cpp
	g++ $(CXXFLAGS) -c insertion_sort.cpp

selection_sort.o: selection_sort.cpp
	g++ $(CXXFLAGS) -c selection_sort.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o bubble_sort insertion_sort selection_sort
