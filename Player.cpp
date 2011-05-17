/**
 * Class: Player
 * File: Player.cpp
 * Date: May 16 2011
 * Description: Contains the Player object and methods needed to access it.
 **/
#include <cstdlib>
#include <iostream>
using namespace std;

/* Player Class will have a description and a weight limit associated with it.*/
class Player {
   string description;
   int max_items;
   int current_number_of_items;
public:
   Player(string, int, int);
   ~Player();
   string getDescription(void) {return description;}
   void setDescription(string description) {this->description = description;}
   int getNumberOfItems(void) {return current_number_of_items;}
   void setNumberOfItems(int number_of_items) {
      current_number_of_items = number_of_items ;
   }
   int getMaxItems(void) {return max_items;}
   void setMaxItems(int max_items) {this->max_items = max_items;}
};

Player::Player(string description, int max_items, int current_number_of_items) {
   this->description = description;
   this->max_items = max_items;
   this->current_number_of_items = current_number_of_items;
}
