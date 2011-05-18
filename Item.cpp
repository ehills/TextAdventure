/**
 * Class: Item
 * File: Item.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for an item
 **/

#include "Item.h"

/* Constructor */
Item::Item(string name, string description) {
    this->name = name;
    this->description = description;
}

Item::Item() {
}

string Item::getName(void) {
    return name;
}

void Item::setName(string name) {
    this->name = name;
}

string Item::getDescription(void) {
    return description;
}

void Item::setDescription(string description) {
    this->description = description;
}

Item::~Item(void) {
}