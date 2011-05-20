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

/* Returns the name of this location */
string Location::getName(void) {
    return this->name;
}

/* Sets the name of this Location */
void Location::setName(string name) {
    this->name = name;
}

/* Returns the description of this room */
string Location::getDescription(void) {
    return this->description;
}

/* Sets the description of this room */
void Location::setDescription(string description) {
    this->description = description;
}

/* Prints out the description plus the objects that are currently in this
 * location to the user
 */
void Location::printRoom(void) {
    cout << this->getDescription() << endl << this->listItems();
}

/* Adds an item to the room */
void Location::addItem(string item_name, Item item) {
    this->items.insert(pair<string, Item > (item_name, item));
}

/* Checks to see if item is in this location */
bool Location::hasItem(string item_name) {
    return this->items.count(item_name) != 0;
}

/* Removes an item from the room */
void Location::removeItem(string item_name) {
    this->items.erase(item_name);
}

/* Returns the description of each item in this location */
string Location::listItemsDescription(void) {    
    string the_items = "-- Items --";
    map<string, Item>::iterator it;
    for (it = items.begin(); it != items.end(); ++it) {
        the_items += ("\n" + it->second.getDescription());
    }
    return the_items;
}

/* Returns the name of each item in this location */
string Location::listItems(void) {    
    string the_items = "-- Items --";
    map<string, Item>::iterator it;
    for (it = items.begin(); it != items.end(); ++it) {
        the_items += ("\n" + it->second.getName());
    }
    return the_items;
}


/* Returns the location pointed to by north */
Location* Location::getNorth(void) {
    return this->north;
}

/* Returns the location pointed to by south */
Location* Location::getSouth(void) {
    return this->south;
}

/* Returns the location pointed to by east */
Location* Location::getEast(void) {
    return this->east;
}

/* Returns the location pointed to by west */
Location* Location::getWest(void) {
    return this->west;
}

/* Sets the location pointed to by north */
void Location::setNorth(Location* location) {
    this->north = location;
}

/* Sets the location pointed to by south */
void Location::setSouth(Location* location) {
    this->south = location;
}

/* Sets the location pointed to by east */
void Location::setEast(Location* location) {
    this->east = location;
}

/* Sets the location pointed to by west */
void Location::setWest(Location* location) {
    this->west = location;
}

/* Destructor */
Location::~Location(void) {
}
