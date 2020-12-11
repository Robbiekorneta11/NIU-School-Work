//
//  functions.h
//  dog
//
//  Created by Robbie Korneta Z1816167
//

#ifndef functions_h
#define functions_h

#include <string>

class functions {

public:

        functions() = default;
        std::string toBinary(char*, int);
        void toHex(char*, int);
        std::string caesarCipher(char*, int, int);
        int rotation(char*, int, int);

};

#endif
