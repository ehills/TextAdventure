#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Location.h"
#include "Item.h"
#include "Player.h"
using namespace std;
#define GAME_NAME "*****The Haunted Mansion*****"
#define CREDITS "By Edward Hills, George Phillips, Samuel Garner and Stephen Herd"
#define WELCOME_MESSAGE "Your name is Andy an amateur ghost buster. You have arrived at your first job armed only with your trusty wrench. Infront of you is an old mansion said to be haunted by an evil presence. This is the perfect place to hone your ghost busting skills."
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
Location* inventory = new Location("inventory", "Player's inventory.", "andy->getInventory()");
Location* masterBedroom = new Location("The master bedroom", "You are surrounded in complete darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you.", "masterBedroom");
Location* secretHall = new Location("The secret hall", "A long narrow hallway extends out in front of you, you see a door at end of the hall which you feel a dark forbidding presence radiating from.", "secretHall");
Location* tortureRoom = new Location("The torture room", "You enter a cold stone room and instantly feel dred. There are rotting corpses sprawled out around you eminating a foul stench. An apparition materializes in front of you wielding a menacing scythe. You have finally reached your destination.", "tortureRoom");

andy->setLocation(garden);andy->setInventory(inventory);andy->setMaxItems(4);
diningRoom->setWest(entranceHall);
entranceHall->setSouth(garden);
entranceHall->setEast(diningRoom);
entranceHall->setWest(masterBedroom);
masterBedroom->setEast(entranceHall);
secretHall->setSouth(entranceHall);
tortureRoom->setSouth(secretHall);

Item bed("bed", "A massive dusty bed.", "bed");
deadSpace->addItem("bed", &bed);
bed.setLocation(deadSpace);
Item box("box", "A large wooden box.", "box");
secretHall->addItem("box", &box);
box.setLocation(secretHall);
box.addAttribute("!isOpen", true);
box.addAttribute("isOpen", false);
box.addAttribute("hasSkull", true);
box.addAttribute("!hasSkull", false);
Item door("door", "A solid wooden door is located in the north wall. You notice a small key hole.", "door");
secretHall->addItem("door", &door);
door.setLocation(secretHall);
door.addAttribute("isLocked", true);
door.addAttribute("!isLocked", false);
door.addAttribute("!isOpen", true);
door.addAttribute("isOpen", false);
Item key("key", "A small key.", "key");
deadSpace->addItem("key", &key);
key.setLocation(deadSpace);
key.addAttribute("canPickup", true);
key.addAttribute("!canPickup", false);
Item lamp("lamp", "An old lamp but still looks like it might work.", "lamp");
diningRoom->addItem("lamp", &lamp);
lamp.setLocation(diningRoom);
lamp.addAttribute("canPickup", true);
lamp.addAttribute("!canPickup", false);
Item mansion_door("door", "The mansion door is bolted shut. You will need to find another way in.", "mansion_door");
garden->addItem("door", &mansion_door);
mansion_door.setLocation(garden);
Item mirror("mirror", "You see your handsome, confident reflection in the mirror. This mirror could be useful.", "mirror");
deadSpace->addItem("mirror", &mirror);
mirror.setLocation(deadSpace);
mirror.addAttribute("canPickup", true);
mirror.addAttribute("!canPickup", false);
Item skull("skull", "A cracked human skull.", "skull");
deadSpace->addItem("skull", &skull);
skull.setLocation(deadSpace);
skull.addAttribute("canPickup", true);
skull.addAttribute("!canPickup", false);
Item window("window", "A cracked window that seems to be your only access to the mansion.", "window");
garden->addItem("window", &window);
window.setLocation(garden);
window.addAttribute("!isOpen", true);
window.addAttribute("isOpen", false);
window.addAttribute("isJammed", true);
window.addAttribute("!isJammed", false);
Item wrench("wrench", "Your trusty wrench. You've used it to help you out of many a tight jam.", "wrench");
andy->getInventory()->addItem("wrench", &wrench);
wrench.setLocation(andy->getInventory());
wrench.addAttribute("canPickup", true);
wrench.addAttribute("!canPickup", false);
cout << endl << "			" << GAME_NAME << endl;
cout << CREDITS << endl << endl;
cout << WELCOME_MESSAGE << endl << endl;
prompt = "\n>>> ";
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();

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

