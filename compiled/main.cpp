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
	int count;

	Location* currentLocation = new Location();
	Location inventory;
	Location hospitalFloor;
	Location startLocation;

	startLocation.setName("start room");
	startLocation.setDescription("You find yourself in an empty room...");
	hospitalFloor.setDescription("You find yourself in a brightly lit room...");
	startLocation.setNorth(&hospitalFloor);
	hospitalFloor.setSouth(&startLocation);
	currentLocation = &startLocation;

	/* Print welcome message and get users name */
	Player* player = new Player();
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
		//cout << "current room: " << currentLocation->getName() << endl;
		cout << prompt;
		getline(cin, command);

		// Get verb and noun from user's input
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
			cout << "Do you really want to quit?: [y]or[n]" << endl << ">>> ";
			cin >> quit;
			cin.ignore();
			if (quit == "y") {
				cout << "Thanks for playing!" << endl;
				break;
			}
			else if (quit == "n") {
				goto main_loop;
			} else {
				goto quit_loop;
			}
		}

		// Look in inventory
		if(command == "i" || command == "inventory" || command == "invent" ) {

			cout << player->getInventory().listItems();
			cout <<  player->getNumberOfItems() << "/" << player->getMaxItems()<< endl;
			goto main_loop;
		}

		// Describe location and items in it
		if(verb == "look" and noun == ""|| verb == "describe" and noun == "") {
			currentLocation->printRoom();
			cout << endl;
			goto main_loop;
		}

		// Move north, south, west or east
		if(verb=="north" and noun == "") {
			if (!currentLocation->hasNorth()) {
				cout << "Sorry you can not go North" << endl;
				goto main_loop;
			} else {
				currentLocation = currentLocation->getNorth();
				cout << currentLocation->getDescription() << endl;
				goto main_loop;
			}
		}

		if(verb=="south" and noun == "") {
			if (!currentLocation->hasSouth()) {
				cout << "Sorry you can not go South" << endl;
				goto main_loop;
			} else {
				currentLocation = currentLocation->getSouth();
				cout << currentLocation->getDescription() << endl;
				goto main_loop;
			}
		}

		if(verb=="west" and noun == "") {
			if (!currentLocation->hasWest()) {
				cout << "Sorry you can not go West" << endl;
				goto main_loop;
			} else {
				currentLocation = currentLocation->getWest();
				cout << currentLocation->getDescription() << endl;
				goto main_loop;
			}
		}

		if(verb=="east" and noun == "") {
			if (!currentLocation->hasEast()) {
				cout << "Sorry you can not go East" << endl;
				goto main_loop;
			} else {
				currentLocation = currentLocation->getEast();
				cout << currentLocation->getDescription() << endl;
				goto main_loop;
			}
		}

		if (verb.compare("verb") == 0) { // if verb is in list of verbs
			if (noun.compare("noun") == 0 ) {
				// noun.doVerb
			} else {
				cout << "Sorry you do not have this item" << endl;
			}
		} else {
			cout << "Sorry I do not understand this command" << endl;
		}
	}
	return 0;
}







