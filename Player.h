/**
 * Class: Player Header File
 * File: Player.h
 * Date: May 16 2011
 * Description: Contains the Player header.
 **/
#ifndef PLAYER_H_
#define PLAYER_H_
#include <cstdlib>
#include <iostream>
#include "Location.h"

using namespace std;

class Player {
   string name;
   string variable_name;
   string description;
   int max_items;
   int current_number_of_items;
   Location current_location;
   Location inventory;
public:
   Player();
   Player(string, string, int, int, Location, Location);
   ~Player();
   string getName(void);
   void setName(string name);
   string getVariableName(void);
   void setVariableName(string variable_name);
   string getDescription(void);
   void setDescription(string description);
   int getNumberOfItems(void);
   void setNumberOfItems(int number_of_items);
   int getMaxItems(void);
   void setMaxItems(int max_items);
   Location getLocation(void);
   void setLocation(Location location);
   Location getInventory(void);
   void setInventory(Location inventory);
};

#endif

