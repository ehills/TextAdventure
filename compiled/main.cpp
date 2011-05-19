#include <iostream>
#include <cstdlib>
#include <string>
#include "Location.h"
#include "Player.h"
using namespace std;
#define WELCOME_MESSAGE "Hello and welcome to zork, please give us a good grade"

int main(int argc, char **argv) {
   string user_response = "";
   string username ="";
   string prompt ="";
   string command="";
   string verb="";
   string noun="";

   Location* inventory = new Location();
   Location* startLocation = new Location();
   Player* player = new Player();

   /* Print welcome message and get users name */
   cout << WELCOME_MESSAGE << endl;
   cout << "Please enter your hero's name: ";
   cin >> username;
   player->setName(username);
   prompt = player->getName() + ": ";
   cout << "Thank you " << player->getName() <<
      ". Your quest will now begin.\n";

    while (true) {
      cout << prompt;
      cout.flush();
      cin >> command;
      verb = command;
      cin >> command;
      noun = command;
  
      if (verb.compare(/*verbs.hasVerb(verb))*/"verb")) { // if verb is in list of verbs
         if (player->getLocation().hasItem(noun)) {
            // player->getLocation().getItem(noun)->doVerb();
         } else {
            cout << "Sorry you do not have this item" << endl;
         }
      } else {
         cout << "Sorry I do not understand this command" << endl;
      }
      cin.ignore();
   
   
       }

   return 0;
}
      

      
   
