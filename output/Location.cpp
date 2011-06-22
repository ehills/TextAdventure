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

Location::Location(string name, string description, string variable_name) {
	this->name = name;
	this->description = description;
	this->north = NULL;
	this->south = NULL;
	this->west = NULL;
	this->east = NULL;
	this->variable_name = variable_name;
	this->showItems = true;
}

Location::Location() {
	this->north = NULL;
	this->south = NULL;
	this->west = NULL;
	this->east = NULL;
	this->variable_name = variable_name;
	this->showItems = true;
}

string Location::getVariableName() {
	return this->variable_name;
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

void Location::addItem(string item_name, Location* item) {
	if (item->hasLocation()) {
		item->getLocation()->removeItem(item_name);
	}
	item->setLocation(this);
	this->items.insert(pair<string, Location*> (toLower(item_name), item));
}

bool Location::hasItem(string item_variable_name) {
	map<string, Location*>::iterator it;
	for (it = items.begin(); it != items.end(); it++) {
		if (it->second->getVariableName() ==  item_variable_name) {
			return true;
		}
	}
	return false;
}

bool Location::itemHasItem(string item_name) {
	map<string, Location*>::iterator it;
	for (it = items.begin(); it != items.end(); it++) {
		if (it->second->hasItem(item_name) && it->second->getShowItems()) {
			return true;
		}
	}
	return false;
}

int Location::getItemCount() {
	return this->items.size();
}

void Location::removeItem(string item_name) {
	this->items.erase(toLower(item_name));
}

string Location::printNameAndDescription() {
	string  name_and_description = "***" + this->getName() + "***\n" + this->getDescription();
	return name_and_description;
}

string Location::listItems(string default_item_name) {
	string the_items;
	int count;
	map<string, Location*>::iterator it;
	for (it = items.begin(), count=0; it != items.end(); count++, ++it) {
		the_items += "[" + (it->second->getName()) + "] ";
		if(it->second->getItemCount() > 0  && it->second->getShowItems()) {
			the_items += it->second->listItems("");
		}
	}
	if (count == 0 || !showItems) {
		the_items = default_item_name;
	} else {
		the_items = default_item_name + the_items;
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

bool Location::hasLocation(void) {
	return (this->location != NULL);
}

Location* Location::getLocation(void) {
	return this->location;
}

void Location::setLocation(Location* location) {
	this->location = location;
}

void Location::addAttribute(string attribute_name, bool is) {
	this->attributes.insert(pair<string, bool>(attribute_name, is));
}

bool Location::hasAttribute(string attribute_name){
	if (this->attributes.count(attribute_name) > 0) {
		return this->attributes[attribute_name];
	}
	return false;
}

void Location::setAttribute(string attribute_name, bool is) {
	this->attributes[attribute_name] = is;
}

void Location::setShowItems(bool showItems) {
	this->showItems = showItems;
}

bool Location::getShowItems() {
	return this->showItems;
}

Location::~Location(void) {
}
