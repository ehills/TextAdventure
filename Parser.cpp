#include "Parser.h"
#include "constants.h"
#include "parsetools.cpp"
#include "Player.h"

#define NEWLINE_HACK "(*-*)"

Parser::Parser(char* filename) {
	ifstream file;
	string line;
	string data;
	file.open(filename);
	if (file.is_open()) {
		while (getline(file, line)) {
			data += line;
			data += NEWLINE_HACK;
		}
		file.close();
	} else {
		cerr << FILE_DID_NOT_OPEN << endl;
		this->errors.push_front(FILE_DID_NOT_OPEN);
	}
	this->file_data = data;
}

/* Calls all methods associated with parsing the file */
list<string> Parser::ParseFile(void) {
	if (this->errors.size() == 0) {
		this->stripComments();
		this->ParseDefaults();
		this->ParsePlayer();
		this->ParseLocations();
		// Player's inventory
		inventory = new Location("inventory", "inventory", "Player's inventory.");
		this->locations.insert(pair<string, Location*>("inventory", inventory));
		this->ParseItems();
		// Check for initialLocation
		if (this->file_data.find("initialLocation") == string::npos) {
			cerr << BAD_INITIAL_LOCATION << endl;
		}
		string location_name = ParseVariableData(this->file_data, "initialLocation");
		if (this->locations.count(location_name) > 0) {
			this->initialLocation = this->locations.find(location_name)->second;
		} else {
			cerr << BAD_LOCATION << endl;
			exit (1);
		}
	}
	return this->errors;
}

/* Strips all comments from the users game */
int Parser::stripComments() {
	// Find all block comments and remove
	unsigned int start, end, size;
	start = this->file_data.find("/*");
	while (start < this->file_data.size()) {
		end = this->file_data.find("*/");
		if (end < this->file_data.size()) {
			size = (end + 2) - start;
			this->file_data.replace(start, size, "");
		} else {
			/* Find Line number and report error */
			string error_message = ERROR_UNCLOSED_COMMENT;
			this->errors.push_front(error_message);
			return this->errors.size();
		}
		start = this->file_data.find("/*");
	}

	// Remove Line Comments
	start = this->file_data.find("//");
	while (start < this->file_data.size()) {
		end = this->file_data.find(NEWLINE_HACK, start);
		size = (end + 5) - start;
		this->file_data.replace(start, size, "");
		start = this->file_data.find("//");
	}

	// Fix Newline Hack (replace with \n)
	start = this->file_data.find(NEWLINE_HACK);
	while (start < this->file_data.size()) {
		this->file_data.replace(start, 5, "\n");
		start = this->file_data.find(NEWLINE_HACK);
	}
	return NO_ERRORS;
}

/* Parses the default settings for verbs */
int Parser::ParseDefaults() {
	unsigned int start, end;
	string data;
	start = this->file_data.find("ItemDefaults");
	if (start < this->file_data.size()) {
		// Parse verb expressions
		start = this->file_data.find("{", start) + 1;
		end = ParseEndBrace(start, this->file_data);
		data = this->file_data.substr(start, end - start);
		default_verb_expressions = ParseVerbs(data);

		// Remove default data to avoid collision of items
		start = this->file_data.find("ItemDefaults");
		this->file_data.replace(start, end + 1 - start, "");
	}

	start = this->file_data.find("LocationDefaults");
	if (start < this->file_data.size()) {
		// Parse verb expressions
		start = this->file_data.find("{", start) + 1;
		end = ParseEndBrace(start, this->file_data);
		data = this->file_data.substr(start, end - start);
		default_location_verb_expressions = ParseVerbs(data);

		// Remove default data to avoid collision of items
		start = this->file_data.find("LocationDefaults");
		this->file_data.replace(start, end + 1 - start, "");

	}
	this->gameName = ParseStringData(this->file_data, "gameName", "");
	this->gameCredits = ParseStringData(this->file_data, "gameCredits", "");
	this->initialDescription = ParseStringData(this->file_data, "initialDescription", "");
	this->defaultResponse = ParseStringData(this->file_data, "defaultResponse", "You do not know how to");
	this->defaultInventoryName = ParseStringData(this->file_data, "defaultInventoryName", "Inventory: ");
	this->defaultInteractiveName = ParseStringData(this->file_data, "defaultInteractiveName", "Objects: ");
	this->defaultNoObjects = ParseStringData(this->file_data, "defaultNoObjects", "None ");
	this->restoreGameChoice = ParseStringData(this->file_data, "restoreGameChoice", "Restore Game.");
	this->restoreGameMessage = ParseStringData(this->file_data, "restoreGameMessage", "Restore game from slot 0-9.");
	this->newGameChoice = ParseStringData(this->file_data, "newGameChoice", "New Game.");
	this->saveGame = ParseStringData(this->file_data, "saveGame", "save");
	this->saveGameMessage = ParseStringData(this->file_data, "saveGameMessage", "Save game to slot 0-9.");
	this->gameSavedMessage = ParseStringData(this->file_data, "gameSavedMessage", "Game successfully saved!");
	return NO_ERRORS;
}

