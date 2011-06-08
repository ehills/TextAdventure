/* 
 * File:   Item.h
 * Author: gphillips
 *
 * Created on May 22, 2011, 9:26 PM
 */

#ifndef ITEM_H
#define	ITEM_H

#include <string>
#include <iostream>
#include <map>

using namespace std;

class Location;

/* Item class will store all relevant information for a particular item */
class Item {
	Location* location;
	string name;
	string description;
	map<string, bool> attributes;
	string variable_name;
public:
	/* Constructor sets up initial variables */
	Item(string name, string description, string variable_name);
	Item();
	string getName(void);
	void setName(string name);
	bool hasLocation(void);
	Location* getLocation(void);
	void setLocation(Location* location);
	string getDescription(void);
	void setDescription(string description);
	void addAttribute(string, bool);
	bool hasAttribute(string);
	void setAttribute(string, bool);
	string getVariableName(void);
	~Item(void);
};
#endif

