#ifndef COMPILER_H_
#define	COMPILER_H_
#include "Parser.h"
using namespace std;

class Compiler {
	string getItem(string expression);
	string getLocation(string expression);
	string CompileSingleVerb(string commands);
	string CompileVerbNoun(Item *item);
	string CompileVerbNounJoin(Item *item);
	string CompileVerb(string line);
	string getSynonyms(string, string);
public:
	Parser* parser;
	Compiler(char* filename);
	void Compile();
	~Compiler(void);
};
#endif
