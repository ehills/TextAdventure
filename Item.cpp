/**
 * Class: Item
 * File: Item.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for an item
 **/

#include <iostream>
#include <cstdlib>
using namespace std;

/* Item class stores all information relevant to a particular item object */
class Item {
   string name;
   string description;
   int weight;
public:
   Item(string, string, int);
   ~Item();
   string getName(void) {return name;}
   void setName(string name) {this->name = name;}
   string getDescription(void) {return description;}
   void setDescription(string description) {this->description = description;}
   int getWeight(void) {return weight;}
   void setWeight(int weight) {this->weight = weight;}
};

/* Constructor */
Item::Item(string name, string description, int weight) {
   this->name = name;
   this->description = description;
   this->weight = weight;
}
