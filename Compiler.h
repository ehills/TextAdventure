#ifndef COMPILER_H_
#define	COMPILER_H_
#include "Parser.h"
using namespace std;

class Compiler {
public:
    Compiler();
    void Compile(char* filename);
    ~Compiler(void);
};


#endif