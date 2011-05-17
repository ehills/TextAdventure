/**
 * Class: Location
 * File: Location.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for each room
 **/
#include <iostream>
#include <cstdlib>
#include "Item.cpp"
#include <list>
using namespace std;

/* Location class will store all information relevant to a particular location*/
class Location {
   string name;
   string description;
   string shortDescription;
   list<Item> items;
public:
   Location(string, string, string, list<Item>);
   ~Location();
   string getName(void) {return name;}
   void setName(string name) {this->name = name;}
   string getDescription(void) {return description;}
   void setDescription(string description) {this->description = description;}
   string getShortDescr(void) {return shortDescription;}
   void setShortDescr(string shortD) {this->shortDescription = shortD;}
   void addItem(Item item);
   void removeItem(string item);
   void makeDescription(void);
};

/* Constructor */
Location::Location(string name, string description,
                   string shortDescription, list<Item> items) {
   this->name = name;
   this->description = description;
   makeDescription();
   this->shortDescription = shortDescription;
   this->items = items;
}

/* Will make the new room description based off the original base and then
 * has each item description added to the rooms description.
 */
void Location::makeDescription(void) {
   list<Item>::iterator iter;
   for (iter =items.begin(); iter != items.end(); ++iter) {
      //this->description += (endl + *iter.getDescription);
   }
}

/* Adds an item to the room */
void Location::addItem(Item item) {
   this->items.push_back(item);
}

/* Removes an item from the room */
void Location::removeItem(string item) {
    list<Item>::iterator iter;
    for (iter =items.begin(); iter != items.end(); ++iter) {
       if (iter->getName() == item) {
          this->items.remove(*iter);
       }
    }
}

   
