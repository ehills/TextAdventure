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
	Player();
	string getName(void);
	void setName(string name);
	string getDescription(void);
	void setDescription(string description);
	bool canCarry(void);
	int getNumberOfItems(void);
	int getMaxItems(void);
	void setMaxItems(int max_items);
	Location* getLocation(void);
	void setLocation(Location* location);
	Location* getInventory(void);
	void setInventory(Location* inventory);
	~Player();
};
#endif

