[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=3057893&assignment_repo_type=AssignmentRepo)
### CSCI 340 - Data Structures and Algorithm Analysis
                  
## Randomly Generated Integers

For this computer assignment, you are to write a C++ program to *generate random integers* in the range `LOW = 1`, `HIGH = 10000` and to store them in a `vector<int> v` of size `VEC_SIZE = 200`. Then, sort the contents of the vector (in ascending order) and display it on stdout.
  
The program is partially implemented. You can obtain the source file `rgi.cc` within this Git repository.

To sort the contents of a vector, use the `sort()` function in the STL. In addition to the `main()` routine, include the following subroutines in your program:

- `void genRndNums(vector<int> &v)` It generates `VEC_SIZE` integers and stores them in `vector v`. Initializes the random number generator (RNG) by calling the function `srand (SEED)` with the seed value `SEED = 1` and generates random integers by calling the function `rand()`.

- `void printVec(const vector<int> &v)` It displays the contents of `vector v` on stdout, printing exactly `NO_ITEMS = 12` numbers in a single line, except perhaps the last line. The sorted numbers need to be properly aligned on the output. For each number, allocate `ITEM_W = 5` spaces on stdout.

**Programming Notes:**

- Do not change existing implementation in `rgi.cc`. But you need to include any necessary headers and add necessary global constants. 

- Your source file are named `rgi.cc` and your header file is `rgi.h`. Guard the statements in your header file using the following format. (This is necessary because you don’t want the statements in a header file processed more than once.)

```c++
#ifndef H_RGI // should not be defined any place else 
#define H_RGI // same const value as for ifndef directive

// put all statements for your header file here

#endif
```

- Include all system header files (that you need in your program) in your header file. For example, to gain access to the `iostream` library, which defines a set of simple I/O operations, insert the line `#include <iostream>` in your header file, to gain access the I/O manipulators such as `setw`, insert the line `#include <iomanip>` in your header file; to access the vector container in the STL, insert the line `#include <vector>` in your header file; and to use the functions in the STL such as sort, insert the line `#include <algorithm>` in your header file. At the top of `rgi.cc`, we have inserted your header file `#include “rgi.h”`.
 
* You are not allowed to use any I/O functions from the C library, such as `scanf` or `printf`. Instead, use the I/O functions from the C++ library, such as `cin` or `cout`.

* Add documentation to your source file (e.g. https://google.github.io/styleguide/cppguide.html#Comments, http://faculty.cs.niu.edu/~mcmahon/CS241/241DocStandards.html), you can use what ever approach you want as long as its consistent and complete.

* We have included a `Makefile` for your reference, in future assignments you will need to build your own. To compile your code just type `make` in the project directory. To test your program, execute `./rgi.exe &> rgi.out`, which will put the output (including any error messages) in file `rgi.out`. You can find the correct output of this program in file `results01.out`, you can compare the two files by using `diff` on turing or hopper, `diff rgi.out results01.out`, if the files are the same there will be no output from `diff`.

When your program is ready for grading, ***commit*** and ***push*** your local repository to remote git classroom repository and follow the _**Assignment Submission Instructions**_. 

