#include <iostream>
#include <cstdlib>
#include <string>
#include "Location.h"
#include "Player.h"
using namespace std;
#define WELCOME_MESSAGE "Placeholder\n"
#define START_L_POINT "Placeholder"
#define START_L_DESCR "Placeholder"
#define PLAYER_DESCR "Placeholder"


int main(int argc, char **argv) {
   string user_response = "";
   string user ="";
   Location startLocation = new Location(START_L_POINT, START_L_DESCR, items);
   Player player = new Player(PLAYER_DESCR, 5, 0, startLocation);

   /* Print welcome message and get users name */
   cout << WELCOME_MESSAGE;
   cout << "Please enter your hero's name: ";
   cin >> user;
   cin.ignore();
   cout << "Thank you " << user << ". Your quest will now begin." << endl;

   while (true) {
      
   }

   return 0;
}
      

      
   
