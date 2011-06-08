/**
 * Class: Location
 * File: Location.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for each room
 **/
#include "Location.h"

Location::Location() {
	this->north = NULL;
	this->south = NULL;
	this->west = NULL;
	this->east = NULL;
}

Location::Location(string variable_name, string name, string description) {
	this->name = name;
	this->variable_name = variable_name;
	this->description = description;
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

string Location::getVariableName(void) {
	return this->variable_name;
}

void Location::setVariableName(string variable_name) {
	this->variable_name = variable_name;
}

string Location::getDescription(void) {
	return this->description;
}

void Location::setDescription(string description) {
	this->description = description;
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
