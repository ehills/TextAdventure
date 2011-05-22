/**
 * Class: Item
 * File: Item.cpp
 * Date: May 17 2011
 * Description: This is the file that will be used for the Item once it
 *              has been parsed from the users file.
 **/

#include <string>
#include <iostream>
using namespace std;

/* Item class will store all relevant information for a particular item */
class Item {
	string name;
	string description;
public:
	/* Constructor sets up initial variables */
	Item(string name, string description) {
		this->name = name;
		this->description = description;
	}

	/* Default constructor to set up an empty Item*/
	Item(){}

	/* Returns the name of the Item */
	string getName(void) {
		return this->name;
	}

	/* Sets the name of the item */
	void setName(string name) {
		this->name = name;
	}

	/* Performs verb on object */
	void doVerb(string verb) {
                cout << "Sorry you can not " << verb << " on " << this->getName() << endl;
	}

	/* Returns a description of the item */
	string getDescription(void) {
		return this->description;
	}

	/* Sets a description for the item */
	void setDescription(string description) {
		this->description = description;
	}

	/* Prints out the Items name and description */
	void print() {
		cout << this->name << ", " << this->description << endl;
	}

	/* Destructor */
	~Item(void) {
	}
};
