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
#define WELCOME_MESSAGE "Your name is Andy an amateur ghost hunter. You have arrived at your first job. Infront of you is an old, haunted mansion locals say to be inhabited by a long dead sycthe weilding psycho. This is the perfect place to hone your ghost busting skills."
#define QUIT_GAME "quit"
string toLower(string text);
int main(int argc, char **argv) {
string username;
string command;
string verb;
string noun;
string prompt;
int count;

Player* andy = new Player();

Location* deadSpace = new Location("Dead space", "Dead space");
Location* diningRoom = new Location("The dining room", "You find yourself in an old dining room, complete with ornate chandeliers.");
Location* entranceHall = new Location("The entrance hall", "You enter a dimly lit hall illuminated only by the faint moonlight filtering through the dusty windows. You are sourrounded in darkness, but can make out doorways to the east and west. South leads out the window to the overgrown garden.");
Location* garden = new Location("The overgrown garden", "You are in an overgrown garden in front of the mansion. The front door has been bolted shut by locals but you notice a window near by that you might be able to squeeze through.");
Location* inventory = new Location("Inventory", "");
Location* masterBedroom = new Location("The master bedroom", "You are surrounded in complete darkness. You cannot see anything but can hear strange noises close by. A cold chill rushes over you.");
Location* secretHall = new Location("The secret hall", "A long narrow hallway extends out in front of you, you see a door at end of the hall which you feel a dark forbidding presence radiating from.");
Location* tortureRoom = new Location("The torture room", "You enter a cold stone room and instantly feel dred. There are rotting corpses sprawled out around you eminating a foul stench. An apparition materializes in front of you wielding a menacing scythe. You have finally reached your destination.");

andy->setLocation(garden);andy->setInventory(inventory);andy->setMaxItems(4);
diningRoom->setWest(entranceHall);
entranceHall->setSouth(garden);
entranceHall->setEast(diningRoom);
entranceHall->setWest(masterBedroom);
masterBedroom->setEast(entranceHall);
secretHall->setSouth(entranceHall);
tortureRoom->setSouth(secretHall);

Item bed("bed", "A massive bed... you can see something glinting in the lamp light under it.");
deadSpace->addItem("bed", &bed);
bed.setLocation(deadSpace);
Item box("box", "A large wooden box");
secretHall->addItem("box", &box);
box.setLocation(secretHall);
box.addAttribute("isOpen", false);
box.addAttribute("isOpen", false);
Item door("door", "A solid wooden door is located in the north wall. You notice a small keyhole.");
secretHall->addItem("door", &door);
door.setLocation(secretHall);
door.addAttribute("isLocked", true);
door.addAttribute("isLocked", true);
Item key("key", "a small key");
deadSpace->addItem("key", &key);
key.setLocation(deadSpace);
key.addAttribute("canPickup", true);
key.addAttribute("canPickup", true);
Item lamp("lamp", "An old lamp but still looks like it might work.");
diningRoom->addItem("lamp", &lamp);
lamp.setLocation(diningRoom);
lamp.addAttribute("canPickup", true);
lamp.addAttribute("canPickup", true);
Item mansion_door("mansion_door", "The mansion door is bolted shut. You will have to find another way into the mansion.");
garden->addItem("mansion_door", &mansion_door);
mansion_door.setLocation(garden);
Item mirror("mirror", "You see your handsome, confident reflection in the mirror. This mirror could be useful.");
deadSpace->addItem("mirror", &mirror);
mirror.setLocation(deadSpace);
mirror.addAttribute("canPickup", true);
mirror.addAttribute("canPickup", true);
Item skull("skull", "A cracked human skull");
deadSpace->addItem("skull", &skull);
skull.setLocation(deadSpace);
skull.addAttribute("canPickup", true);
skull.addAttribute("canPickup", true);
Item window("window", "An old cracked window it seems to be your only access to the mansion.");
garden->addItem("window", &window);
window.setLocation(garden);
window.addAttribute("isClosed", true);
window.addAttribute("isJammed", true);
window.addAttribute("isJammed", true);
Item wrench("wrench", "An old wrench.");
inventory->addItem("wrench", &wrench);
wrench.setLocation(inventory);
wrench.addAttribute("canPickup", true);
wrench.addAttribute("isJammed", true);
wrench.addAttribute("isJammed", true);
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
cout << andy->getNumberOfItems() << "/" << andy->getMaxItems() << endl;

goto main_loop;}
if (verb == "look" || verb == "l"){
if (andy->getLocation() == tortureRoom) {
cout << "You look into the face of death and feel the scythe rip through your body. You flop over in agony and slowly die with the last thing you hear being the spectre cackling at your misfortune...";
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
cout << "I don't know how to " << verb << " here";
} else if (verb != "" && noun != "" ){
if ((toLower(noun) == toLower("bed")) && (andy->getLocation()->hasItem("bed") || andy->getInventory()->hasItem("bed"))) {
if (verb == "under" || verb == "look" || verb == "examine" || verb == "x" || verb == "ex") {
if (key.getLocation() == andy->getInventory()) {
cout << " A massive bed";
} else {
cout << "You see a key glinting under the bed.";
masterBedroom->addItem(key.getName(), &key);
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (bed.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(bed.getName())) {
cout << "You already have the ";
cout << bed.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(bed.getName(), &bed);
cout << "You pickup the ";
cout << bed.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << bed.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << bed.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(bed.getName())) {
andy->getLocation()->addItem(bed.getName(), &bed);
cout << "You drop the ";
cout << bed.getName();
} else {
cout << "I don't have ";
cout << bed.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "bed" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("box")) && (andy->getLocation()->hasItem("box") || andy->getInventory()->hasItem("box"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (box.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(box.getName())) {
cout << "You already have the ";
cout << box.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(box.getName(), &box);
cout << "You pickup the ";
cout << box.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << box.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "open") {
if (box.hasAttribute("isOpen")) {
cout << "The box is already open...";
} else {
secretHall->addItem(skull.getName(), &skull);
box.setAttribute("isOpen", true);
cout << "You open the box and discover a human skull... the body is nowhere to been seen.";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << box.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(box.getName())) {
andy->getLocation()->addItem(box.getName(), &box);
cout << "You drop the ";
cout << box.getName();
} else {
cout << "I don't have ";
cout << box.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "box" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("door")) && (andy->getLocation()->hasItem("door") || andy->getInventory()->hasItem("door"))) {
if (verb == "unlock") {
if (key.getLocation() == andy->getInventory()) {
if (door.hasAttribute("isLocked")) {
door.setAttribute("isLocked", false);
cout << "You unlock the door with the small key.";
} else {
cout << "The door is already unlocked.";
}
} else {
cout << "You do not have a key to unlock the door";
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (door.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(door.getName())) {
cout << "You already have the ";
cout << door.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(door.getName(), &door);
cout << "You pickup the ";
cout << door.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << door.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "open") {
if (door.hasAttribute("isLocked")) {
cout << "You cannot open the door it is locked.";
} else {
secretHall->setNorth(tortureRoom);
cout << "The door swings open.";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << door.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(door.getName())) {
andy->getLocation()->addItem(door.getName(), &door);
cout << "You drop the ";
cout << door.getName();
} else {
cout << "I don't have ";
cout << door.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "door" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("key")) && (andy->getLocation()->hasItem("key") || andy->getInventory()->hasItem("key"))) {
if (verb == "use") {
if (andy->getLocation() == secretHall) {
cout << "You struggle to turn the key in the old door but manage to unlock it.";
secretHall->setNorth(tortureRoom);
door.setAttribute("isLocked", false);
} else {
cout << "You can't use the key here.";
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (key.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(key.getName())) {
cout << "You already have the ";
cout << key.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(key.getName(), &key);
cout << "You pickup the ";
cout << key.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << key.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << key.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(key.getName())) {
andy->getLocation()->addItem(key.getName(), &key);
cout << "You drop the ";
cout << key.getName();
} else {
cout << "I don't have ";
cout << key.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "key" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("lamp")) && (andy->getLocation()->hasItem("lamp") || andy->getInventory()->hasItem("lamp"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (lamp.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(lamp.getName())) {
cout << "You already have the ";
cout << lamp.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(lamp.getName(), &lamp);
cout << "You pickup the ";
cout << lamp.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << lamp.getName();
cout << ", what were you thinking...";
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
entranceHall->setDescription("With light eminating from the lamp you can now make out a doorway to the north as long with the doorways to the east and west and window leading south.");entranceHall->setNorth(secretHall);
masterBedroom->setDescription("With the aid of the lamp you find yourself in an old creepy bedroom.");masterBedroom->addItem(mirror.getName(), &mirror);
masterBedroom->addItem(bed.getName(), &bed);
cout << "You fiddle around with the old lamp and manage to turn it on.";
} else {
cout << "You don't have that item.";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << lamp.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(lamp.getName())) {
andy->getLocation()->addItem(lamp.getName(), &lamp);
cout << "You drop the ";
cout << lamp.getName();
} else {
cout << "I don't have ";
cout << lamp.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "lamp" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("mansion_door")) && (andy->getLocation()->hasItem("mansion_door") || andy->getInventory()->hasItem("mansion_door"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (mansion_door.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(mansion_door.getName())) {
cout << "You already have the ";
cout << mansion_door.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(mansion_door.getName(), &mansion_door);
cout << "You pickup the ";
cout << mansion_door.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << mansion_door.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "open") {
cout << "The mansion door is bolted shut. You will have to find another way into the mansion.";
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << mansion_door.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(mansion_door.getName())) {
andy->getLocation()->addItem(mansion_door.getName(), &mansion_door);
cout << "You drop the ";
cout << mansion_door.getName();
} else {
cout << "I don't have ";
cout << mansion_door.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "mansion_door" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("mirror")) && (andy->getLocation()->hasItem("mirror") || andy->getInventory()->hasItem("mirror"))) {
if (verb == "use" || verb == "lookat" || verb == "look-at") {
if (andy->getLocation() == tortureRoom) {
cout << "You pull out out the mirror, the ghost upon seeing it's horrific reflection flees in terror. Congratulations you have busted your first ghost!";
break;
} else {
cout << "You admire yourself in the mirror.";
}
goto main_loop;}if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (mirror.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(mirror.getName())) {
cout << "You already have the ";
cout << mirror.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(mirror.getName(), &mirror);
cout << "You pickup the ";
cout << mirror.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << mirror.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << mirror.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(mirror.getName())) {
andy->getLocation()->addItem(mirror.getName(), &mirror);
cout << "You drop the ";
cout << mirror.getName();
} else {
cout << "I don't have ";
cout << mirror.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "mirror" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("skull")) && (andy->getLocation()->hasItem("skull") || andy->getInventory()->hasItem("skull"))) {
if (verb == "wear") {
if (skull.getLocation() == andy->getInventory()) {
cout << "For some perverse reason you shove the skull onto your head... Your body starts to decay and rot away, before you know it you have provided this skull with a new skeleton.";
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
if (andy->getInventory()->hasItem(skull.getName())) {
cout << "You already have the ";
cout << skull.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(skull.getName(), &skull);
cout << "You pickup the ";
cout << skull.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << skull.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << skull.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(skull.getName())) {
andy->getLocation()->addItem(skull.getName(), &skull);
cout << "You drop the ";
cout << skull.getName();
} else {
cout << "I don't have ";
cout << skull.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "skull" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("window")) && (andy->getLocation()->hasItem("window") || andy->getInventory()->hasItem("window"))) {
if (verb == "pickup" || verb == "pick-up" || verb == "get") {
if (window.hasAttribute("canPickup")) {
if (andy->getInventory()->hasItem(window.getName())) {
cout << "You already have the ";
cout << window.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(window.getName(), &window);
cout << "You pickup the ";
cout << window.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << window.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "open") {
if (window.hasAttribute("isJammed")) {
cout << "The window seems to be jammed.";
} else {
window.setAttribute("isClosed", false);
garden->setNorth(entranceHall);
cout << "The old window grates open.";
}
goto main_loop;}if (verb == "go" || verb == "climb" || verb == "enter") {
if (window.hasAttribute("isClosed")) {
cout << "You can't do that the window is closed";
} else {
andy->setLocation(entranceHall);
cout << andy->getLocation()->printNameAndDescription() << endl;
cout << andy->getLocation()->listItems();
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << window.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(window.getName())) {
andy->getLocation()->addItem(window.getName(), &window);
cout << "You drop the ";
cout << window.getName();
} else {
cout << "I don't have ";
cout << window.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "window" << "'";
goto main_loop;
}if ((toLower(noun) == toLower("wrench")) && (andy->getLocation()->hasItem("wrench") || andy->getInventory()->hasItem("wrench"))) {
if (verb == "use") {
if (andy->getLocation() == garden) {
if (wrench.getLocation() == andy->getInventory()) {
if (window.hasAttribute("isJammed")) {
window.setAttribute("isJammed", false);
cout << "You pry loose the window with the wrench. Now it can easily be opened.";
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
if (andy->getInventory()->hasItem(wrench.getName())) {
cout << "You already have the ";
cout << wrench.getName();
} else {
if (andy->canCarry()) {
andy->getInventory()->addItem(wrench.getName(), &wrench);
cout << "You pickup the ";
cout << wrench.getName();
} else {
cout << "You are carrying too much already.";
}
}
} else {
cout << "You cannont pick up the ";
cout << wrench.getName();
cout << ", what were you thinking...";
}
goto main_loop;}if (verb == "examine" || verb == "x" || verb == "ex" || verb == "look" || verb == "l") {
cout << wrench.getDescription();
goto main_loop;}if (verb == "drop" || verb == "discard" || verb == "throwout" || verb == "throw-out") {
if (andy->getInventory()->hasItem(wrench.getName())) {
andy->getLocation()->addItem(wrench.getName(), &wrench);
cout << "You drop the ";
cout << wrench.getName();
} else {
cout << "I don't have ";
cout << wrench.getName();
}
goto main_loop;}cout << "Sorry you can not '" << verb << "' on '" << "wrench" << "'";
goto main_loop;
}cout << "I can't find a " << noun << " here";
}
}
}