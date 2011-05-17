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
   int weight_limit;
public:
   Player(string, int);
   ~Player();
   string getDescription(void) {return description;}
   void setDescription(string description) {this->description = description;}
   int getWeightLimit(void) {return weight_limit;}
   void setWeightLimit(int limit) {weight_limit = limit;}
};

Player::Player(string description, int weight_limit) {
   this->description = description;
   this->weight_limit = weight_limit;
}
