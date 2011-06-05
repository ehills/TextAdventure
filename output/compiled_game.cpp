#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Location.h"
#include "Item.h"
#include "Player.h"
using namespace std;
#define GAME_NAME "*****Mother(Example Game)*****"
#define CREDITS "By randoms"
#define WELCOME_MESSAGE "You have just returned from the supermarket. You put the key into the keyhole, turn it and open the door. As you pickup your groceries and enter the house, you hear a baby crying. Oh, no! You forgot about your baby and left it at home while you went out shopping. To make things worse, you can't reemember where in the house you put it. You are a terrible mother! Now there is nonly one thing on your mind... Where is the baby crying?"
#define QUIT_GAME "quit"
string toLower(string text);
int main(int argc, char **argv) {
string username;
string command;
string verb;
string noun;
string prompt;
int count;

Player* mother = new Player();

Location* bathroom = new Location("Bathroom", "This room is empty. Maybe you should wait for me to finish the game first!");
Location* bedroom = new Location("Bedroom", "You wake up from this terrible nightmare! To be continued...");
Location* dead_space = new Location("Dead Space", "The game dump");
Location* hallway = new Location("Hallway", "This square of land connects four rooms together. To the north is the kitchen. To the south is the bathroom. To the west is the toilet. To the east is the living room.");
Location* inventory = new Location("Inventory", "");
Location* kitchen = new Location("Kitchen", "This room is empty. Maybe you should wait for me to finish the game first!");
Location* living_room = new Location("Living room", "A room with a small television and a couch. There is not much else in here. It's hard to afford nice things with a young child. There is a jammed door to the north that leads to the bedroom and a door to the west that leads to a hallway. The front door to the south leads you outside, but I wouldn't leave the baby unattended again...");
Location* toilet_room = new Location("Toilet Room", "This is where the toilet is. You can exit to the east when you've finished business.");

mother->setLocation(living_room);mother->setInventory(inventory);mother->setMaxItems(4);
bathroom->setNorth(hallway);
bedroom->setSouth(living_room);
hallway->setNorth(kitchen);
hallway->setSouth(bathroom);
hallway->setEast(living_room);
hallway->setWest(toilet_room);
kitchen->setSouth(hallway);
living_room->setWest(hallway);
toilet_room->setEast(hallway);

Item bedroom_door("Bedroom_Door", "This is the bedroom door. There's no lock on it but the door knob is stuck. What a piece of crap");
living_room->addItem("Bedroom_Door", &bedroom_door);
bedroom_door.setLocation(living_room);
Item brick("brick", "A wet brick. You could try licking it if you're thirsty.");
dead_space->addItem("brick", &brick);
brick.setLocation(dead_space);
Item couch("Couch", "An old second hand couch. Beggars can't be choosers.");
living_room->addItem("Couch", &couch);
couch.setLocation(living_room);
Item television("television", "An ancient CRT TV from the early 2000s Definitely not HD ready.");
living_room->addItem("television", &television);
television.setLocation(living_room);
Item toilet("Toilet", "You know what this is for.");
toilet_room->addItem("Toilet", &toilet);
toilet.setLocation(toilet_room);
cout << endl << "			" << GAME_NAME << endl;
cout << CREDITS << endl << endl;
cout << WELCOME_MESSAGE << endl << endl;
prompt = "\n>>> ";
cout << mother->getLocation()->printNameAndDescription() << endl;
cout << mother->getLocation()->listItems() << endl;
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
      } else {           word >> noun;
      }
      count++;
   }
