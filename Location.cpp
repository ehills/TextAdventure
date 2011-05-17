/**
 * Class: Location
 * File: Location.cpp
 * Date: May 17 2011
 * Description: This will be the object that is created for each room
 **/
#include <iostream>
#include <cstdlib>
#include "Item.h"
#include <list>
using namespace std;

/* Location class will store all information relevant to a particular location*/
class Location {
   string name;
   string description;
   string shortDescription;
   list<Item> items;
public:
   Location(string, string, string, List);
   ~Location();
   string getName(void) {return name;}
   void setName(string name) {this->name = name;}
   string getDescription(void) {return description;}
   void setDescription(string description) {this->description = description;}
   string getShortDescr(void) {return shortDescription;}
   string setShortDescr(string shortD) {this->shortDescription = shortD;}
   void addItem(Item item);
   void removeItem(Item item);
   void makeDescription(void);
};

Location::Location(string name, string description,
                   string shortDescription, List items) {
   this->name = name;
   this->description = description;
   makeDescription(void);
   this->shortDescription = shortDescription;
   this->items = items;
}

/* Will make the new room description based off the original base and then
 * has each item description added to the rooms description.
 */
//////////////// ITEM CLASS NEEDS TO BE MADE //////////////
Location::makeDescription(void) {
   list<Item>::iterator iter;
   for (iter =items.begin(); iter != items.end(); ++iter) {
      this->description += (endl + *iter.getDescription);
   }
}

Location::addItem(Item item) {
   // to be dones
}

Location:removieItem(Item item) {
   // to be done
}

   
