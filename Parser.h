/* 
 * File:   Parser.h
 * Author: gphillips
 *
 * Created on May 17, 2011, 5:26 PM
 */

#ifndef PARSER_H
#define	PARSER_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <map>
using namespace std;

class Parser {
public:
    Parser(char* filename);
    
    // returns the errors
    list<string> ParseFile();
    
    // Object Deletion
    ~Parser(void);
private:
    //comment striping code
    int stripComments();
    int ParseDefaults();
    int ParseLocations();
    int ParseItems();
    //Player ParsePlayer();
    
    // Parsing Data
    string file_data;
    list<string> errors;
    map<string, char> locations;
    map<string, char> items;
};

#endif