/**
 * Class: Item
 * File: Item.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for an item
 **/

#include "Item.h"

/* Constructor */
 Item::Item(string name, string description,
            map<string, string> verb_expressions) {
    this->name = name;
    this->description = description;
    this->verb_expressions = verb_expressions;
}

Item::Item() {
}

string Item::getName(void) {
    return this->name;
}

void Item::setName(string name) {
    this->name = name;
}

string Item::getDescription(void) {
    return this->description;
}

void Item::setDescription(string description) {
    this->description = description;
}

void Item::addVerb(string verb, string expressions) {
   this->verb_expressions.insert(pair<string, string>(verb, expressions));
}

void Item::removeVerb(string verb) {
   this->verb_expressions.erase(verb);
}

string Item::getVerbExpression(string verb) {
   map<string, string>::iterator it;
   it = verb_expressions.find(verb);
   return it->second;
}   

void Item::print() {
    cout << this->name << ", " << this->description << endl;
}   

Item::~Item(void) {
}
