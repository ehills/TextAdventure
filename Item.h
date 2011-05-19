#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <map>
#include <iostream>
using namespace std;

/* Item class stores all information relevant to a particular item object */
class Item {
    string name;
    string description;
    map<string, string> verb_expressions;
    map<string, bool> attributes;
public:
     /* Constructor sets up initial variables */
    Item(string name, string description, map<string, string>);
    /* Default constructor to set up an empty Item*/
    Item();
    /* Returns the name of the Item */
    string getName(void);
    /* Sets the name of the item */
    void setName(string name);
    /* Returns a description of the item */
    string getDescription(void);
    /* Sets a description for the item */
    void setDescription(string description);
    /* Adds a verb to the list of valid verbs for this item */
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
    /* Destructor */
    ~Item();
};


#endif
