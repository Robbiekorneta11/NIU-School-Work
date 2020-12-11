
CXX = g++
CXXFLAGS = -Wall -std=c++11

assign4: main.o functions.o
        $(CXX) $(CXXFLAGS) -o assign4 $^

main.o: main.cpp functions.h
functions.o: functions.cpp functions.h

clean:
        rm -f assign4 *.o


