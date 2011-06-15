/* Description: Contains the Player object and methods needed to access it. */

#include <sstream>
#include "Player.h"

/* Player Class will have a description and a weight limit associated with it.*/

/* Constructor */
Player::Player(){}

Player::Player(string name, string description , int max_items,
		int current_number_of_items, Location current_location,
		Location inventory) {
	this->name = name;
	this->description = description;
	this->max_items = max_items;
	this->current_number_of_items = current_number_of_items;
	this->current_location = current_location;
	this->inventory = inventory;
}

Player::~Player(){

}

string Player::getName(void) {return name;}

void Player::setName(string name) {this->name = name;}


string Player::getVariableName(void) {return variable_name;}

void Player::setVariableName(string variable_name) {this->variable_name = variable_name;}

string Player::getDescription(void) {return description;}

void Player::setDescription(string description) {
	this->description = description;
}

int Player::getNumberOfItems(void) {return current_number_of_items;}

void Player::setNumberOfItems(int number_of_items) {
	current_number_of_items = number_of_items ;
}

int Player::getMaxItems(void) {return max_items;}
string Player::getMaxItemsString(void) {
	stringstream s;
	s << max_items;
	return s.str();
}

void Player::setMaxItems(int max_items) {this->max_items = max_items;}

Location Player::getLocation(void) {return current_location;}

void Player::setLocation(Location location) {
	this->current_location = location;
}

Location Player::getInventory(void) {return inventory;}

void Player::setInventory(Location inventory) {this->inventory = inventory;}
