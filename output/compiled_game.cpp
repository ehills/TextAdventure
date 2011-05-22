#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Location.h"
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

    Location inventory("Inventory", "Description of the inventory");
    Player* player = new Player();
    player->setLocation(&livingRoom);    player->setInventory(inventory);
    player->setMaxItems(8);
    cout << WELCOME_MESSAGE << endl;

    prompt = ">>> ";
    
    cout << player->getLocation()->getDescription() << endl;
    while (true) {
        main_loop:
        cout << prompt;
        getline(cin, command);
        istringstream word(command);
        verb = "";
        noun = "";
        count = 0;
        while (word) {
            if (count > 2) {
            cout << "I do not understand your command. Enter 2 words at most, a verb followed by a noun" << endl;
            goto main_loop;
            }
            if (count == 0) {
            word >> verb;
            } else {
            word >> noun;
            }
            count++;
        }
    if (command == QUIT_GAME) {
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
        if(verb=="north") {
            if (!player->getLocation()->hasNorth()) {
                cout << "Sorry you can not go North" << endl;
                goto main_loop;
            } else {
                player->setLocation(player->getLocation()->getNorth());
                cout << player->getLocation()->getDescription() << endl;
                goto main_loop;
            }
        }

        if(verb=="south") {
            if (!player->getLocation()->hasSouth()) {
                cout << "Sorry you can not go South" << endl;
                goto main_loop;
            } else {
                player->setLocation(player->getLocation()->getSouth());
                cout << player->getLocation()->getDescription() << endl;
                goto main_loop;
            }
        }

        if(verb=="west") {
            if (!player->getLocation()->hasWest()) {
                cout << "Sorry you can not go West" << endl;
                goto main_loop;            } else {                player->setLocation(player->getLocation()->getWest());
                cout << player->getLocation()->getDescription() << endl;
                goto main_loop;            }
        }
        if(verb=="east") {
            if (!player->getLocation()->hasEast()) {
                cout << "Sorry you can not go East" << endl;
                goto main_loop;
            } else {
                 player->setLocation(player->getLocation()->getEast());
                cout << player->getLocation()->getDescription() << endl;
                goto main_loop;
            }
        }
    }
}
}