if (count == 3 || count > 4) {
	 cout << "Enter 1, 2 or 4 words: a (verb) or a (verb and noun) or a (verb, noun, join and noun).";
	goto main_loop;
}

if (count == 1) {

if (verb == "east" || verb == "e"){
if (andy->getLocation()->hasEast()) {
andy->setLocation(andy->getLocation()->getEast()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();
} else {
cout << "You cannot go east.";
}

goto main_loop;}
if (verb == "i" || verb == "inventory" || verb == "invent" || verb == "inv"){
cout << "Inventory " << andy->getInventory()->listItems() << " ";
cout << andy->getNumberOfItems() << "/" << andy->getMaxItems();

goto main_loop;}
if (verb == "look" || verb == "l"){
if (andy->getLocation() == tortureRoom) {
cout << "You look into the face of death and feel his scythe rip through your body. You flop over in agony and slowly die with the last thing you hear being the spectre cackling at your misfortune.";
break;
} else {
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();
}

goto main_loop;}
if (verb == "north" || verb == "n" || verb == "nth"){
if (andy->getLocation()->hasNorth()) {
andy->setLocation(andy->getLocation()->getNorth()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();
} else {
cout << "You cannot go north.";
}

goto main_loop;}
if (verb == "quit" || verb == "q"){
cout << "Bye bye thanks for playing!!!";
break;

goto main_loop;}
if (verb == "south" || verb == "s" || verb == "sth"){
if (andy->getLocation() == tortureRoom) {
cout << "As you turn to flee you hear a bone-chilling cackling behind you as the apparation swings his scythe. Before you can react you feel a sickening pain in your neck. You have been decapitated, your head rolls and your body crumples to the ground. You are dead.";
break;
}
if (andy->getLocation()->hasSouth()) {
andy->setLocation(andy->getLocation()->getSouth()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();
} else {
cout << "You cannot go south.";
}

goto main_loop;}
if (verb == "west" || verb == "w"){
if (andy->getLocation()->hasWest()) {
andy->setLocation(andy->getLocation()->getWest()); 
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();
} else {
cout << "You cannot go west.";
}

goto main_loop;}

cout << "I don't know how to " << verb << " here.";

} else if (count == 2){

if ((andy->getLocation()->getVariableName() == bed.getLocation()->getVariableName() || andy->getInventory()->hasItem("bed")) && (toLower(noun) == toLower("bed"))) {
if (verb == "under" || verb == "look" || verb == "examine" || verb == "x" || verb == "ex") {
if (key.getLocation() == andy->getInventory()) {
cout << "A massive dusty bed.";
} else {
cout << "You see a key glinting under the bed.";
masterBedroom->addItem(key.getName(), &key);
}
goto main_loop;}if (verb == "sleep" || verb == "nap") {
cout << "You lay down on the bed. As your eyes close you feel something lay down beside you. Your eyes flicker open but there's nobody there. You decide this is not a good place to take a nap.";
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (bed.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (bed.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(bed.getVariableName())) {
cout << "You already have the ";
cout << bed.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(bed.getName(), &bed);
cout << "You pickup the ";
cout << bed.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << bed.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << bed.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(bed.getVariableName())) {
andy->getLocation()->addItem(bed.getName(), &bed);
cout << "You drop the ";
cout << bed.getName() << ".";
} else {
cout << "You don't have a ";
cout << bed.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "bed" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == box.getLocation()->getVariableName() || andy->getInventory()->hasItem("box")) && (toLower(noun) == toLower("box"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (box.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (box.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(box.getVariableName())) {
cout << "You already have the ";
cout << box.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(box.getName(), &box);
cout << "You pickup the ";
cout << box.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << box.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "open") {
if (box.hasAttribute("!isOpen")) {
if (box.hasAttribute("hasSkull")) {
secretHall->addItem(skull.getName(), &skull);
box.setAttribute("isOpen", true);
box.setAttribute("!isOpen", false);
cout << "You open the box and discover a human skull. The body is nowhere to been seen.";
} else {
box.setAttribute("isOpen", true);
box.setAttribute("!isOpen", false);
cout << "You open the box to find nothing inside.";
}
} else {
cout << "The box is already open.";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << box.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(box.getVariableName())) {
andy->getLocation()->addItem(box.getName(), &box);
cout << "You drop the ";
cout << box.getName() << ".";
} else {
cout << "You don't have a ";
cout << box.getName() << ".";
}
goto main_loop;}if (verb == "close") {
if (box.hasAttribute("isOpen")) {
if (skull.getLocation() == secretHall) {
if (box.hasAttribute("hasSkull")) {
deadSpace->addItem(skull.getName(), &skull);
box.setAttribute("!isOpen", true);
box.setAttribute("isOpen", false);
cout << "You shut the creepy looking skull back into the box.";
} else {
box.setAttribute("!isOpen", true);
box.setAttribute("isOpen", false);
cout << "You shut the box.";
}
} else {
box.setAttribute("!isOpen", true);
box.setAttribute("isOpen", false);
cout << "You shut the box.";
}
} else {
cout << "The box is already closed.";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "box" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == door.getLocation()->getVariableName() || andy->getInventory()->hasItem("door")) && (toLower(noun) == toLower("door"))) {
if (verb == "unlock") {
if (key.getLocation() == andy->getInventory()) {
if (door.hasAttribute("isLocked")) {
door.setAttribute("!isLocked", true);
door.setAttribute("isLocked", false);
cout << "You struggle to turn the key in the old door but manage to unlock it.";
} else {
cout << "The door is already unlocked.";
}
} else {
cout << "You do not have a key to unlock the door.";
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (door.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (door.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(door.getVariableName())) {
cout << "You already have the ";
cout << door.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(door.getName(), &door);
cout << "You pickup the ";
cout << door.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << door.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "open") {
if (door.hasAttribute("!isOpen")) {
if (door.hasAttribute("isLocked")) {
cout << "You cannot open the door it is locked.";
} else {
door.setAttribute("isOpen", true);
door.setAttribute("!isOpen", false);
secretHall->setNorth(tortureRoom);
cout << "The door swings open.";
}
} else {
cout << "The door is already open";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << door.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(door.getVariableName())) {
andy->getLocation()->addItem(door.getName(), &door);
cout << "You drop the ";
cout << door.getName() << ".";
} else {
cout << "You don't have a ";
cout << door.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "door" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == key.getLocation()->getVariableName() || andy->getInventory()->hasItem("key")) && (toLower(noun) == toLower("key"))) {
if (verb == "use") {
if (door.hasAttribute("isLocked")) {
if (andy->getLocation() == secretHall) {
cout << "You struggle to turn the key in the old door but manage to unlock it.";
secretHall->setNorth(tortureRoom);
door.setAttribute("!isLocked", true);
door.setAttribute("isLocked", false);
} else {
cout << "You can't use the key here.";
}
} else {
cout << "The door is already unlocked.";
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (key.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (key.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(key.getVariableName())) {
cout << "You already have the ";
cout << key.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(key.getName(), &key);
cout << "You pickup the ";
cout << key.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << key.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << key.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(key.getVariableName())) {
andy->getLocation()->addItem(key.getName(), &key);
cout << "You drop the ";
cout << key.getName() << ".";
} else {
cout << "You don't have a ";
cout << key.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "key" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == lamp.getLocation()->getVariableName() || andy->getInventory()->hasItem("lamp")) && (toLower(noun) == toLower("lamp"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (lamp.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (lamp.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(lamp.getVariableName())) {
cout << "You already have the ";
cout << lamp.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(lamp.getName(), &lamp);
cout << "You pickup the ";
cout << lamp.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << lamp.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "off" || verb == "turnoff" || verb == "turn-off") {
if (lamp.getLocation() == andy->getInventory()) {
entranceHall->setDescription("You enter a dimly lit hall illuminated only by the faint moonlight filtering through the dusty windows. You are sourrounded in darkness, but can make out doorways to the east and west. South leads out the window to the overgrown garden.");entranceHall->setNorth(NULL);
masterBedroom->setDescription("You are surrounded in darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you.");cout << "You switch off the old lamp.";
} else {
cout << "You don't have that item.";
}
goto main_loop;}if (verb == "light" || verb == "use" || verb == "turn-on" || verb == "turnon") {
if (lamp.getLocation() == andy->getInventory()) {
entranceHall->setDescription("With the aid of the lamp you can now make out a doorway to the north. The other exits are doorways to the east and west and the window leading south.");entranceHall->setNorth(secretHall);
masterBedroom->setDescription("With the lamp illuminating your surroundings you find yourself in a creepy old bedroom decorated with many mirrors. You keep seeing things move in them out of the corner of your eye. There is also a massive bed taking up most of the room. You can see many things glinting under it.");masterBedroom->addItem(mirror.getName(), &mirror);
masterBedroom->addItem(bed.getName(), &bed);
cout << "You fiddle around with the old lamp and manage to turn it on.";
} else {
cout << "You don't have that item.";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << lamp.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(lamp.getVariableName())) {
andy->getLocation()->addItem(lamp.getName(), &lamp);
cout << "You drop the ";
cout << lamp.getName() << ".";
} else {
cout << "You don't have a ";
cout << lamp.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "lamp" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == mansion_door.getLocation()->getVariableName() || andy->getInventory()->hasItem("mansion_door")) && (toLower(noun) == toLower("door"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (mansion_door.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (mansion_door.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(mansion_door.getVariableName())) {
cout << "You already have the ";
cout << mansion_door.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(mansion_door.getName(), &mansion_door);
cout << "You pickup the ";
cout << mansion_door.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << mansion_door.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "open") {
cout << "The mansion door is bolted shut. You will need to find another way in.";
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << mansion_door.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(mansion_door.getVariableName())) {
andy->getLocation()->addItem(mansion_door.getName(), &mansion_door);
cout << "You drop the ";
cout << mansion_door.getName() << ".";
} else {
cout << "You don't have a ";
cout << mansion_door.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "door" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == mirror.getLocation()->getVariableName() || andy->getInventory()->hasItem("mirror")) && (toLower(noun) == toLower("mirror"))) {
if (verb == "use" || verb == "lookat" || verb == "look-at") {
if (andy->getLocation() == tortureRoom) {
cout << "You pull out out the mirror, the ghost upon seeing it's horrific reflection flees in terror. Congratulations you have busted your first ghost!";
break;
} else {
cout << "You admire yourself in the mirror.";
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (mirror.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (mirror.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(mirror.getVariableName())) {
cout << "You already have the ";
cout << mirror.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(mirror.getName(), &mirror);
cout << "You pickup the ";
cout << mirror.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << mirror.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << mirror.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(mirror.getVariableName())) {
andy->getLocation()->addItem(mirror.getName(), &mirror);
cout << "You drop the ";
cout << mirror.getName() << ".";
} else {
cout << "You don't have a ";
cout << mirror.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "mirror" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == skull.getLocation()->getVariableName() || andy->getInventory()->hasItem("skull")) && (toLower(noun) == toLower("skull"))) {
if (verb == "wear") {
if (skull.getLocation() == andy->getInventory()) {
cout << "For some perverse reason you shove the skull onto your head. Your body starts to decay and rot away, before you know it you have provided this skull with a new skeleton.";
break;
} else {
cout << "You don't have the skull in your inventory.";
}
goto main_loop;}if (verb == "use" || verb == "show") {
if (skull.getLocation() == andy->getInventory()) {
if (andy->getLocation() == tortureRoom) {
cout << "The skull begins to contort and grow, before long the skull has morphed into an angry looking ghost of a man. It lets out a blood curdling cry and lashes out at the apparation. The evil apparation disapates and dies... again. The man ghost turns and knods his thanks to you and vanishes. You have won congradulations!";
break;
} else {
cout << "You wave the skull around like a demented lunatic.";
}
} else {
cout << "You don't have that item.";
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (skull.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (skull.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(skull.getVariableName())) {
cout << "You already have the ";
cout << skull.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(skull.getName(), &skull);
cout << "You pickup the ";
cout << skull.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << skull.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << skull.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(skull.getVariableName())) {
andy->getLocation()->addItem(skull.getName(), &skull);
cout << "You drop the ";
cout << skull.getName() << ".";
} else {
cout << "You don't have a ";
cout << skull.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "skull" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == window.getLocation()->getVariableName() || andy->getInventory()->hasItem("window")) && (toLower(noun) == toLower("window"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (window.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (skull.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(window.getVariableName())) {
cout << "You already have the ";
cout << window.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(window.getName(), &window);
cout << "You pickup the ";
cout << window.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << window.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "open") {
if (window.hasAttribute("!isOpen")) {
if (window.hasAttribute("isJammed")) {
cout << "You cannot open the window it is jammed.";
} else {
window.setDescription("The window is open allowing you access to the mansion.");window.setAttribute("isOpen", true);
window.setAttribute("!isOpen", false);
garden->setNorth(entranceHall);
cout << "With a heave the window grates open to leave a nice opening to enter through.";
}
} else {
cout << "The window is already open.";
}
goto main_loop;}if (verb == "go" || verb == "climb" || verb == "enter") {
if (window.hasAttribute("isOpen")) {
andy->setLocation(entranceHall);
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();
} else {
cout << "You can't do that the window is closed.";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << window.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(window.getVariableName())) {
andy->getLocation()->addItem(window.getName(), &window);
cout << "You drop the ";
cout << window.getName() << ".";
} else {
cout << "You don't have a ";
cout << window.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "window" << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == wrench.getLocation()->getVariableName() || andy->getInventory()->hasItem("wrench")) && (toLower(noun) == toLower("wrench"))) {
if (verb == "use") {
if (andy->getLocation() == garden) {
if (wrench.getLocation() == andy->getInventory()) {
if (window.hasAttribute("isJammed")) {
window.setAttribute("!isJammed", true);
window.setAttribute("isJammed", false);
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
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (wrench.hasAttribute("canPickup")) {
if (andy->getLocation() == secretHall) {
if (skull.getVariableName() == skull.getVariableName()) {
} 
box.setAttribute("!hasSkull", true);
box.setAttribute("hasSkull", false);
}
if (andy->getInventory()->hasItem(wrench.getVariableName())) {
cout << "You already have the ";
cout << wrench.getName() << ".";
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(wrench.getName(), &wrench);
cout << "You pickup the ";
cout << wrench.getName() << ".";
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannot pick up the ";
cout << wrench.getName() << ".";
cout << " What were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << wrench.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(wrench.getVariableName())) {
andy->getLocation()->addItem(wrench.getName(), &wrench);
cout << "You drop the ";
cout << wrench.getName() << ".";
} else {
cout << "You don't have a ";
cout << wrench.getName() << ".";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " << "wrench" << ".";
goto main_loop;
}

cout << "I can't find a " << noun << " here.";

} else if (count == 4){

if ((andy->getLocation()->getVariableName() == bed.getLocation()->getVariableName() || andy->getInventory()->hasItem("bed")) && (toLower(noun) == toLower("bed"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == box.getLocation()->getVariableName() || andy->getInventory()->hasItem("box")) && (toLower(noun) == toLower("box"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == door.getLocation()->getVariableName() || andy->getInventory()->hasItem("door")) && (toLower(noun) == toLower("door"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == key.getLocation()->getVariableName() || andy->getInventory()->hasItem("key")) && (toLower(noun) == toLower("key"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == lamp.getLocation()->getVariableName() || andy->getInventory()->hasItem("lamp")) && (toLower(noun) == toLower("lamp"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == mansion_door.getLocation()->getVariableName() || andy->getInventory()->hasItem("mansion_door")) && (toLower(noun) == toLower("door"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == mirror.getLocation()->getVariableName() || andy->getInventory()->hasItem("mirror")) && (toLower(noun) == toLower("mirror"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == skull.getLocation()->getVariableName() || andy->getInventory()->hasItem("skull")) && (toLower(noun) == toLower("skull"))) {
if ((verb == "put") && (join == "into" || join == "in" || join == "inside")) {
if (andy->getLocation() == secretHall) {
if (box.hasAttribute("isOpen")) {
box.setAttribute("hasSkull", true);
box.setAttribute("!hasSkull", false);
andy->getLocation()->addItem(skull.getName(), &skull);
cout << "You return the skull to the box.";
} else {
cout << "You cannot do that the box is closed.";
}
} else {
cout << "You do not have the skull.";
}
} else {
cout << "You cannot do that here.";
}
goto main_loop;}cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == window.getLocation()->getVariableName() || andy->getInventory()->hasItem("window")) && (toLower(noun) == toLower("window"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

if ((andy->getLocation()->getVariableName() == wrench.getLocation()->getVariableName() || andy->getInventory()->hasItem("wrench")) && (toLower(noun) == toLower("wrench"))) {
cout << "Sorry you can not " << verb << " the " <<  noun  << " " << join << " the " << second_noun << ".";
goto main_loop;
}

}
}