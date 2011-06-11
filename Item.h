#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <map>
#include <iostream>
#include "Location.h"
using namespace std;

/* Item class stores all information relevant to a particular item object */
class Item {
	string variable_name; // Used as an item's unique identifier.
	string name;
	string description;
	string attribute_string;
	map<string, string> verb_expressions;
	map<string, bool> attributes;
	Location* location;
public:
	/* Constructor sets up initial variables */
	Item(string name, string description, map<string, string>);
	Item();
	string getName(void);
	void setName(string name);
	string getVariableName(void);
	void setVariableName(string name);
	string getDescription(void);
	void setDescription(string description);
	map<string, string> getVerbs();
	void addVerb(string verb, string expression);
	void addVerbs(map<string, string> verb_expressions);
	map<string, bool> getAttributes();
	void setAttributes(map<string, bool> attributes);
	void printVerbs();
	void removeVerb(string verb);
	void print();
	string getVerbExpression(string verb);
	Location* getLocation(void);
	void setLocation(Location* location);
	void setAttributeString(string);
	string getAttributeString(void);
	~Item();
};
#endif
