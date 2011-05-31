			#include <iostream>
			#include <cstdlib>
			#include <string>
			#include <sstream>
			#include "Location.h"
			#include "Item.h"
			#include "Player.h"
			using namespace std;
			#define WELCOME_MESSAGE "Your name is Andy an amateur ghost hunter. You have arrived at your first job and find yourself in an overgrown garden, to the north is the old, abandoned mansion locals say to be haunted by a sadistic cultist who once inhabited it many years ago. This is the perfect place to hone your ghost-busting skills."
			#define QUIT_GAME "quit"
			string toLower(string text);
			int main(int argc, char **argv) {
			string username;
			string command;
			string verb;
			string noun;
			string prompt;
			int count;
			
Location* deadSpace = new Location("Dead space", "Dead space");
Location* diningRoom = new Location("The dining room", "You find yourself in an old dusty dining room, complete with ornate chandeliers. To the west is the Entrance hall where you just entered from.");
Location* entranceHall = new Location("The entrance hall", "You find yourself in a dimly lit expansive entrance hall illuminated only by the faint moonlight filtering through the dusty windows. You can only see darkness to the north and doorways to the east and west.");
Location* garden = new Location("The overgrown garden", "You are in the overgrown garden in front of the mansion.");
Location* masterBedroom = new Location("The master bedroom", "You are surrounded in darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you. To the east is the Entrance hall where you just entered from.");
Location* secretHall = new Location("The secret hall", "A long narrow hallway expands out in front of you, you see an opening at the end of the hall which you can feel a dark forbidding presence coming from it.");
Location* tortureRoom = new Location("The torture room", "You enter a cold stone room and instantly feel terrified. You see pentagrams carved into the stone floors which look to be covered in fresh blood. A hooded apparition materializes in front of you, wielding a menacing scythe. You can see your death is it's eyes.");

diningRoom->setWest(entranceHall);
entranceHall->setEast(diningRoom);
entranceHall->setWest(masterBedroom);
garden->setNorth(entranceHall);
masterBedroom->setEast(entranceHall);
secretHall->setNorth(tortureRoom);
secretHall->setSouth(entranceHall);
tortureRoom->setSouth(secretHall);
Location* compiler_inventory = new Location("Inventory", "Description of the inventory");Player* andy = new Player();andy->setLocation(garden);andy->setInventory(compiler_inventory);andy->setMaxItems(4);Item lamp("lamp", "A rusty old lamp but still looks like it might work.");
diningRoom->addItem("lamp", &lamp);
lamp.setLocation(diningRoom);
Item mirror("mirror", "You see your handsome, confident reflection in the mirror. This mirror could be useful...");
deadSpace->addItem("mirror", &mirror);
mirror.setLocation(deadSpace);
cout << WELCOME_MESSAGE << endl;prompt = "\n>>> ";cout << andy->getLocation()->printRoom() << endl;while (true) {   main_loop:   cout << prompt;   getline(cin, command);   istringstream word(command);   verb = "";   noun = "";   count = 0;   while (word) {      if (count > 2) {           cout << "I do not understand your command. Enter 2 words at most, a verb followed by a noun" << endl;           goto main_loop;      }      if (count == 0) {           word >> verb;      } else {           word >> noun;      }      count++;   }			if (command == QUIT_GAME) {
			quit_loop:
			string quit = "";
			cout << "Do you really want to quit?: [y]or[n] ";			getline(cin, quit);
			if (quit == "y") {
			cout << "Thanks for playing!" << endl;
			break;
			} else if (quit == "n") {
			goto main_loop;
			} else {
			goto quit_loop;
			}
			}			if (count == 2) {
if (verb == "east" || verb == "e"){
if (andy->getLocation()->hasEast()) {
andy->setLocation(andy->getLocation()->getEast()); 
cout << andy->getLocation()->getDescription() << endl;
cout << andy->getLocation()->listItems() << endl;
} else {cout << "You cannot go east";
}

goto main_loop;}
if (verb == "look"){
if (andy->getLocation() == tortureRoom) {
cout << "You look into the face of death and feel the scythe rip through your body. You flop over in agony and slowly die with the last thing you hear being the spectre cackling at your misfortune...";
break;
} else {cout << andy->getLocation()->getDescription() << endl;
cout << andy->getLocation()->listItems() << endl;
}

goto main_loop;}
if (verb == "north" || verb == "n" || verb == "nth"){
if (andy->getLocation()->hasNorth()) {
andy->setLocation(andy->getLocation()->getNorth()); 
cout << andy->getLocation()->getDescription() << endl;
cout << andy->getLocation()->listItems() << endl;
} else {cout << "You cannot go north";
}

goto main_loop;}
if (verb == "south" || verb == "s" || verb == "sth"){
if (andy->getLocation() == tortureRoom) {
cout << "As you turn to flee you hear a bone-chilling cackling behind you as the apparation swings his scythe. Before you can react you feel a sickening pain in your neck. You have been decapitated, your head rolls and your body crumples to the ground. You are dead...";
break;
cout << andy->getLocation()->listItems() << endl;
}
if (andy->getLocation()->hasSouth()) {
andy->setLocation(andy->getLocation()->getSouth()); 
cout << andy->getLocation()->getDescription() << endl;
cout << andy->getLocation()->listItems() << endl;
} else {cout << "You cannot go south";
}

goto main_loop;}
if (verb == "west" || verb == "w"){
if (andy->getLocation()->hasWest()) {
andy->setLocation(andy->getLocation()->getWest()); 
cout << andy->getLocation()->getDescription() << endl;
cout << andy->getLocation()->listItems() << endl;
} else {cout << "You cannot got west";
}

goto main_loop;}

			if ((verb == "i") || (verb == "inventory") || (verb == "invent")) {
			cout << andy->getInventory()->listItems() << endl;
			cout << andy->getNumberOfItems() << "/" << andy->getMaxItems() << endl;
			goto main_loop;
			}

			
cout << "I don't know how to " << verb << " here" << endl;
} else {
if ((toLower(noun) == toLower("lamp")) && (andy->getLocation()->hasItem("lamp") || andy->getInventory()->hasItem("lamp"))) {
if (verb == "drop") {
if (andy->getInventory()->hasItem(lamp.getName())) {
andy->getLocation()->addItem(lamp.getName(), &lamp);
cout << "You drop the ";
cout << lamp.getName() << endl;
} else {cout << "I don't have ";
cout << lamp.getName() << endl;
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look") {
cout << lamp.getDescription() << endl;
goto main_loop;}
if (verb == "light" || verb == "use" || verb == "turn-on" || verb == "turnon") {
if (lamp.getLocation() == andy->getInventory()) {
entranceHall->setDescription("With light eminating from the lamp you can now make out a doorway to the north as long with the doorways to the east and west.");entranceHall->setNorth(secretHall);
masterBedroom->setDescription("With the aid of the lamp you find yourself in an old creepy bedroom.");masterBedroom->addItem(mirror.getName(), &mirror);
cout << "You fiddle around with the old lamp and manage to turn it on.";
} else {cout << "You don't have that item.";
}
goto main_loop;}
if (verb == "off" || verb == "turnoff" || verb == "turn-off") {
if (lamp.getLocation() == andy->getInventory()) {
entranceHall->setDescription("You find yourself in a dimly lit expansive  entrance hall, only illuminated by the faint moonlight filtering through the dusty windows. You can only make out darkness to the north.");entranceHall->setNorth(NULL);
masterBedroom->setDescription("You are surrounded in darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you.");cout << "You switch off the old lamp.";
} else {cout << "You don't have that item.";
}
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (andy->getInventory()->hasItem(lamp.getName())) {
cout << "You already have the ";
cout << lamp.getName() << endl;
} else {if (andy->canCarry()) {
andy->getInventory()->addItem(lamp.getName(), &lamp);
cout << "You pickup the ";
cout << lamp.getName() << endl;
} else {cout << "You are carrying too much already.";
}
}
goto main_loop;}
cout << "Sorry you can not '" << verb << "' on '" << "lamp" << "'" << endl;
goto main_loop;
}if ((toLower(noun) == toLower("mirror")) && (andy->getLocation()->hasItem("mirror") || andy->getInventory()->hasItem("mirror"))) {
if (verb == "drop") {
if (andy->getInventory()->hasItem(mirror.getName())) {
andy->getLocation()->addItem(mirror.getName(), &mirror);
cout << "You drop the ";
cout << mirror.getName() << endl;
} else {cout << "I don't have ";
cout << mirror.getName() << endl;
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look") {
cout << mirror.getDescription() << endl;
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (andy->getInventory()->hasItem(mirror.getName())) {
cout << "You already have the ";
cout << mirror.getName() << endl;
} else {if (andy->canCarry()) {
andy->getInventory()->addItem(mirror.getName(), &mirror);
cout << "You pickup the ";
cout << mirror.getName() << endl;
} else {cout << "You are carrying too much already.";
}
}
goto main_loop;}
if (verb == "use" || verb == "lookat" || verb == "look-at") {
if (andy->getLocation() == tortureRoom) {
cout << "You pull out out the mirror, the ghost upon seeing it's horrific reflection flees in terror. Congratulations you have busted your first ghost!";
break;
} else {cout << "You admire yourself in the mirror.";
}
goto main_loop;}
cout << "Sorry you can not '" << verb << "' on '" << "mirror" << "'" << endl;
goto main_loop;
}cout << "I can't find a " << noun << " here" << endl;
}
}
}