#include "Item.h"

/* Constructor sets up initial variables */
Item::Item(string name, string description) {
	this->name = name;
	this->description = description;
	this->location = NULL;
}

/* Default constructor to set up an empty Item*/
Item::Item() {
}

/* Returns the name of the Item */
string Item::getName(void) {
	return this->name;
}

/* Sets the name of the item */
void Item::setName(string name) {
	this->name = name;
}

bool Item::hasLocation(void) {
	return (this->location != NULL);
}

Location* Item::getLocation(void) {
	return this->location;
}

/* Sets the name of the item */
void Item::setLocation(Location* location) {
	this->location = location;
}

/* Returns a description of the item */
string Item::getDescription(void) {
	return this->description;
}

/* Sets a description for the item */
void Item::setDescription(string description) {
	this->description = description;
}

/* Prints out the Items name and description */
void Item::print() {
	cout << this->name << ", " << this->description << endl;
}

/* Add an attribute to an item */
void Item::addAttribute(string attribute_name, bool is) {
	this->attributes.insert(pair<string, bool>(attribute_name, is));
}

/* Returns an items attribute */
bool Item::hasAttribute(string attribute_name){
	if (this->attributes.count(attribute_name) > 0) {
		return this->attributes[attribute_name];
	}
	return false;
}

/* Returns an items attribute */
void Item::setAttribute(string attribute_name, bool is) {
	this->attributes[attribute_name] = is;

}

/* Destructor */
Item::~Item(void) {
}
