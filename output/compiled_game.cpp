#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Location.h"
#include "Player.h"
using namespace std;
#define GAME_NAME "*****The Haunted Mansion*****"
#define CREDITS "By Samuel Garner, George Phillips, Edward Hills and Stephen Herd"
#define WELCOME_MESSAGE "Your name is Andy an amateur ghost buster. You have arrived at your first job armed only with your trusty wrench. Infront of you is an old mansion said to be haunted by an evil presence. This is the perfect place to hone your ghost busting skills."
#define DEFAULT_RESPONSE "You do not know how to"
#define DEFAULT_INVENTORY_NAME "Inventory: "
#define DEFAULT_INTERACTIVE_NAME "Objects: "
string toLower(string text);
int main(int argc, char **argv) {
string username;
string command;
string command_word;
string verb;
string noun;
string join;
string second_noun;
string prompt;
int count;

Player* andy = new Player();

Location* deadSpace = new Location("Dead space", "Dead space", "deadSpace");
Location* diningRoom = new Location("The dining room", "You find yourself in an old dining room, complete with ornate chandeliers.", "diningRoom");
Location* entranceHall = new Location("The entrance hall", "You enter a dimly lit hall illuminated only by the faint moonlight filtering through the dusty windows. You are surrounded in darkness but can make out doorways to the east and west. South leads out the window to the overgrown garden.", "entranceHall");
Location* garden = new Location("The overgrown garden", "You are in an overgrown garden in front of the mansion. The front door has been bolted shut by locals but you notice a window near by that you might be able to squeeze through.", "garden");
Location* inventory = new Location("inventory", "Player's inventory.", "inventory");
Location* masterBedroom = new Location("The master bedroom", "You are surrounded in complete darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you.", "masterBedroom");
Location* secretHall = new Location("The secret hall", "A long narrow hallway extends out in front of you, you see a door at end of the hall which you feel a dark forbidding presence radiating from.", "secretHall");
Location* tortureRoom = new Location("The torture room", "You enter a cold stone room and instantly feel dred. There are rotting corpses sprawled out around you eminating a foul stench. An apparition materializes in front of you wielding a menacing scythe. You have finally reached your destination.", "tortureRoom");

andy->setLocation(garden);
inventory->setName(DEFAULT_INVENTORY_NAME);
andy->setInventory(inventory);
andy->setMaxItems(4);

diningRoom->setWest(entranceHall);
entranceHall->setSouth(garden);
entranceHall->setEast(diningRoom);
entranceHall->setWest(masterBedroom);
masterBedroom->setEast(entranceHall);
masterBedroom->setShowItems(false);
secretHall->setSouth(entranceHall);
tortureRoom->setSouth(secretHall);

Location* bed = new Location("bed", "A massive dusty bed.", "bed");
Location* box = new Location("box", "A large wooden box.", "box");
Location* door = new Location("door", "A solid wooden door is located in the north wall. You notice a small key hole.", "door");
Location* key = new Location("key", "A small key.", "key");
Location* lamp = new Location("lamp", "An old lamp but still looks like it might work.", "lamp");
Location* mansion_door = new Location("door", "The mansion door is bolted shut. You will need to find another way in.", "mansion_door");
Location* mirror = new Location("mirror", "You see your handsome, confident reflection in the mirror. This mirror could be useful.", "mirror");
Location* skull = new Location("skull", "A cracked human skull.", "skull");
Location* window = new Location("window", "A cracked window that seems to be your only access to the mansion.", "window");
Location* wrench = new Location("wrench", "Your trusty wrench. You have used it to help you out of many a tight jam.", "wrench");
masterBedroom->addItem("bed", bed);
bed->setLocation(masterBedroom);
secretHall->addItem("box", box);
box->setLocation(secretHall);
box->setShowItems(false);
box->addAttribute("!isOpen", true);
box->addAttribute("isOpen", false);
secretHall->addItem("door", door);
door->setLocation(secretHall);
door->addAttribute("isLocked", true);
door->addAttribute("!isLocked", false);
door->addAttribute("!isOpen", true);
door->addAttribute("isOpen", false);
deadSpace->addItem("key", key);
key->setLocation(deadSpace);
key->addAttribute("canPickup", true);
key->addAttribute("!canPickup", false);
key->addAttribute("putBox", true);
key->addAttribute("!putBox", false);
diningRoom->addItem("lamp", lamp);
lamp->setLocation(diningRoom);
lamp->setShowItems(false);
lamp->addAttribute("canPickup", true);
lamp->addAttribute("!canPickup", false);
garden->addItem("door", mansion_door);
mansion_door->setLocation(garden);
masterBedroom->addItem("mirror", mirror);
mirror->setLocation(masterBedroom);
mirror->addAttribute("canPickup", true);
mirror->addAttribute("!canPickup", false);
mirror->addAttribute("putBox", true);
mirror->addAttribute("!putBox", false);
box->addItem("skull", skull);
skull->setLocation(box);
skull->addAttribute("canPickup", true);
skull->addAttribute("!canPickup", false);
skull->addAttribute("putBox", true);
skull->addAttribute("!putBox", false);
garden->addItem("window", window);
window->setLocation(garden);
window->addAttribute("!isOpen", true);
window->addAttribute("isOpen", false);
window->addAttribute("isJammed", true);
window->addAttribute("!isJammed", false);
inventory->addItem("wrench", wrench);
wrench->setLocation(inventory);
wrench->addAttribute("canPickup", true);
wrench->addAttribute("!canPickup", false);
wrench->addAttribute("putBox", true);
wrench->addAttribute("!putBox", false);

cout << endl << "			" << GAME_NAME << endl;
cout << CREDITS << endl << endl;
cout << WELCOME_MESSAGE << endl << endl;
prompt = "\n>>> ";
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems(DEFAULT_INTERACTIVE_NAME);

while (true) { 
   main_loop:
   cout << prompt;
   prompt = "\n>>> ";
   getline(cin, command);
   if (command == "") {
		prompt = ">>> "; 
		goto main_loop; 
	} else { 
   	prompt = "\n>>> ";
 	}
   istringstream word(command);
   command_word = "";
   verb = "";
   noun = "";
   join = "";
   second_noun = "";
   count = 0;
   do {
      word >> command_word;
      if (count == 0 && command_word != "") {
           verb = command_word;
           count++;
      } else if (count == 1 && command_word != "") {
           noun = command_word;
           count++;
      } else if (count == 2 && command_word != "") {
           join = command_word;
           count++;
      } else if (count == 3 && command_word != "") {
           second_noun = command_word;
           count++;
      } else if (count == 4 && command_word != "") {
           count++;
           break;
      }
      command_word = "";
    } while (word);

if (count == 1) {

if (verb == "east" || verb == "e"){
if (andy->getLocation()->hasEast()) {
andy->setLocation(andy->getLocation()->getEast()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems(DEFAULT_INTERACTIVE_NAME);
} else {
cout << "You cannot go east.";
}

goto main_loop;
}
if (verb == "i" || verb == "inventory" || verb == "invent" || verb == "inv"){
cout << inventory->getName() << andy->getInventory()->listItems("") << " ";
cout << andy->getNumberOfItems() << "/" << andy->getMaxItems();

goto main_loop;
}
if (verb == "look" || verb == "l"){
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems(DEFAULT_INTERACTIVE_NAME);

goto main_loop;
}
if (verb == "north" || verb == "n" || verb == "nth"){
if (andy->getLocation()->hasNorth()) {
andy->setLocation(andy->getLocation()->getNorth()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems(DEFAULT_INTERACTIVE_NAME);
} else {
cout << "You cannot go north.";
}

goto main_loop;
}
if (verb == "quit" || verb == "q"){
cout << "Bye bye thanks for playing!!!";
break;

goto main_loop;
}
if (verb == "south" || verb == "s" || verb == "sth"){
if (andy->getLocation() == tortureRoom) {
cout << "As you turn to flee you hear a bone-chilling cackling behind you as the apparation swings his scythe. Before you can react you feel a sickening pain in your neck. You have been decapitated, your head rolls and your body crumples to the ground. You are dead.";
break;
}
if (andy->getLocation()->hasSouth()) {
andy->setLocation(andy->getLocation()->getSouth()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems(DEFAULT_INTERACTIVE_NAME);
} else {
cout << "You cannot go south.";
}

goto main_loop;
}
if (verb == "west" || verb == "w"){
if (andy->getLocation()->hasWest()) {
andy->setLocation(andy->getLocation()->getWest()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems(DEFAULT_INTERACTIVE_NAME);
} else {
cout << "You cannot go west.";
}

goto main_loop;
}

} else if (count == 2) {

if (((andy->getLocation()->getVariableName() == bed->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("bed") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("bed"))) {
if (verb == "under" || verb == "look" || verb == "examine" || verb == "x" || verb == "ex" || verb == "l") {
if (key->getLocation() == andy->getInventory()) {
cout << "A massive dusty bed.";
} else {
cout << "You see a key glinting under the bed.";
masterBedroom->addItem(key->getName(), key);
}
goto main_loop;}
if (verb == "sleep" || verb == "nap") {
cout << "You lay down on the bed. As your eyes close you feel something lay down beside you. Your eyes flicker open but there is nobody there. You decide this is not a good place to take a nap.";
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (bed->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(bed->getVariableName())) {
cout << "You already have the bed";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(bed->getName(), bed);
cout << "You pickup the bed.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the bed what were you thinking...";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << bed->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(bed->getVariableName())) {
andy->getLocation()->addItem(bed->getName(), bed);
cout << "You drop the bed.";
} else {
cout << "You do not have a bed.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == box->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("box") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("box"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (box->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(box->getVariableName())) {
cout << "You already have the box";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(box->getName(), box);
cout << "You pickup the box.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the box what were you thinking...";
}
goto main_loop;}
if (verb == "open") {
if (box->hasAttribute("!isOpen")) {
box->setShowItems(true);
box->setAttribute("isOpen", true);
box->setAttribute("!isOpen", false);
cout << "You open the box and find a ";
cout << box->listItems();
} else {
cout << "The box is already open.";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << box->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(box->getVariableName())) {
andy->getLocation()->addItem(box->getName(), box);
cout << "You drop the box.";
} else {
cout << "You do not have a box.";
}
goto main_loop;}
if (verb == "close") {
if (box->hasAttribute("isOpen")) {
box->setShowItems(false);
box->setAttribute("!isOpen", true);
box->setAttribute("isOpen", false);
cout << "You close the box.";
} else {
cout << "The box is already closed.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == door->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("door") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("door"))) {
if (verb == "unlock") {
if (key->getLocation() == andy->getInventory()) {
if (door->hasAttribute("isLocked")) {
door->setAttribute("!isLocked", true);
door->setAttribute("isLocked", false);
cout << "You struggle to turn the key in the old door but manage to unlock it.";
} else {
cout << "The door is already unlocked.";
}
} else {
cout << "You do not have a key to unlock the door.";
}
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (door->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(door->getVariableName())) {
cout << "You already have the door";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(door->getName(), door);
cout << "You pickup the door.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the door what were you thinking...";
}
goto main_loop;}
if (verb == "open") {
if (door->hasAttribute("!isOpen")) {
if (door->hasAttribute("isLocked")) {
cout << "You cannot open the door it is locked.";
} else {
door->setAttribute("isOpen", true);
door->setAttribute("!isOpen", false);
secretHall->setNorth(tortureRoom);
cout << "The door swings open.";
}
} else {
cout << "The door is already open";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << door->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(door->getVariableName())) {
andy->getLocation()->addItem(door->getName(), door);
cout << "You drop the door.";
} else {
cout << "You do not have a door.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == key->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("key") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("key"))) {
if (verb == "use") {
if (door->hasAttribute("isLocked")) {
if (andy->getLocation() == secretHall) {
cout << "You struggle to turn the key in the old door but manage to unlock it.";
secretHall->setNorth(tortureRoom);
door->setAttribute("!isLocked", true);
door->setAttribute("isLocked", false);
} else {
cout << "You can not use the key here.";
}
} else {
cout << "The door is already unlocked.";
}
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (key->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(key->getVariableName())) {
cout << "You already have the key";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(key->getName(), key);
cout << "You pickup the key.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the key what were you thinking...";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << key->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(key->getVariableName())) {
andy->getLocation()->addItem(key->getName(), key);
cout << "You drop the key.";
} else {
cout << "You do not have a key.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == lamp->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("lamp") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("lamp"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (lamp->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(lamp->getVariableName())) {
cout << "You already have the lamp";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(lamp->getName(), lamp);
cout << "You pickup the lamp.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the lamp what were you thinking...";
}
goto main_loop;}
if (verb == "off" || verb == "turnoff" || verb == "turn-off") {
if (lamp->getLocation() == andy->getInventory()) {
entranceHall->setDescription("You enter a dimly lit hall illuminated only by the faint moonlight filtering through the dusty windows. You are sourrounded in darkness, but can make out doorways to the east and west. South leads out the window to the overgrown garden.");entranceHall->setNorth(NULL);
masterBedroom->setDescription("You are surrounded in darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you.");masterBedroom->setShowItems(false);
cout << "You switch off the old lamp.";
} else {
cout << "You do not have that item.";
}
goto main_loop;}
if (verb == "light" || verb == "use" || verb == "turn-on" || verb == "turnon") {
if (lamp->getLocation() == andy->getInventory()) {
entranceHall->setDescription("With the aid of the lamp you can now make out a doorway to the north. The other exits are doorways to the east and west and the window leading south.");entranceHall->setNorth(secretHall);
masterBedroom->setDescription("With the lamp illuminating your surroundings you find yourself in a creepy old bedroom decorated with many mirrors. You keep seeing things move in them out of the corner of your eye. There is also a massive bed taking up most of the room. You can see many things glinting under it.");masterBedroom->setShowItems(true);
cout << "You fiddle around with the old lamp and manage to turn it on.";
} else {
cout << "You do not have that item.";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << lamp->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(lamp->getVariableName())) {
andy->getLocation()->addItem(lamp->getName(), lamp);
cout << "You drop the lamp.";
} else {
cout << "You do not have a lamp.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == mansion_door->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("mansion_door") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("door"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (mansion_door->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(mansion_door->getVariableName())) {
cout << "You already have the mansion_door";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(mansion_door->getName(), mansion_door);
cout << "You pickup the mansion_door.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the mansion_door what were you thinking...";
}
goto main_loop;}
if (verb == "open") {
cout << "The mansion door is bolted shut. You will need to find another way in.";
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << mansion_door->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(mansion_door->getVariableName())) {
andy->getLocation()->addItem(mansion_door->getName(), mansion_door);
cout << "You drop the mansion_door.";
} else {
cout << "You do not have a mansion_door.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == mirror->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("mirror") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("mirror"))) {
if (verb == "use" || verb == "lookat" || verb == "look-at") {
if (andy->getLocation() == tortureRoom) {
cout << "You pull out out the mirror, the ghost upon seeing it's horrific reflection flees in terror. Congratulations you have busted your first ghost!";
break;
} else {
cout << "You admire yourself in the mirror.";
}
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (mirror->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(mirror->getVariableName())) {
cout << "You already have the mirror";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(mirror->getName(), mirror);
cout << "You pickup the mirror.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the mirror what were you thinking...";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << mirror->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(mirror->getVariableName())) {
andy->getLocation()->addItem(mirror->getName(), mirror);
cout << "You drop the mirror.";
} else {
cout << "You do not have a mirror.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == skull->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("skull") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("skull"))) {
if (verb == "wear") {
if (skull->getLocation() == andy->getInventory()) {
cout << "For some perverse reason you shove the skull onto your head. Your body starts to decay and rot away, before you know it you have provided this skull with a new skeleton.";
break;
} else {
cout << "You do not have the skull in your inventory.";
}
goto main_loop;}
if (verb == "use" || verb == "show") {
if (skull->getLocation() == andy->getInventory()) {
if (andy->getLocation() == tortureRoom) {
cout << "The skull begins to contort and grow, before long the skull has morphed into an angry looking ghost of a man. It lets out a blood curdling cry and lashes out at the apparation. The evil apparation disapates and dies... again. The man ghost turns and knods his thanks to you and vanishes. You have won congradulations!";
break;
} else {
cout << "You wave the skull around like a demented lunatic.";
}
} else {
cout << "You do not have that item.";
}
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (skull->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(skull->getVariableName())) {
cout << "You already have the skull";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(skull->getName(), skull);
cout << "You pickup the skull.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the skull what were you thinking...";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << skull->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(skull->getVariableName())) {
andy->getLocation()->addItem(skull->getName(), skull);
cout << "You drop the skull.";
} else {
cout << "You do not have a skull.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == window->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("window") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("window"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (window->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(window->getVariableName())) {
cout << "You already have the window";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(window->getName(), window);
cout << "You pickup the window.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the window what were you thinking...";
}
goto main_loop;}
if (verb == "open") {
if (window->hasAttribute("!isOpen")) {
if (window->hasAttribute("isJammed")) {
cout << "You cannot open the window it is jammed.";
} else {
window->setDescription("The window is open allowing you access to the mansion.");window->setAttribute("isOpen", true);
window->setAttribute("!isOpen", false);
garden->setNorth(entranceHall);
cout << "With a heave the window grates open to leave a nice opening to enter through.";
}
} else {
cout << "The window is already open.";
}
goto main_loop;}
if (verb == "go" || verb == "climb" || verb == "enter") {
if (window->hasAttribute("isOpen")) {
andy->setLocation(entranceHall);
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems(DEFAULT_INTERACTIVE_NAME);
} else {
cout << "You cannot do that the window is closed.";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << window->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(window->getVariableName())) {
andy->getLocation()->addItem(window->getName(), window);
cout << "You drop the window.";
} else {
cout << "You do not have a window.";
}
goto main_loop;}
}
if (((andy->getLocation()->getVariableName() == wrench->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("wrench") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("wrench"))) {
if (verb == "use") {
if (andy->getLocation() == garden) {
if (wrench->getLocation() == andy->getInventory()) {
if (window->hasAttribute("isJammed")) {
window->setAttribute("!isJammed", true);
window->setAttribute("isJammed", false);
cout << "You manage to pry open the window far enough to get your hands under.";
} else {
cout << "You have already pried loose the window.";
}
} else {
cout << "You do not have the wrench.";
}
} else {
cout << "You cannot use the wrench here.";
}
goto main_loop;}
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (wrench->hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(wrench->getVariableName())) {
cout << "You already have the wrench";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(wrench->getName(), wrench);
cout << "You pickup the wrench.";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the wrench what were you thinking...";
}
goto main_loop;}
if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << wrench->getDescription();
goto main_loop;}
if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(wrench->getVariableName())) {
andy->getLocation()->addItem(wrench->getName(), wrench);
cout << "You drop the wrench.";
} else {
cout << "You do not have a wrench.";
}
goto main_loop;}
}

} else if (count == 4) {

if (((andy->getLocation()->getVariableName() == bed->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("bed") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("bed"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (bed->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
bed->addItem(bed->getName(), bed);
cout << "You put the bed into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the bed.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the bed in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == box->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("box") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("box"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (box->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(box->getName(), box);
cout << "You put the box into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the box.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the box in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == door->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("door") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("door"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (door->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(door->getName(), door);
cout << "You put the door into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the door.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the door in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == key->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("key") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("key"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (key->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(key->getName(), key);
cout << "You put the key into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the key.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the key in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == lamp->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("lamp") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("lamp"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (lamp->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(lamp->getName(), lamp);
cout << "You put the lamp into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the lamp.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the lamp in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == mansion_door->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("mansion_door") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("door"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (mansion_door->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(mansion_door->getName(), mansion_door);
cout << "You put the mansion_door into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the mansion_door.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the mansion_door in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == mirror->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("mirror") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("mirror"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (mirror->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(mirror->getName(), mirror);
cout << "You put the mirror into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the mirror.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the mirror in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == skull->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("skull") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("skull"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (skull->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(skull->getName(), skull);
cout << "You put the skull into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the skull.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the skull in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == window->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("window") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("window"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (window->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(window->getName(), window);
cout << "You put the window into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the window.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the window in the box.";
}
goto main_loop;
}
if (((andy->getLocation()->getVariableName() == wrench->getLocation()->getVariableName() && andy->getLocation()->getShowItems()) || andy->getInventory()->hasItem("wrench") || andy->getLocation()->itemHasItem(noun) || andy->getInventory()->itemHasItem(noun)) && (toLower(noun) == toLower("wrench"))) {
if ((verb == "put" || verb == "place") && (join == "into" || join == "in" || join == "inside") && box->getName() ==  second_noun) {
if (wrench->hasAttribute("putBox")) {
if (andy->getLocation() == secretHall) {
if (box->hasAttribute("isOpen")) {
box->addItem(wrench->getName(), wrench);
cout << "You put the wrench into the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the wrench.";
}
} else {
cout << "You cannot do that here.";
}
} else {
cout << "You cannot put the wrench in the box.";
}
goto main_loop;
}
}
cout << DEFAULT_RESPONSE << " " << command;
}
}