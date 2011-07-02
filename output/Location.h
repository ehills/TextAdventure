#ifndef LOCATION_H_
#define	LOCATION_H_
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

class Location;

/* Location class will store all information relevant to a particular location*/
class Location {
	string name;
	string description;
	Location* south;
	Location* north;
	Location* east;
	Location* west;
	map<string, Location*> items;
	map<string, bool> attributes;
	Location* location;
	string variable_name; // Used as a locations unique identifier.
	bool showItems;
public:
	Location(string, string, string);
	Location();
	string getName(void);
	void setName(string name);
	string getDescription(void);
	void setDescription(string description);
	string getVariableName(void);

	// These methods will deal with Location links
	Location* getNorth(void);
	Location* getSouth(void);
	Location* getEast(void);
	Location* getWest(void);
	void setNorth(Location* location);
	void setSouth(Location* location);
	void setEast(Location* location);
	void setWest(Location* location);
	bool hasNorth(void);
	bool hasSouth(void);
	bool hasEast(void);
	bool hasWest(void);
	void addAttribute(string, bool);
	bool hasAttribute(string);
	void setAttribute(string, bool);

	// These methods will deal with Items stored in this location
	void addItem(string item_name, Location* item);
	int getItemCount();
	void removeItem(string item_name);
	string listItems(string default_item_name="", string default_no_items="");
	bool hasItem(string);
	bool hasLocation(void);
	Location* getLocation(void);
	void setLocation(Location* location);
	string printNameAndDescription(void);
	void setShowItems(bool showItems);
	bool getShowItems();
	bool itemHasItem(string);
	~Location(void);
};
#endif
