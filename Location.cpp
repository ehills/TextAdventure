/**
 * Class: Location
 * File: Location.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for each room
 **/
#include "Location.h"

/* Default Constructor */
Location::Location() {
}

/* Constructor */
Location::Location(string name, string description, map<string, Item> items) {
    this->name = name;
    this->description = description;
    this->items = items;
}

// Directions

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

/* Adds an item to the room */
void Location::addItem(string item_name, Item item) {
    this->items.insert(pair<string, Item>(item_name, item));
}

/* Adds an item to the room */
bool Location::hasItem(string item_name) {
    return this->items.count(item_name) != 0;
}

/* Removes an item from the room */
void Location::removeItem(string item_name) {
    this->items.erase(item_name);
}

/* Iterates through all items in the room and prints there description */
void Location::listItems(void) {
   map<string,Item>::iterator it;
   for (it = items.begin(); it != items.end(); ++it) {
      cout << endl << it->second.getDescription();
   }
}

/* Destructor */
Location::~Location(void) {
}
