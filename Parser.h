/* 
 * File:   Parser.h
 * Author: gphillips
 *
 * Created on May 17, 2011, 5:26 PM
 */

#ifndef PARSER_H_
#define	PARSER_H_
#include <fstream>
#include <list>
#include <iostream>
#include <cstdlib>
#include <map>
#include "Location.h"
#include "Item.h"
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
    map<string, Location> locations;
    map<string, Item> items;
};

#endif