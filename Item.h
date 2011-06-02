#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <map>
#include <iostream>
#include "Location.h"
using namespace std;

/* Item class stores all information relevant to a particular item object */
class Item {
    string variable_name;
    string name;
    string description;
    string attribute_string;
    map<string, string> verb_expressions;
    map<string, bool> attributes;
    Location* location;
public:
     /* Constructor sets up initial variables */
    Item(string name, string description, map<string, string>);
    /* Default constructor to set up an empty Item*/
    Item();
    /* Returns the name of the Item */
    string getName(void);
    /* Sets the name of the item */
    void setName(string name);
    /* Returns the name of the Item */
    string getVariableName(void);
    /* Sets the name of the item */
    void setVariableName(string name);
    /* Returns a description of the item */
    string getDescription(void);
    /* Sets a description for the item */
    void setDescription(string description);
    /* Adds a verb to the list of valid verbs for this item */
    map<string, string> getVerbs();
    void addVerb(string verb, string expression);
    void addVerbs(map<string, string> verb_expressions);
    map<string, bool> getAttributes();
    void setAttributes(map<string, bool> attributes);
    void printVerbs();
    /* Removes a verb from the list of valid verbs for this item */
    void removeVerb(string verb);
    /* Prints out the Items name and description */
    void print();
    /* Returns the value associated with a key verb */
    string getVerbExpression(string verb);
    
    Location* getLocation(void);
    void setLocation(Location* location);

    void setAttributeString(string);

    string getAttributeString(void);

    /* Destructor */
    ~Item();
};


#endif
