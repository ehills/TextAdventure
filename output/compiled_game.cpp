#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Location.h"
#include "Item.h"
#include "Player.h"
using namespace std;
#define WELCOME_MESSAGE "You find yourself in an overgrown garden, to the north is an old, desolate mansion. Locals say it to be haunted by a sadistic cultist who once inhabited it many years ago. This is the perfect place to hone your ghost-busting skills"
#define QUIT_GAME "quit"
int main(int argc, char **argv) {
    string username;
    string command;
    string verb;
    string noun;
    string prompt;
    int count;
    
Location diningRoom("The dining room", "An old dusty dinning room, complete with ornate chandeliers. You notice an old lamp resting on the long dinning room table. To the west is the Entrance hall where you just entered from");
Location entranceHall("The entrance hall", "You find yourself in a dimly lit expansive entrance hall illuminated only by the faint moonlight filtering through the dusty windows. You can only see darkness to the north and doorways to the east and west");
Location garden("The overgrown garden", "An overgrown garden in front of an old, spooky mansion");
Location masterBedroom("The master bedroom", "You are surrounded in darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you. To the east is the Entrance hall where you just entered from");
Location secretHall("The secret hall", "A long narrow hallway expands out in front of you, you see an opening at the end of the hall which you can feel a dark forbidding presence coming from. You notice openings to the south and north");
Location tortureRoom("The torture room", "You enter a cold stone room and instantly feel terrified. You see pentagrams carved into the stone floors which look to be covered in fresh blood. A hooded apparition materializes in front of you, wielding a menacing scythe. You can see your death is it's eyes");

diningRoom.setWest(&entranceHall);
entranceHall.setEast(&diningRoom);
entranceHall.setWest(&masterBedroom);
garden.setNorth(&entranceHall);
masterBedroom.setEast(&entranceHall);
secretHall.setNorth(&tortureRoom);
secretHall.setSouth(&entranceHall);
tortureRoom.setSouth(&secretHall);
Location compiler_inventory("Inventory", "Description of the inventory");Player* andy = new Player();andy->setLocation(&garden);andy->setInventory(&compiler_inventory);andy->setMaxItems(4);Item lamp("lamp", "A rusty old lamp but looks like it still works");
diningRoom.addItem("lamp", &lamp);
lamp.setLocation(&diningRoom);
Item mirror("mirror", "You see your handsome, confident reflection in the mirror. This mirror could be useful..");
masterBedroom.addItem("mirror", &mirror);
mirror.setLocation(&masterBedroom);
cout << WELCOME_MESSAGE << endl;prompt = "\n>>> ";cout << andy->getLocation()->printRoom() << endl;while (true) {   main_loop:   cout << prompt;   getline(cin, command);   istringstream word(command);   verb = "";   noun = "";   count = 0;   while (word) {      if (count > 2) {           cout << "I do not understand your command. Enter 2 words at most, a verb followed by a noun" << endl;           goto main_loop;      }      if (count == 0) {           word >> verb;      } else {           word >> noun;      }      count++;   }    if (command == QUIT_GAME) {
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
                cout << andy->getInventory()->listItems() << endl;
                cout << andy->getNumberOfItems() << "/" << andy->getMaxItems() << endl;
                goto main_loop;
        }

        if(verb=="north") {
            if (!andy->getLocation()->hasNorth()) {
                cout << "Sorry you can not go North" << endl;
                goto main_loop;
            } else {
                andy->setLocation(andy->getLocation()->getNorth());
                cout << andy->getLocation()->printRoom() << endl;
                 goto main_loop;
            }
        }

        if(verb=="south") {
            if (!andy->getLocation()->hasSouth()) {
                cout << "Sorry you can not go South" << endl;
                goto main_loop;
            } else {
                andy->setLocation(andy->getLocation()->getSouth());
                cout << andy->getLocation()->printRoom() << endl;
                goto main_loop;
            }
        }

        if(verb=="west") {
            if (!andy->getLocation()->hasWest()) {
                cout << "Sorry you can not go West" << endl;
                goto main_loop;
            } else {
                andy->setLocation(andy->getLocation()->getWest());
                cout << andy->getLocation()->printRoom() << endl;
                goto main_loop;
            }
        }
        if(verb=="east") {
            if (!andy->getLocation()->hasEast()) {
                cout << "Sorry you can not go East" << endl;
                goto main_loop;
            } else {
                andy->setLocation(andy->getLocation()->getEast());
                cout << andy->getLocation()->printRoom() << endl;
                goto main_loop;
            }
        }if (verb=="look"){
cout << andy->getLocation()->getDescription() << endl;
cout << andy->getLocation()->listItemsDescription() << endl;

goto main_loop;}
cout << "I don't know how to " << verb << " here" << endl;
} else {
if (andy->getLocation()->hasItem("lamp") || andy->getInventory()->hasItem("lamp")) {
if (verb == "drop") {
if (andy->getInventory()->hasItem(lamp.getName())) {
andy->getLocation()->addItem(lamp.getName(), &lamp);
} else {cout << "I don't have ";
cout << lamp.getDescription() << endl;
cout << ".";
}
goto main_loop;}
if (verb == "examine") {
cout << lamp.getName() << endl;
goto main_loop;}
if (verb == "light") {
entranceHall.setDescription("You can now make out a door to the north");entranceHall.setNorth(&secretHall);
masterBedroom.setDescription("You can now make out a mirror in the far corner of the room");cout << "You fiddle around with the old lamp and manage to get it working";
} else {cout << "You don't have that item";
}
goto main_loop;}
if (verb == "off") {
entranceHall.setDescription("You find yourself in a dimly lit expansive  entrance hall, only illuminated by the faint moonlight filtering through the dusty windows. You can only make out darkness to the north");entranceHall.setNorth(NULL);
masterBedroom.setDescription("You are surrounded in darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you");cout << "You switch off the old lamp";
} else {cout << "You don't have that item";
}
goto main_loop;}
if (verb == "pickup") {
if (andy->canCarry()) {
andy->getInventory()->addItem(lamp.getName(), &lamp);
} else {cout << "You are carrying too much already";
}
goto main_loop;}
cout << "Sorry you can not " << verb << "on" << "lamp" << endl;
goto main_loop;
}if (andy->getLocation()->hasItem("mirror") || andy->getInventory()->hasItem("mirror")) {
if (verb == "drop") {
if (andy->getInventory()->hasItem(mirror.getName())) {
andy->getLocation()->addItem(mirror.getName(), &mirror);
} else {cout << "I don't have ";
cout << mirror.getDescription() << endl;
cout << ".";
}
goto main_loop;}
if (verb == "examine") {
cout << mirror.getName() << endl;
goto main_loop;}
if (verb == "pickup") {
if (andy->canCarry()) {
andy->getInventory()->addItem(mirror.getName(), &mirror);
} else {cout << "You are carrying too much already";
}
goto main_loop;}
if (verb == "use") {
if (andy->getLocation() == &tortureRoom) {
cout << "You pull out out the mirror, the ghost upon seeing it's horrific reflection fleas in terror. Congratulations you have busted your first ghost!";
break;
} else {cout << "You admire yourself in the mirror.";
}
goto main_loop;}
cout << "Sorry you can not " << verb << "on" << "mirror" << endl;
goto main_loop;
}cout << "I can't find a " << noun << " here" << endl;
}
}
}