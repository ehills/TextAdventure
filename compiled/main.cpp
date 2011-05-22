#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Location.h"
#include "Player.h"
using namespace std;
#define WELCOME_MESSAGE "Hello and welcome to zork, please give us a good grade"
#define QUIT_GAME "quit"

int main(int argc, char **argv) {
    string username;
    string command;
    string verb;
    string noun;
    string prompt;
    bool globalVerb = false;
    int count;

    Player* player = new Player();
    Location* currentLocation = new Location();
    Location inventory;
    //currentLocation = &player->getLocation();

    Location hospitalFloor;
    Location startLocation;
    Item sword("Long sword", "A dirty long sword");
    Item mace("Spikey mace", "A brutal looking mace");

    startLocation.setName("start room");
    startLocation.setDescription("You find yourself in an empty room...");
    hospitalFloor.setDescription("You find yourself in a brightly lit room...");
    startLocation.setNorth(&hospitalFloor);
    hospitalFloor.setSouth(&startLocation);
    currentLocation = &startLocation;
    currentLocation->addItem("sword", sword);
    currentLocation->addItem("mace", mace);

    /* Print welcome message and get users name */
    player->setInventory(inventory);
    player->setMaxItems(8);
    player->setNumberOfItems(+1);
    cout << WELCOME_MESSAGE << endl;
    cout << "Please enter your hero's name: ";
    cin >> username;
    cin.ignore();
    player->setName(username);
    prompt = player->getName() + ": ";

    cout << "Thank you " << player->getName() <<
            ". Your quest will now begin.\n";

    cout << currentLocation->getDescription() << endl;

    while (command != QUIT_GAME) {
main_loop:
        // Get verb and noun from user's input
        cout << prompt;
        getline(cin, command);
        istringstream word(command);
        verb = "";
        noun = "";
        count = 0;
        while (word) {
            // Error check for more than 2 words
            if (count > 2) {
                cout << "I do not understand your command. Enter 2 words at most, a verb followed by a noun" << endl;
                goto main_loop;
            }
            // Get the verb
            if (count == 0) {
                word >> verb;
                // Get the noun
            } else {
                word >> noun;
            }
            count++;
        }

        // Quit game...? yes or no...?
        if (command == QUIT_GAME) {
quit_loop:
            string quit = "";
            cout << "Do you really want to quit?: [y]or[n]" << endl << prompt;
            getline(cin, quit);
            if (quit == "y" or quit == "yes") {
                cout << "Thanks for playing!" << endl;
                break;
            } else if (quit == "n" or quit == "no") {
                goto main_loop;
            } else {
                cout << "Please enter [y]or[n]:" << endl;
                goto quit_loop;
            }
        }

        // Look in inventory
        if (count == 2) {
            if ((verb == "i" and noun == "") or (verb == "inventory" and noun == "") or (verb == "invent" and noun == "")) {
                cout << player->getInventory().listItems();
                cout << player->getNumberOfItems() << "/" << player->getMaxItems() << endl;
                goto main_loop;
            }

            // Move north, south, west or east
            if (verb == "north" and noun == "") {
                if (!currentLocation->hasNorth()) {
                    cout << "Sorry you can not go North" << endl;
                    goto main_loop;
                } else {
                    currentLocation = currentLocation->getNorth();
                    cout << currentLocation->getDescription() << endl;
                    goto main_loop;
                }
            }

            if (verb == "south" and noun == "") {
                if (!currentLocation->hasSouth()) {
                    cout << "Sorry you can not go South" << endl;
                    goto main_loop;
                } else {
                    currentLocation = currentLocation->getSouth();
                    cout << currentLocation->getDescription() << endl;
                    goto main_loop;
                }
            }

            if (verb == "west" and noun == "") {
                if (!currentLocation->hasWest()) {
                    cout << "Sorry you can not go West" << endl;
                    goto main_loop;
                } else {
                    currentLocation = currentLocation->getWest();
                    cout << currentLocation->getDescription() << endl;
                    goto main_loop;
                }
            }

            if (verb == "east" and noun == "") {
                if (!currentLocation->hasEast()) {
                    cout << "Sorry you can not go East" << endl;
                    goto main_loop;
                } else {
                    currentLocation = currentLocation->getEast();
                    cout << currentLocation->getDescription() << endl;
                    goto main_loop;
                }
            }

            
            
            // If item is in the current location
        } else {
            if (currentLocation->hasItem(noun)) {
                currentLocation->getItem(noun).doVerb(verb);
                // If item is in player's inventory
            } else if (player->getInventory().hasItem(noun)) {
                player->getInventory().getItem(noun).doVerb(verb);
                // If verb is a global verb
            } else {
                cout << "Sorry I can not find a " << noun << endl;
            }
        }
    }
    return 0;

}






