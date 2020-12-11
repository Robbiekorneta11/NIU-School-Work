//
//  sml.h
//  SimpleSim
//
//  Created by Robbie Korneta on 2/5/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

#ifndef sml_h
#define sml_h

//Input/Output Operations
#define READ 01
#define WRITE 02

//Store/Load Operations
#define STORE 11
#define LOAD 12

//Arithmetic Operations
#define ADD 21
#define SUBTRACT 22
#define MULTIPLY 23
#define DIVIDE 24

//Transfer of Controls Operations
#define BRANCH 31
#define BRANCHZERO 32
#define BRANCHNEG 33
#define HALT 34

#endif /* sml_h */
