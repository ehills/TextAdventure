/* 
 * File:   Item.h
 * Author: gphillips
 *
 * Created on May 22, 2011, 9:26 PM
 */

#ifndef ITEM_H
#define	ITEM_H

#include <string>
#include <iostream>
using namespace std;

class Location;

/* Item class will store all relevant information for a particular item */
class Item {
   Location* location;
   string name;
   string description;
   
public:
   /* Constructor sets up initial variables */
   Item(string name, string description);
   
   /* Default constructor to set up an empty Item*/
   Item();
   
   /* Returns the name of the Item */
   string getName(void);

   /* Sets the name of the item */
   void setName(string name);
   
   /* Returns the name of the Item */
   bool hasLocation(void);
   
   /* Returns the name of the Item */
   Location* getLocation(void);

   /* Sets the name of the item */
   void setLocation(Location* location);

   /* Returns a description of the item */
   string getDescription(void);

   /* Sets a description for the item */
   void setDescription(string description);

   /* Prints out the Items name and description */
   void print();
   
   /* Destructor */
   ~Item(void);
};


#endif	/* ITEM_H */

