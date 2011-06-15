#include "Player.h"

/* Player Class will have a description, name, maximum number of items,
 * current number of items held, the current location and a location which
 * will store the inventory.
 */

Player::Player(){}

string Player::getName(void) {return name;}

void Player::setName(string name) {this->name = name;}

string Player::getDescription(void) {return description;}

void Player::setDescription(string description) {this->description = description;}

int Player::getNumberOfItems(void) {return inventory->getItemCount();}

bool Player::canCarry(void) {return this->getNumberOfItems() < max_items;}

int Player::getMaxItems(void) {return max_items;}

void Player::setMaxItems(int max_items) {this->max_items = max_items;}

Location* Player::getLocation(void) {return current_location;}

void Player::setLocation(Location* location) {this->current_location = location;}

Location* Player::getInventory(void) {return inventory;}

void Player::setInventory(Location* inventory) {this->inventory = inventory;}
