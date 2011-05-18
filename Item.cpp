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

void Item::addVerb(string verb, string expression) {
   this->verb_expressions.insert(pair<string, string>(verb, expression));
}

void Item::removeVerb(string verb) {
   this->verb_expressions.erase(verb);
}

void Item::printVerb(void) {
   map<string, string>::iterator it;
   for (it = verb_expressions.begin(); it != verb_expressions.end(); ++it) {
      cout << it->first;
   }
}

string Item::getVerbExpression(string verb) {
   map<string, string>::iterator it;
   it = verb_expressions.find(verb);
   return it->second;
}   

Item::~Item(void) {
}
