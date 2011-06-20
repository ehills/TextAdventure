/* Description: This will be the object that is created for an item */

#include "Item.h"


/* Constructor sets up initial item variables */
Item::Item(string name, string description,
		map<string, string> verb_expressions) {
	this->name = name;
	this->description = description;
	this->verb_expressions = verb_expressions;
	this->showItems = true;
}

Item::Item() {
	this->location = NULL;
	this->showItems = true;
}

string Item::getName(void) {
	return this->name;
}

void Item::setName(string name) {
	this->name = name;
}

string Item::getVariableName(void) {
	return this->variable_name;
}

void Item::setVariableName(string name) {
	this->variable_name = name;
}

string Item::getDescription(void) {
	return this->description;
}

void Item::setDescription(string description) {
	this->description = description;
}

void Item::addVerb(string verb, string expressions) {
	this->verb_expressions.insert(pair<string, string > (verb, expressions));
}

map<string, string> Item::getVerbs() {
	return this->verb_expressions;
}

void Item::addVerbs(map<string, string> verb_expressions) {
	map<string, string>::iterator it;
	for (it = verb_expressions.begin(); it != verb_expressions.end(); it++) {
		this->verb_expressions[it->first] = it->second;
	}
}

map<string, bool> Item::getAttributes() {
	return this->attributes;
}

void Item::setAttributes(map<string, bool> attributes) {
	this->attributes = attributes;
}

void Item::removeVerb(string verb) {
	this->verb_expressions.erase(verb);
}

void Item::setItem(Item* item) {
	this->item = item;
}

Item* Item::getItem(void) {
	return this->item;
}

string Item::getVerbExpression(string verb) {
	map<string, string>::iterator it;
	it = verb_expressions.find(verb);
	return it->second;
}

void Item::print() {
	cout << this->name << ", " << this->description << endl;
}

void Item::printVerbs() {
	map<string, string>::iterator it;
	for (it = this->verb_expressions.begin(); it != this->verb_expressions.end(); it++) {
		cout << it->first << endl << it->second << endl;
	}
}

Location* Item::getLocation(void) {
	return this->location;
}
void Item::setLocation(Location* location) {
	this->location = location;
}

void Item::setAttributeString(string attribute_string) {
	this->attribute_string = attribute_string;
}

string Item::getAttributeString(void) {
	return this->attribute_string;
}

void Item::setShowItems(bool is) {
	this->showItems = is;
}

bool Item::getShowItems(void) {
	return this->showItems;
}

Item::~Item(void) {
}
