/**
 * Class: Player
 * File: Player.cpp
 * Date: May 16 2011
 * Description: Contains the Player object and methods needed to access it.
 **/
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

/* Gets player name */
string Player::getName(void) {return name;}

/* Sets player name */
void Player::setName(string name) {this->name = name;}

/* Gets player description */
string Player::getDescription(void) {return description;}

/* Sets player description */
void Player::setDescription(string description) {
   this->description = description;
}

/* Returns the number of items currently held by the player */
int Player::getNumberOfItems(void) {return current_number_of_items;}

/* Sets the number of items that the player currently has */
void Player::setNumberOfItems(int number_of_items) {
   current_number_of_items = number_of_items ;
}

/* Returns the max number of items the player can hold */
int Player::getMaxItems(void) {return max_items;}

/* Sets the number of max items the player can hold */
void Player::setMaxItems(int max_items) {this->max_items = max_items;}

/* Returns the players starting location */
Location Player::getLocation(void) {return current_location;}

/* Sets the players starting location */
void Player::setLocation(Location location) {
   this->current_location = location;
}

/* Returns the players inventory location */
Location Player::getInventory(void) {return inventory;}

/* Sets the players inventory location */
void Player::setInventory(Location inventory) {this->inventory = inventory;}
