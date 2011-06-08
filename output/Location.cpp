/**
 * Class: Location
 * File: Location.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for each room
 **/
#include "Location.h"

string toLower(string text) {
	size_t pos = 0;
	string ret = "";
	while (pos < text.length()) {
		ret += tolower(text.at(pos));
		pos++;
	}
	return ret;
}

Location::Location(string name, string description) {
	this->name = name;
	this->description = description;
	this->north = NULL;
	this->south = NULL;
	this->west = NULL;
	this->east = NULL;
}

Location::Location() {
	this->north = NULL;
	this->south = NULL;
	this->west = NULL;
	this->east = NULL;
}

string Location::getName(void) {
	return this->name;
}

void Location::setName(string name) {
	this->name = name;
}

string Location::getDescription(void) {
	return this->description;
}

void Location::setDescription(string description) {
	this->description = description;
}

void Location::addItem(string item_name, Item* item) {
	if (item->hasLocation()) {
		item->getLocation()->removeItem(item_name);
	}
	item->setLocation(this);
	this->items.insert(pair<string, Item*> (toLower(item_name), item));
}

bool Location::hasItem(string item_name) {
	return this->items.count(toLower(item_name)) != 0;
}

int Location::getItemCount() {
	return this->items.size();
}

void Location::removeItem(string item_name) {
	this->items.erase(toLower(item_name));
}

string Location::printNameAndDescription() {
	string name_and_description;
	name_and_description += "\t\t\t" + this->getName() + "\n" + this->getDescription();
	return name_and_description;
}

/* Returns the name of each item in this location */
string Location::listItems(void) {
	string the_items, item;
	int count;
	map<string, Item*>::iterator it;
	for (it = items.begin(), count=0; it != items.end(); count++, ++it) {
		item += "[" + (it->second->getName()) + "] ";
	}
	if (count == 0) {
		the_items += "Items: None";
	} else {
		the_items += "Items: " + item;
	}
	return the_items;
}

bool Location::hasNorth(void) {
	return (this->north != NULL);
}

bool Location::hasSouth(void) {
	return (this->south != NULL);
}

bool Location::hasEast(void) {
	return (this->east != NULL);
}

bool Location::hasWest(void) {
	return (this->west != NULL);
}

Location* Location::getNorth(void) {
	return this->north;
}

Location* Location::getSouth(void) {
	return this->south;
}

Location* Location::getEast(void) {
	return this->east;
}

Location* Location::getWest(void) {
	return this->west;
}

void Location::setNorth(Location* location) {
	this->north = location;
}

void Location::setSouth(Location* location) {
	this->south = location;
}

void Location::setEast(Location* location) {
	this->east = location;
}

void Location::setWest(Location* location) {
	this->west = location;
}

Location::~Location(void) {
}
