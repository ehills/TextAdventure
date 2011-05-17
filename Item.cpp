/**
 * Class: Item
 * File: Item.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for an item
 **/

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

/* Item class stores all information relevant to a particular item object */
class Item {
   string name;
   string description;
public:
   Item(string, string);
   ~Item();
   string getName(void) {return name;}
   void setName(string name) {this->name = name;}
   string getDescription(void) {return description;}
   void setDescription(string description) {this->description = description;}
};

/* Constructor */
Item::Item(string name, string description) {
   this->name = name;
   this->description = description;
}
