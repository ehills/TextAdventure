#ifndef COMPILER_H_
#define	COMPILER_H_
#include "Parser.h"
using namespace std;

class Compiler {
	string CompileNounVerb(Item *item);
	string getItem(string expression);
	string getLocation(string expression);
	string CompileSingleVerb(string commands);
	string CompileVerb(string line);
	string getVerbSynonyms(string);
public:
	Parser* parser;
	Compiler(char* filename);
	void Compile();
	~Compiler(void);
};
#endif
