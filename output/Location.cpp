/**
 * Class: Location
 * File: Location.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for each room
 **/
#include "Location.h"

/* Default Constructor */
Location::Location() {
   this->north = NULL;
   this->south = NULL;
   this->west = NULL;
   this->east = NULL;
}


/* Constructor */
Location::Location(string name, string description) {
   this->name = name;
   this->description = description;
   this->north = NULL;
   this->south = NULL;
   this->west = NULL;
   this->east = NULL;
}

/* Destructor */
Location::~Location(void) {
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
string Location::printRoom(void) {
    return this->getDescription() + "\n" + this->listItemsDescription();
}

/* Adds an item to the room */
void Location::addItem(string item_name, Item* item) {
    cerr << "adding " << item_name << " to " << this->getName() << endl;
    if (item->hasLocation()) {
        item->getLocation()->removeItem(item_name);
    }
    item->setLocation(this);
    this->items.insert(pair<string, Item*> (item_name, item));
}

/* Checks to see if item is in this location */
bool Location::hasItem(string item_name) {
    return this->items.count(item_name) != 0;
}

/* Checks to see if item is in this location */
int Location::getItemCount() {
    return this->items.size();
}

/* Removes an item from the room */
void Location::removeItem(string item_name) {
    cerr << "removing " << item_name << " from " << this->getName() << endl;
    this->items.erase(item_name);
}

/* Returns the description of each item in this location */
string Location::listItemsDescription(void) {    
    string the_items;
    map<string, Item*>::iterator it;
    for (it = items.begin(); it != items.end(); ++it) {
        the_items += (it->second->getDescription());
    }
    return the_items;
}

/* Returns the name of each item in this location */
string Location::listItems(void) {    
    string the_items = "Items: ";
    map<string, Item*>::iterator it;
    for (it = items.begin(); it != items.end(); ++it) {
       the_items += ("\n" + it->second->getName() + " - " + it->second->getDescription());
    }
    return the_items;
}

/* Checks to see if the location can go north */
bool Location::hasNorth(void) {
   return (this->north != NULL);
}

/* Checks to see if the location can go south */
bool Location::hasSouth(void) {
   return (this->south != NULL);
}

/* Checks to see if the location can go east */
bool Location::hasEast(void) {
   return (this->east != NULL);
}

/* Checks to see if the location can go west */
bool Location::hasWest(void) {
   return (this->west != NULL);
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