/* Parses all locations in the game */
int Parser::ParseLocations() {
	// Find all block comments and remove
	unsigned int start, end, size;

	// Parse the Location names first time through
	start = this->file_data.find("Location");
	while (start < this->file_data.size()) {

		if (this->file_data.at(start - 1) == 'l' || this->file_data.at(start - 1) == 'n') {
			end = start + 9;
		} else {
			end = this->file_data.find("{", start);
			if (end < this->file_data.size() && end < this->file_data.find(";", start)) {
				start += 9;
				size = (end) - start;
				// Check for Location variable name
				if (size == 0) {
					cerr << NO_LOCATION_VARIABLE_NAME << endl;
					exit (1);
				} else if (size == 1 && this->file_data.substr(start, size) == " ") {
					cerr << NO_LOCATION_VARIABLE_NAME << endl;
					exit (1);
				} else if (size > 1 && stringTrim(this->file_data.substr(start, size)) == " ") {
					cerr << NO_LOCATION_VARIABLE_NAME << endl;
					exit (1);
				}
				Location* location = new Location();
				string location_name = stringTrim(this->file_data.substr(start, size));

				location->setVariableName(location_name);
				this->file_data.replace(start, size, location_name + " ");
				this->locations[location_name] = location;
			}
		}
		if (end < this->file_data.size()) {
			start = this->file_data.find("Location", end);
		} else {
			break;
		}
	}
	// Parse the Location details second time through
	map<string, Location*>::iterator it;
	for (it = this->locations.begin(); it != this->locations.end(); it++) {
		string search = "Location " + it->first + " {";
		start = this->file_data.find(search) + search.length();
		if (start < this->file_data.size()) {
			end = ParseEndBrace(start, this->file_data);
			size = (end) - start;
			string data = this->file_data.substr(start, size);
			ParseLocation(data, it->second);
		} else {
			cout << BAD_LOCATION << endl;
		}
	}
	return NO_ERRORS;
}

/* Parse the player object */
int Parser::ParsePlayer() {
	// Find all block comments and remove
	unsigned int start, end, size;
	string attribute, data;

	// Parse the Items first time through*/
	start = this->file_data.find("Player ");
	if (start < this->file_data.size()) {
		end = this->file_data.find("{", start);
		if (end < this->file_data.size()) {
			start += 7;
			size = end - start;
			// Check for Player variable name
			if (size == 0) {
				cerr << NO_PLAYER_VARIABLE_NAME << endl;
				exit (1);
			} else if (size == 1 && this->file_data.substr(start, size) == " ") {
				cerr << NO_PLAYER_VARIABLE_NAME << endl;
				exit (1);
			} else if (size > 1 && stringTrim(this->file_data.substr(start, size)) == " ") {
				cerr << NO_PLAYER_VARIABLE_NAME << endl;
				exit (1);
			}
			player = new Player();
			attribute = stringTrim(this->file_data.substr(start, size));
			player->setVariableName(attribute);
			end++;
			data = this->file_data.substr(end, ParseEndBrace(end, this->file_data));
			attribute = ParseVariableData(data, "carryLimit");
			player->setMaxItems(atoi(attribute.c_str()));
		}
	}
	return NO_ERRORS;
}

/* Parse all items used in the game */
int Parser::ParseItems() {
	// Find all block comments and remove
	unsigned int start, end, size;
	// Parse the Items first time through
	start = this->file_data.find("Item ");
	while (start < this->file_data.size()) {
		end = this->file_data.find("{", start);
		if (end < this->file_data.size()) {
			if (this->file_data.at(start - 1) != 't') {
				start += 5;
				size = (end) - start;
				// Check for Item variable name
				if (size == 0) {
					cerr << NO_ITEM_VARIABLE_NAME << endl;
					exit (1);
				} else if (size == 1 && this->file_data.substr(start, size) == " ") {
					cerr << NO_ITEM_VARIABLE_NAME << endl;
					exit (1);
				} else if (size > 1 && stringTrim(this->file_data.substr(start, size)) == " ") {
					cerr << NO_ITEM_VARIABLE_NAME << endl;
					exit (1);
				}
				Item *item = new Item();
				string item_name = stringTrim(this->file_data.substr(start, size));
				this->file_data.replace(start, size, item_name +  " ");
				item->setVariableName(item_name);
				this->items[item_name] = item;
			}
		}
		start = this->file_data.find("Item ", end);
	}
	// Parse the Item details second time through
	map<string, Item*>::iterator it;
	for (it = this->items.begin(); it != this->items.end(); it++) {
		string search = "Item " + it->first + " {";
		start = this->file_data.find(search) + search.length();
		if (start < this->file_data.size()) {
			end = ParseEndBrace(start, this->file_data);
			size = (end) - start;
			string data = this->file_data.substr(start, size);
			ParseItem(data, it->second);
		} else {
			cout << NO_ITEM << endl;
		}
	}
	return NO_ERRORS;
}