if (verb != "" && noun == "" ) {
if (verb == "east" || verb == "e"){
if (mother->getLocation()->hasEast()) {
mother->setLocation(mother->getLocation()->getEast()); 
cout << mother->getLocation()->printNameAndDescription() << endl;
cout << mother->getLocation()->listItems() << endl;
} else {
cout << "You cannot go east.";
}

goto main_loop;}
if (verb == "i" || verb == "inventory" || verb == "invent"){
cout << "Inventory " << mother->getInventory()->listItems() << " ";
cout << mother->getNumberOfItems() << "/" << mother->getMaxItems() << endl;

goto main_loop;}
if (verb == "look"){
cout << mother->getLocation()->printNameAndDescription() << endl;
cout << mother->getLocation()->listItems() << endl;

goto main_loop;}
if (verb == "north" || verb == "n" || verb == "nth"){
if (mother->getLocation()->hasNorth()) {
mother->setLocation(mother->getLocation()->getNorth()); 
cout << mother->getLocation()->printNameAndDescription() << endl;
cout << mother->getLocation()->listItems() << endl;
} else {
cout << "You cannot go north.";
}

goto main_loop;}
if (verb == "quit" || verb == "q"){
cout << "Bye bye thanks for playing!!!";
break;

goto main_loop;}
if (verb == "south" || verb == "s" || verb == "sth"){
if (mother->getLocation()->hasSouth()) {
mother->setLocation(mother->getLocation()->getSouth()); 
cout << mother->getLocation()->printNameAndDescription() << endl;
cout << mother->getLocation()->listItems() << endl;
} else {
cout << "You cannot go south.";
}

goto main_loop;}
if (verb == "west" || verb == "w"){
if (mother->getLocation()->hasWest()) {
mother->setLocation(mother->getLocation()->getWest()); 
cout << mother->getLocation()->printNameAndDescription() << endl;
cout << mother->getLocation()->listItems() << endl;
} else {
cout << "You cannot go west.";
}

goto main_loop;}
cout << "I don't know how to " << verb << " here";
} else if (verb != "" && noun != "" ){
if ((toLower(noun) == toLower("Bedroom_Door")) && (mother->getLocation()->hasItem("Bedroom_Door") || mother->getInventory()->hasItem("Bedroom_Door"))) {
if (verb == "pickup") {
if (mother->canCarry()) {
bedroom->addItem(bedroom_door.getName(), &bedroom_door);
} else {
cout << "You are carrying too much already";
}
goto main_loop;}if (verb == "open") {
cout << "You turn the door handle but unfortunately the door doesn't open.";
goto main_loop;}if (verb == "examine") {
cout << bedroom->getName();
goto main_loop;}if (verb == "drop") {
if (bedroom->hasItem(bedroom_door.getName())) {
bedroom->addItem(bedroom_door.getName(), &bedroom_door);
} else {
cout << "I don't have ";
cout << bedroom->getName();
cout << ".";
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "Bedroom_Door" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("brick")) && (mother->getLocation()->hasItem("brick") || mother->getInventory()->hasItem("brick"))) {
if (verb == "throw") {
if (mother->getLocation() == living_room) {
cout << "You throw the brick at the door. It opens up.";
dead_space->addItem(brick.getName(), &brick);
living_room->setNorth(bedroom);
bedroom->setDescription("A room with a small television and a couch. There is not much else in here. It's hard to afford nice things with a young child. There is an open door to the north that leads to the bedroom and a door to the west that leads to a hallway. The front door to the south leads you outside, but I wouldn't leave the baby unattended again...");} else {
cout << "What is throwing a brick going to accomplish?";
}
goto main_loop;}if (verb == "take") {
cout << "You take the brick. it's quite wet in your pocket.";
goto main_loop;}if (verb == "pickup") {
if (mother->canCarry()) {
mother->getInventory()->addItem(brick.getName(), &brick);
} else {
cout << "You are carrying too much already";
}
goto main_loop;}if (verb == "examine") {
cout << brick.getName();
goto main_loop;}if (verb == "drop") {
if (mother->getInventory()->hasItem(brick.getName())) {
mother->getLocation()->addItem(brick.getName(), &brick);
} else {
cout << "I don't have ";
cout << brick.getName();
cout << ".";
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "brick" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("Couch")) && (mother->getLocation()->hasItem("Couch") || mother->getInventory()->hasItem("Couch"))) {
if (verb == "sit") {
cout << "You sit on the couch and fall asleep. When you wake up it's silent.\nThe baby's dead";
break;
goto main_loop;}if (verb == "pickup") {
if (mother->canCarry()) {
mother->getInventory()->addItem(couch.getName(), &couch);
} else {
cout << "You are carrying too much already";
}
goto main_loop;}if (verb == "lift") {
cout << "You lift the couch up from one side. No baby under here.";
goto main_loop;}if (verb == "examine") {
cout << couch.getName();
goto main_loop;}if (verb == "drop") {
if (mother->getInventory()->hasItem(couch.getName())) {
mother->getLocation()->addItem(couch.getName(), &couch);
} else {
cout << "I don't have ";
cout << couch.getName();
cout << ".";
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "Couch" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("television")) && (mother->getLocation()->hasItem("television") || mother->getInventory()->hasItem("television"))) {
if (verb == "pickup") {
if (mother->canCarry()) {
mother->getInventory()->addItem(television.getName(), &television);
} else {
cout << "You are carrying too much already";
}
goto main_loop;}if (verb == "on") {
cout << "Now is not the time to watch TV!!! You have a  more important task at hand.";
goto main_loop;}if (verb == "examine") {
cout << television.getName();
goto main_loop;}if (verb == "drop") {
if (mother->getInventory()->hasItem(television.getName())) {
mother->getLocation()->addItem(television.getName(), &television);
} else {
cout << "I don't have ";
cout << television.getName();
cout << ".";
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "television" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("Toilet")) && (mother->getLocation()->hasItem("Toilet") || mother->getInventory()->hasItem("Toilet"))) {
if (verb == "sit") {
cout << "You sit on the toilet. The crying isn't very loud isn't very loud in here, you may want to try looking elsewhere";
goto main_loop;}if (verb == "pickup") {
if (mother->canCarry()) {
mother->getInventory()->addItem(toilet.getName(), &toilet);
} else {
cout << "You are carrying too much already";
}
goto main_loop;}if (verb == "open") {
cout << "You lift the toilet lid.";
if (toilet.getLocation() == toilet_room) {
if (brick.getLocation() == dead_space) {
cout << "Inside is a brick!";
toilet_room->addItem(brick.getName(), &brick);
} else {
cout << "The toilet is empty";
}
}
goto main_loop;}if (verb == "examine") {
cout << toilet.getName();
goto main_loop;}if (verb == "drop") {
if (mother->getInventory()->hasItem(toilet.getName())) {
mother->getLocation()->addItem(toilet.getName(), &toilet);
} else {
cout << "I don't have ";
cout << toilet.getName();
cout << ".";
}
goto main_loop;}if (verb == "close") {
cout << "You put down the toilet lid.";
if (brick.getLocation() == toilet_room) {
dead_space->addItem(brick.getName(), &brick);
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "Toilet" << "'";
goto main_loop;
}cout << "I can't find a " << noun << " here";
}
}
}