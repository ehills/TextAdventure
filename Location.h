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

using namespace std;

/* Location class will store all information relevant to a particular location*/
class Location {
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
    // Object Deletion
    ~Location(void);
private:
    string name;
    string variable_name;
    string description;
    Location* south;
    Location* north;
    Location* east;
    Location* west;
};

#endif
