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
public:
    Item(string name, string description, map<string, string>);
    Item();
    string getName(void);
    void setName(string name);
    string getDescription(void);
    void setDescription(string description);
    void addVerb(string verb, string expression);
    void removeVerb(string verb);
    void print();
    string getVerbExpression(string verb);
    ~Item();
};


#endif
