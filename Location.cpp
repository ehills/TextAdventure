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
Location::Location(string variable_name, string name, string description) {
    this->name = name;
    this->variable_name = variable_name;
    this->description = description;
    this->north = NULL;
    this->south = NULL;
    this->west = NULL;
    this->east = NULL;
}

/* Returns the name of this location */
string Location::getName(void) {
    return this->name;
}

/* Sets the name of this Location */
void Location::setName(string name) {
    this->name = name;
}

/* Returns the name of this location */
string Location::getVariableName(void) {
    return this->variable_name;
}

/* Sets the name of this Location */
void Location::setVariableName(string variable_name) {
    this->variable_name = variable_name;
}

/* Returns the description of this room */
string Location::getDescription(void) {
    return this->description;
}

/* Sets the description of this room */
void Location::setDescription(string description) {
    this->description = description;
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

/* Destructor */
Location::~Location(void) {
}
