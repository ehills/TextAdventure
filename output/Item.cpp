#include "Item.h"

/* Constructor sets up initial variables */
Item::Item(string name, string description) {
    this->name = name;
    this->description = description;
    this->location = NULL;
}

/* Default constructor to set up an empty Item*/
Item::Item() {
}

/* Returns the name of the Item */
Item::string Item::getName(void) {
    return this->name;
}

/* Sets the name of the item */
void Item::setName(string name) {
    this->name = name;
}

/* Returns the name of the Item */
bool Item::hasLocation(void) {
    return (this->location != NULL);
}

/* Returns the name of the Item */
Location* Item::getLocation(void) {
    return this->location;
}

/* Sets the name of the item */
void Item::setLocation(Location* location) {
    this->location = location;
}

/* Returns a description of the item */
string Item::getDescription(void) {
    return this->description;
}

/* Sets a description for the item */
void Item::setDescription(string description) {
    this->description = description;
}

/* Prints out the Items name and description */
void Item::print() {
    cout << this->name << ", " << this->description << endl;
}

/* Destructor */
Item::~Item(void) {
}