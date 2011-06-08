#include "Item.h"

/* Constructor sets up initial variables */
Item::Item(string name, string description, string variable_name) {
	this->name = name;
	this->description = description;
	this->location = NULL;
	this->variable_name = variable_name;
}

Item::Item() {
}

string Item::getVariableName() {
	return this->variable_name;
}

string Item::getName(void) {
	return this->name;
}

void Item::setName(string name) {
	this->name = name;
}

bool Item::hasLocation(void) {
	return (this->location != NULL);
}

Location* Item::getLocation(void) {
	return this->location;
}

void Item::setLocation(Location* location) {
	this->location = location;
}

string Item::getDescription(void) {
	return this->description;
}

void Item::setDescription(string description) {
	this->description = description;
}

void Item::addAttribute(string attribute_name, bool is) {
	this->attributes.insert(pair<string, bool>(attribute_name, is));
}

bool Item::hasAttribute(string attribute_name){
	if (this->attributes.count(attribute_name) > 0) {
		return this->attributes[attribute_name];
	}
	return false;
}

void Item::setAttribute(string attribute_name, bool is) {
	this->attributes[attribute_name] = is;
}

Item::~Item(void) {
}