/* Parses a location */
void Parser::ParseLocation(string data, Location *location) {
	string attribute;
	Location *link;
	unsigned int start, end;
	// Parse Name
	attribute = ParseStringData(data, "name");
	if (validAttribute(attribute)) {
		location->setName(attribute);
		start = data.find("name");
		end = data.find(";", start) + 1;
		data.replace(start, end - start, "");
	} else {
		cout << NO_LOCATION_NAME << endl;
	}
	// Parse Description
	attribute = ParseStringData(data, "description");
	if (validAttribute(attribute)) {
		location->setDescription(attribute);
		start = data.find("description");
		end = data.find(";", start) + 1;
		data.replace(start, end - start, "");
	} else {
		cout << NO_LOCATION_DESCRIPTION << ": " << location->getName() << endl;
	}
	// Parse Exits
	attribute = ParseVariableData(data, "north");
	if (validAttribute(attribute)) {
		if (this->locations.count(attribute) > 0) {
			link = this->locations.at(attribute);
			location->setNorth(link);
		} else {
			cerr << NO_JOINED_LOCATION << attribute << endl;
		}
	}
	attribute = ParseVariableData(data, "south");
	if (validAttribute(attribute)) {
		if (this->locations.count(attribute) > 0) {
			link = this->locations.at(attribute);
			location->setSouth(link);
		} else {
			cerr << NO_JOINED_LOCATION << attribute << endl;
		}
	}
	attribute = ParseVariableData(data, "east");
	if (validAttribute(attribute)) {
		if (this->locations.count(attribute) > 0) {
			link = this->locations.at(attribute);
			location->setEast(link);
		} else {
			cerr << NO_JOINED_LOCATION << attribute << endl;
		}
	}
	attribute = ParseVariableData(data, "west");
	if (validAttribute(attribute)) {
		if (this->locations.count(attribute) > 0) {
			link = this->locations.at(attribute);
			location->setWest(link);
		} else {
			cerr << NO_JOINED_LOCATION << attribute << endl;
		}
	}
	// Parse hide items
	if (data.find("hideItems;") != string::npos) {
		location->setShowItems(false);
	}
}

/* Parses a particular item */
void Parser::ParseItem(string data, Item *item) {
	string attribute;
	// Parse Name
	attribute = ParseStringData(data, "name");
	if (validAttribute(attribute)) {
		item->setName(attribute);
	} else {
		cout << NO_ITEM_NAME << endl;
	}
	// Parse Description
	attribute = ParseStringData(data, "description");
	if (validAttribute(attribute)) {
		item->setDescription(attribute);
	} else {
		cout << NO_ITEM_DESCRIPTION << endl;
	}
	// Parse location
	attribute = ParseVariableData(data, "location");
	if (attribute == this->player->getVariableName()) {
		this->locations.insert(pair<string, Location*>("inventory", inventory));
		item->setLocation(this->locations.at("inventory"));
	} else if (validAttribute(attribute)) {
		if (this->locations.count(attribute) > 0) {
			item->setLocation(this->locations.at(attribute));
		} else if (this->items.count(attribute) > 0) {
			item->setItem(this->items.at(attribute));
		} else {
			cerr << BAD_LOCATION << attribute << endl;
			exit (1);
		}
	} else {
		cerr << NO_ITEM_LOCATION << endl;
	}

	// Parse verbs
	item->addVerbs(this->default_verb_expressions);
	item->addVerbs(ParseVerbs(data));

	// Parse attributes
	attribute = ParseVariableData(data, "hasAttributes");
	if (validAttribute(attribute)) {
		item->setAttributeString(attribute);
	}
	// Parse hide items
	if (data.find("hideItems;") != string::npos) {
		item->setShowItems(false);
	}
}

Parser::~Parser() {
	map<string, Location*>::iterator locations;
	for (locations = this->locations.begin(); locations != this->locations.end(); locations++) {
		delete locations->second;
	}
	map<string, Item*>::iterator objects;
	for (objects = this->items.begin(); objects != this->items.end(); objects++) {
		delete objects->second;
	}
	delete this->player;
}
