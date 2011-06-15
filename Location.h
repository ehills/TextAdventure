#ifndef LOCATION_H_
#define	LOCATION_H_
#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;
class Item;

/* Location class will store all information relevant to a particular location*/
class Location {
	string name;
	string variable_name; // Used as a locations unique identifier.
	string description;
	Location* south;
	Location* north;
	Location* east;
	Location* west;
public:
	Location(string, string, string);
	Location();

	// Details
	string getName(void);
	void setName(string name);
	string getVariableName(void);
	void setVariableName(string variable_name);
	string getDescription(void);
	void setDescription(string description);

	// Directions
	Location* getNorth(void);
	Location* getSouth(void);
	Location* getEast(void);
	Location* getWest(void);
	bool hasNorth(void);
	bool hasSouth(void);
	bool hasEast(void);
	bool hasWest(void);
	void setNorth(Location* location);
	void setSouth(Location* location);
	void setEast(Location* location);
	void setWest(Location* location);

	~Location(void);
};

#endif
