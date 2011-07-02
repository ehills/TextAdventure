#ifndef PARSER_H_
#define	PARSER_H_
#include <fstream>
#include <list>
#include <iostream>
#include <cstdlib>
#include <map>
#include "Location.h"
#include "Item.h"
#include "Player.h"

using namespace std;

class Parser {
	int stripComments(); // Comment striping code
	int ParseDefaults();
	int ParseLocations();
	int ParsePlayer();
	int ParseItems();
	void ParseLocation(string data, Location* location);
	void ParseItem(string data, Item* item);
	string file_data;
	Location* inventory;
public:
	Parser(char* filename);
	list<string> ParseFile(); // Returns the errors
	string gameName;
	string gameCredits;
	string initialDescription;
	string defaultResponse;
	string defaultInventoryName;
	string defaultInteractiveName;
	string defaultNoObjects;
	Location *initialLocation;
	list<string> errors;
	map<string, Location*> locations;
	map<string, Item*> items;
	map<string, string> default_verb_expressions;
	map<string, string> default_location_verb_expressions;
	Player* player;
	~Parser(void);
};
#endif
