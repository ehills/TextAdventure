#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Location.h"
#include "Item.h"
#include "Player.h"
using namespace std;
#define WELCOME_MESSAGE "Ed Is a Fucking homo"
#define QUIT_GAME "quit"
int main(int argc, char **argv) {
    string username;
    string command;
    string verb;
    string noun;
    string prompt;
    int count;
    
Location kitchen("Kitchen", "A kitchen is a room or part of a room used for cooking and food preparation. In the West, a modern residential kitchen is typically equipped with a stove, a sink with hot and cold running water, a refrigerator and kitchen cabinets arranged according to a modular design. Many households have a microwave oven, a dishwasher and other electric appliances. The main function of a kitchen is cooking or preparing food but it may also be used for dining and entertaining.");
Location livingRoom("The Living Room", "The Living Room");

kitchen.setNorth(&livingRoom);
livingRoom.setSouth(&kitchen);
Location inventory("Inventory", "Description of the inventory");Player* mother = new Player();mother->setLocation(&livingRoom);mother->setInventory(&inventory);mother->setMaxItems(8);Item television("Television", "A small television placed in the corner of the kitchen. It looks broken");
// television.setLocation(&kitchen);
kitchen.addItem("Television", television);
cout << WELCOME_MESSAGE << endl;prompt = ">>> ";cout << mother->getLocation()->getDescription() << endl;while (true) {   main_loop:   cout << prompt;   getline(cin, command);   istringstream word(command);   verb = "";   noun = "";   count = 0;   while (word) {      if (count > 2) {           cout << "I do not understand your command. Enter 2 words at most, a verb followed by a noun" << endl;           goto main_loop;      }      if (count == 0) {           word >> verb;      } else {           word >> noun;      }      count++;   }    if (command == QUIT_GAME) {
        quit_loop:
        string quit = "";
        cout << "Do you really want to quit?: [y]or[n] ";        cout.flush();
	cin >> quit;
	cin.ignore();
	if (quit == "y") {
        	cout << "Thanks for playing!" << endl;
                break;
	} else if (quit == "n") {
                goto main_loop;
	} else {
		goto quit_loop;
	}
    }    if (count == 2) {

        if ((verb == "i") || (verb == "inventory") || (verb == "invent")) {
                cout << mother->getInventory()->listItems();
                cout << mother->getNumberOfItems() << "/" << mother->getMaxItems() << endl;
                goto main_loop;
        }

        if(verb=="north") {
            if (!mother->getLocation()->hasNorth()) {
                cout << "Sorry you can not go North" << endl;
                goto main_loop;
            } else {
                mother->setLocation(mother->getLocation()->getNorth());
                cout << mother->getLocation()->getDescription() << endl;
                goto main_loop;
            }
        }

        if(verb=="south") {
            if (!mother->getLocation()->hasSouth()) {
                cout << "Sorry you can not go South" << endl;
                goto main_loop;
            } else {
                mother->setLocation(mother->getLocation()->getSouth());
                cout << mother->getLocation()->getDescription() << endl;
                goto main_loop;
            }
        }

        if(verb=="west") {
            if (!mother->getLocation()->hasWest()) {
                cout << "Sorry you can not go West" << endl;
                goto main_loop;
            } else {
                mother->setLocation(mother->getLocation()->getWest());
                cout << mother->getLocation()->getDescription() << endl;
                goto main_loop;
            }
        }
        if(verb=="east") {
            if (!mother->getLocation()->hasEast()) {
                cout << "Sorry you can not go East" << endl;
                goto main_loop;
            } else {
                mother->setLocation(mother->getLocation()->getEast());
                cout << mother->getLocation()->getDescription() << endl;
                goto main_loop;
            }
        }if (verb=="look"){
cout << mother->getLocation()->getDescription() << endl;
cout << mother->getLocation()->listItems() << endl;

goto main_loop;}
cout << "I don't know how to " << verb << " here" << endl;
} else {
if (mother->getLocation()->hasItem("Television") || mother->getInventory()->hasItem("Television")) {
cerr << "hit object in room" << endl;
if (verb == "drop") {
cerr << "DOING drop" << endl;
mother->getLocation()->addItem(television.getName(), television);
cout << "I don't have";
cout << television.getName();
cout << ".";
goto main_loop;}
if (verb == "examine") {
cerr << "DOING examine" << endl;
cout << television.getDescription();
goto main_loop;}
if (verb == "take") {
cerr << "DOING take" << endl;
mother->getInventory()->addItem(television.getName(), television);
cout << "You are carrying to much already";
goto main_loop;}
cout << "Sorry you can not " << verb << "on" << "Television" << endl;
goto main_loop;
}cout << "I can't find a " << noun << " here" << endl;
}
}
}
