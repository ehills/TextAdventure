#include <cstdlib>
#include <iostream>

using namespace std;

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
