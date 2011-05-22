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

/* Player Class will have a description, name, maximum number of items,
 * current number of items held, the current location and a location which
 * will store the inventory.
 */
class Player {
   string name;
   string description;
   int max_items;
   Location* current_location;
   Location* inventory;
 public:
   /* Constructor */
   Player();

   /* Destructor */
   ~Player();

   /* Gets player name */
   string getName(void);

   /* Sets player name */
   void setName(string name);

   /* Gets player description */
   string getDescription(void);

   /* Sets player description */
   void setDescription(string description);

   /* Returns the number of items currently held by the player */
   int getNumberOfItems(void);

   /* Returns the max number of items the player can hold */
   int getMaxItems(void);

   /* Sets the number of max items the player can hold */
   void setMaxItems(int max_items);

   /* Returns the players starting location */
   Location* getLocation(void);

   /* Sets the players starting location */
   void setLocation(Location* location);

   /* Returns the players inventory location */
   Location* getInventory(void);

   /* Sets the players inventory location */
   void setInventory(Location* inventory);
};

#endif

