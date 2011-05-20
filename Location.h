/* 
 * File:   Parser.h
 * Author: gphillips
 *
 * Created on May 17, 2011, 5:26 PM
 */

#ifndef LOCATION_H_
#define	LOCATION_H_
#include <iostream>
#include <cstdlib>
#include <map>
#include "Item.h"

using namespace std;

/* Location class will store all information relevant to a particular location*/
class Location {
public:
    Location(string, string, map<string, Item>);
    Location();

    // Details
    string getName(void);
    void setName(string name);
    string getDescription(void);
    void setDescription(string description);
    void printRoom(void);
    
    // Directions
    Location* getNorth(void);
    Location* getSouth(void);
    Location* getEast(void);
    Location* getWest(void);
    void setNorth(Location* location);
    void setSouth(Location* location);
    void setEast(Location* location);
    void setWest(Location* location);
    
    // Items
    void addItem(string item_name, Item item);
    bool hasItem(string item_name);
    void removeItem(string item_name);
    string listItemsDescription(void);
    string listItems(void);
    
    // Object Deletion
    ~Location(void);
private:
    string name;
    string description;
    Location* south;
    Location* north;
    Location* east;
    Location* west;
    map<string, Item> items;
};

#endif
