/**
 * Class: Item
 * File: Item.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for an item
 **/

#include "Item.h"


 /* Constructor sets up initial variables */
 Item::Item(string name, string description,
            map<string, string> verb_expressions) {
    this->name = name;
    this->description = description;
    this->verb_expressions = verb_expressions;
}

/* Default constructor to set up an empty Item*/
Item::Item() {
}

/* Returns the name of the Item */
string Item::getName(void) {
    return this->name;
}

/* Sets the name of the item */
void Item::setName(string name) {
    this->name = name;
}

/* Returns a description of the item */
string Item::getDescription(void) {
    return this->description;
}

/* Sets a description for the item */
void Item::setDescription(string description) {
    this->description = description;
}

/* Adds a verb to the list of valid verbs for this item */
void Item::addVerb(string verb, string expressions) {
    this->verb_expressions.insert(pair<string, string > (verb, expressions));
}

void Item::addVerbs(map<string, string> verb_expressions) {
    
    map<string, string>::iterator it;
    for (it = verb_expressions.begin(); it != verb_expressions.end(); it++) {
         this->verb_expressions[it->first] = it->second;
    }
   
}

map<string, bool> Item::getAttributes() {
    return this->attributes;
}

void Item::setAttributes(map<string, bool> attributes) {
    this->attributes = attributes;
}

/* Removes a verb from the list of valid verbs for this item */
void Item::removeVerb(string verb) {
    this->verb_expressions.erase(verb);
}

/* Returns the value associated with a key verb */
string Item::getVerbExpression(string verb) {
    map<string, string>::iterator it;
    it = verb_expressions.find(verb);
    return it->second;
}

/* Prints out the Items name and description */
void Item::print() {
    cout << this->name << ", " << this->description << endl;
}

void Item::printVerbs() {
    map<string, string>::iterator it;
    for (it = this->verb_expressions.begin(); it != this->verb_expressions.end(); it++) {
        cout << it->first << endl << it->second << endl;
    }
}

/* Destructor */
Item::~Item(void) {
}
