/**
 * Class: Location
 * File: Location.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for each room
 **/
#include "Location.h"

/* Constructor */
Location::Location() {
    this->name = "";
    this->description = "";
    this->items = "";
}

/* Constructor */
Location::Location(string name, string description, list<int> items) {
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
void Location::addItem(string item_name) {
    this->items.insert(item_name);
}

/* Removes an item from the room */
void Location::removeItem(string item_name) {
    this->items.erase(item_name);
}
    
string listItems(void) {
    return "NOT DONE";
}

/* Constructor */
Location::~Location(void) {
    
}
