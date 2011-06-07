#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Compiler.h"
#include "constants.h"
#define INVENTORY_NAME "inventory"

/* Removes all white space before the string */
void ltrim(string& str) {
	string::size_type pos = 0;
	while (pos < str.size() && isspace(str[pos])) pos++;
	str.erase(0, pos);
}

/* Removes all white space after the string */
void rtrim(string& str) {
	string::size_type pos = str.size();
	while (pos > 0 && isspace(str[pos - 1])) pos--;
	str.erase(pos);
}

/* Removes all white space before and after string */
void btrim(string& str) {
	ltrim(str);
	rtrim(str);
}

/* Constructor */
Compiler::Compiler(char* filename) {
	this->parser = new Parser(filename);
	parser->ParseFile();
}

/* Compiles the user game */
void Compiler::Compile() {
	if (parser->errors.size() > 0) {
		cerr << PARSER_FAIL << endl;
		return;
	}

	if (parser->locations.count("inventory") == 0) {
		cout << NO_INVENTORY << endl;
		exit(EXIT_FAILURE);
	}

	// Setting up includes/defines
	string output =
			"#include <iostream>\n"
			"#include <cstdlib>\n"
			"#include <string>\n"
			"#include <sstream>\n"
			"#include \"Location.h\"\n"
			"#include \"Item.h\"\n"
			"#include \"Player.h\"\n"
			"using namespace std;\n"
			"#define GAME_NAME \"" + parser->gameName + "\"\n"
			"#define CREDITS \"" + parser->credits + "\"\n"
			"#define WELCOME_MESSAGE \"" + parser->initialDescription + "\"\n"
			"#define QUIT_GAME \"quit\"\n"
			"string toLower(string text);\n";

	// START OF MAIN METHOD
	output +=
			"int main(int argc, char **argv) {\n"
			"string username;\n"
			"string command;\n"
			"string verb;\n"
			"string noun;\n"
			"string prompt;\n"
			"int count;\n"
			"\n";

	// Create player
	output += "Player* " + parser->player->getVariableName() + " = new Player();\n\n";

	// Output locations
	map<string, Location*>::iterator it;
	for (it = parser->locations.begin(); it != parser->locations.end(); it++) {
		output += "Location* " + it->first + " = new Location(\"" + it->second->getName() + "\", \"" + it->second->getDescription() + "\");\n";
	}

	output += "\n";

	// Output Inventory
	//"Location* " + inventory_name + " = new Location(\"inventory\", \"Description of the inventory\");"
	output += "" + parser->player->getVariableName() + "->setLocation(" + parser->initialLocation->getVariableName() + ");"
			"" + parser->player->getVariableName() + "->setInventory(" + INVENTORY_NAME + ");"
			"" + parser->player->getVariableName() + "->setMaxItems(" + parser->player->getMaxItemsString() + ");";

	output += "\n";

	for (it = parser->locations.begin(); it != parser->locations.end(); it++) {
		Location *location = it->second;
		if (location->hasNorth()) {
			output += "" + it->first + "->setNorth(" + (location->getNorth()->getVariableName()) + ");\n";
		}
		if (location->hasSouth()) {
			output += "" + it->first + "->setSouth(" + (location->getSouth()->getVariableName()) + ");\n";
		}
		if (location->hasEast()) {
			output += "" + it->first + "->setEast(" + location->getEast()->getVariableName() + ");\n";
		}
		if (location->hasWest()) {
			output += "" + it->first + "->setWest(" + location->getWest()->getVariableName() + ");\n";
		}
	}

	output += "\n";

	//Output default attributes
	/*map<string, bool>::iterator at;
	for (at = parser->default_attribute_values.begin(); at != parser->default_attribute_values.end(); at++) {
		output += "Attribute* " + at->first + " = new Attribute(" + '"' + at->first + '"' + ");\n";
	}*/

	// Output Items
	map<string, Item*>::iterator objects;
	for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
		output += "Item " + objects->first + "(\"" + objects->second->getName() + "\", \"" + objects->second->getDescription() + "\");\n";
		output += objects->second->getLocation()->getVariableName() + "->addItem(\"" + objects->second->getName() + "\", &" + objects->first + ");\n";
		output += objects->first + ".setLocation(" + objects->second->getLocation()->getVariableName() + ");\n";

		// Add item attributes
		size_t pos;
		string temp;
		string sub;
		istringstream word(objects->second->getAttributeString());
		do {
			string sub = "";
			word >> temp;
			if (temp.find('!') != string::npos) {
				pos = temp.find('!') + 1;
				sub = temp.substr(pos);
				output += objects->first + ".addAttribute(" + '"' + temp + '"' + ", true);\n";
				output += objects->first + ".addAttribute(" + '"' + sub + '"' + ", false);\n";
			} else if (temp != ""){
				sub = "!" + temp;
				output += objects->first + ".addAttribute(" + '"' + temp + '"' + ", true);\n";
				output += objects->first + ".addAttribute(" + '"' + sub + '"' + ", false);\n";
			}
			temp = "";
		} while (word);
	}

	// START OF GAME LOOP AND WORD READING
	output +=
			"cout << endl << \"\t\t\t\" << GAME_NAME << endl;\n"
			"cout << CREDITS << endl << endl;\n"
			"cout << WELCOME_MESSAGE << endl << endl;\n"
			"prompt = \"\\n>>> \";\n"
			"cout << " + parser->player->getVariableName() + "->getLocation()->printNameAndDescription() << endl;\n"
			"cout << " + parser->player->getVariableName() + "->getLocation()->listItems();\n"
			"while (true) { \n"
			"   main_loop:\n"
			"   cout << prompt;\n"
			"   prompt = \"\\n>>> \";\n"
			"   getline(cin, command);\n"
			"   if (command == \"\") {\n"
			"		prompt = \">>> \"; \n"
			"		goto main_loop; \n"
			"	} else { \n"
			"   	prompt = \"\\n>>> \";\n"
			" 	}\n"
			"   istringstream word(command);\n"
			"   verb = \"\";\n"
			"   noun = \"\";\n"
			"   count = 0;\n"
			"   while (word) {\n"
			"      if (count > 2) {\n"
			"           cout << \"I do not understand your command. Enter 2 words at most, a verb followed by a noun\";\n"
			"           goto main_loop;\n"
			"      }\n"
			"      if (count == 0) {\n"
			"           word >> verb;\n"
			"      } else {"
			"           word >> noun;\n"
			"      }\n"
			"      count++;\n"
			"   }\n";

	//QUIT GAME METHOD
	/*output += "\
			if (command == QUIT_GAME) {\n\
			quit_loop:\n\
			string quit = \"\";\n\
			cout << \"Do you really want to quit?: [y]or[n] \";\
			getline(cin, quit);\n\
			if (quit == \"y\") {\n\
			cout << \"Thanks for playing!\" << endl;\n\
			break;\n\
			} else if (quit == \"n\") {\n\
			goto main_loop;\n\
			} else {\n\
			goto quit_loop;\n\
			}\n\
			}";*/


	// SINGLE VERB
	output += "if (verb != \"\" && noun == \"\" ) {\n";

	// VERBS
	map<string, string>::iterator iterator;
	for (iterator = parser->default_location_verb_expressions.begin(); iterator != parser->default_location_verb_expressions.end(); iterator++) {
		string verbs = getVerbSynonyms(iterator->first);
		output += "if (" + verbs + "){\n" + CompileSingleVerb(iterator->second) + "\ngoto main_loop;}\n";
	}

	// INVENTORY
	/*output += "\n\
			if ((verb == \"i\") || (verb == \"inventory\") || (verb == \"invent\")) {\n\
			cout << " + parser->player->getVariableName() + "->getInventory()->listItems() + \" \";\n\
			cout << " + parser->player->getVariableName() + "->getNumberOfItems() << \"/\" << " + parser->player->getVariableName() + "->getMaxItems() << endl;\n\
			goto main_loop;\n\
			}\n\n\
			\n";*/

	output += "cout << \"I don't know how to \" << verb << \" here\";\n";

	// SINGLE VERB END / VERB NOUN START
	output += "} else if (verb != \"\" && noun != \"\" ){\n";

	for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
		output += "if ((toLower(noun) == toLower(\"" + objects->second->getName() + "\")) && (" + parser->player->getVariableName() + "->getLocation()->hasItem(\"" + objects->second->getName() + "\") || " + parser->player->getVariableName() + "->getInventory()->hasItem(\"" + objects->second->getName() + "\"))) {\n"
				"" + CompileNounVerb(objects->second) + ""
				"goto main_loop;\n"
				"}";
	}
	output += "cout << \"I can't find a \" << noun << \" here\";\n";
	//  VERB NOUN END
	output += "}\n";

	// END OF GAME LOOP
	output += "}\n";

	// END OF MAIN METHOD
	output += "}";

	ofstream file;
	file.open("output/compiled_game.cpp", ios::out | ios::trunc);
	if (file.is_open()) {
		file << output;
		file.flush();
		file.close();
	}

}

/* Gets the item from the expression */
string Compiler::getItem(string expression) {
	string item = "";
	map<string, Item*>::iterator objects;
	for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
		istringstream word(expression);
		do {
			word >> item;
			size_t pos = item.find(';');
			if(pos != string::npos) {
				item.erase(pos, 1);
			}
			if (objects->second->getName() == item) {
				return item;
			}
		} while (word);
	}
	return "";
}

/* Gets the location from the expression */
string Compiler::getLocation(string expression) {
	string location = "";
	map<string, Location*>::iterator locations;
	for (locations = parser->locations.begin(); locations != parser->locations.end(); locations++) {
		if (expression.find(locations->first) < expression.length()) {
			location = locations->first;
			break;
		}
	}
	if (location == "") {
		if (expression.find(parser->player->getVariableName()) < expression.length()) {
			location = parser->player->getVariableName() + "->getInventory()";
		} else if (expression.find("currentLocation") < expression.length()) {
			location = parser->player->getVariableName() + "->getLocation()";
		}
	}
	return location;
}

/* Compiles a single verb from the input command */
string Compiler::CompileSingleVerb(string commands) {
	string line, output = "";
	istringstream lines(commands);
	while (getline(lines, line)) {
		btrim(line);
		output += CompileVerb(line);
	}
	return output;
}

/* Compiles the noun and verb together */
string Compiler::CompileNounVerb(Item *item) {
	map<string, string> verbs = item->getVerbs();
	map<string, string>::reverse_iterator rit;
	string line, output = "";

	// Reverse iterate so that predefined item verbs get precedence over item default verbs.
	for (rit = verbs.rbegin(); rit != verbs.rend(); rit++) {
		string data = rit->second;

		// REPLACE inputItem
		size_t pos = data.find("inputItem");
		while (pos < data.size()) {
			data.replace(pos, 9, item->getVariableName());
			pos = data.find("inputItem");
		}

		// START VERB
		string verbs = getVerbSynonyms(rit->first);
		output += "if (" + verbs + ") {\n";
		istringstream lines(data);
		while (getline(lines, line)) {
			output += CompileVerb(line);
		}

		// END VERB
		output += "goto main_loop;";
		output += "}";
	}
	output += "cout << \"Sorry you can not '\" << verb << \"' on '\" << \"" + item->getName() + "\" << \"'\";\n";
	return output;
}

/* Compiles a single verb from the input command */
string Compiler::CompileVerb(string line) {
	btrim(line);

	string output = "";
	if (line.length() > 0) {
		if (line.compare("describe;") == 0) {
			output += "cout << " + parser->player->getVariableName() + "->getLocation()->printNameAndDescription() << endl;\n";
		} else if (line.compare("describeInventory;") == 0) {
			output += "cout << \"Inventory \" << " + parser->player->getVariableName() + "->getInventory()->listItems() << \" \";\n";
			output += "cout << " + parser->player->getVariableName() + "->getNumberOfItems() << \"/\" << " + parser->player->getVariableName() + "->getMaxItems();\n";
		} else if (line.compare("list;") == 0) {
			output += "cout << " + parser->player->getVariableName() + "->getLocation()->listItems();\n";
		} else if (line.compare("gameOver;") == 0) {
			output += "break;\n";
		} else if (line.find("print \"") < line.length()) {
			size_t start, end;
			start = line.find_first_of("\"") + 1;
			end = line.find_last_of("\"");
			output += "cout << \"" + line.substr(start, end - start) + "\";\n";
		} else if (line.find("print ") < line.length()) {
			string location = getLocation(line);
			string item = getItem(line);
			if (location != "") {
				if (line.find("getDescription;") < line.length() && line.find(item) < line.length()) {
					output += "cout << " + location + "->getDescription();\n";
				} else {
					output += "cout << " + location + "->getName();\n";
				}
			} else if (item != "") {
				if (line.find("getDescription") < line.length()) {
					output += "cout << " + item + ".getDescription();\n";
				} else {
					output += "cout << " + item + ".getName();\n";
				}
			} else {
				cout << UNKNOWN_PRINT_STATEMENT << ":" << line << endl;
			}
		} else if (line.find("setDescription") < line.length()) {
			string location = getLocation(line);
			size_t start, end;
			start = line.find("\"") + 1;
			end = line.find("\"", start);
			output += location + "->setDescription(\"" + line.substr(start, end - start) + "\");";
		} else if (line.find("if") < line.length()) {
			size_t open, close;
			open = line.find("(");
			close = line.find(")");
			if (open < line.length() && close < line.length()) {
				open++;
				string expression = line.substr(open, close - open);
				if (line.find("hasItem") < line.length()) {
					string location = getLocation(expression);
					string item = getItem(expression);
					if (location == "" || item == "") {
						cout << INCOMPLETE_EXPRESSION << endl;
					} else {
						output += "if (" + location + "->hasItem(" + item + ".getName())) {\n";
					}
				} else if (line.find("hasAttribute") < line.length()) {
					string item = getItem(expression);
					size_t start, end;
					start = line.find("hasAttribute");
					end = line.find(")");
					if (line.substr(start+13, (end-start-13)).find('!') == 0) {
						output += "if (" + item + "." + "hasAttribute(" + '"' + line.substr(start+13, (end-start-13)) + '"' + ")) {\n";
					} else {
						output += "if (" + item + "." + "hasAttribute(" + '"' + line.substr(start+13, (end-start-13)) + '"' + ")) {\n";
					}
				} else if (line.find("canCarry") < line.length()) {
					if (line.find(parser->player->getVariableName()) < line.length()) {
						output += "if (" + parser->player->getVariableName() + "->canCarry()) {\n";
					} else {
						cout << BAD_CARRIABLE_EXPRESSION << endl;
					}
				} else if (line.find("inLocation") < line.length()) {
					string location = getLocation(expression);
					string item = getItem(expression);
					if (location != "" && item != "") {
						output += "if (" + item + ".getLocation() == " + location + ") {\n";
					} else if (item != "") {
						size_t pos = line.find(parser->player->getVariableName());
						if (pos < line.length()) {
							output += "if (" + parser->player->getVariableName() + "->getInventory() == " + item + ".getLocation()) {\n";
						}
					} else if (location != "") {
						if (line.find("hasNorth") < line.length()){
							output += "if (" + parser->player->getVariableName() + "->getLocation()->hasNorth()) {\n";
						} else if(line.find("hasSouth") < line.length()) {
							output += "if (" + parser->player->getVariableName() + "->getLocation()->hasSouth()) {\n";
						} else if(line.find("hasEast") < line.length()) {
							output += "if (" + parser->player->getVariableName() + "->getLocation()->hasEast()) {\n";
						} else if(line.find("hasWest") < line.length()) {
							output += "if (" + parser->player->getVariableName() + "->getLocation()->hasWest()) {\n";
						} else {
							output += "if (" + parser->player->getVariableName() + "->getLocation() == " + location + ") {\n";
						}
					} else {
						cout << BAD_INLOCATION << endl;
					}
				} else {
					cout << BAD_BOOLEAN << endl;
				}
			} else {
				cout << BAD_BRACES << endl;
			}
		} else if (line.find("else") < line.length()) {
			output += "} else {\n";
		} else if (line.find("setLocation") < line.length() && line.find("toNorth") < line.length()) {
			output += parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getNorth()); \n";
		} else if (line.find("setLocation") < line.length() && line.find("toSouth") < line.length()) {
			output += parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getSouth()); \n";
		} else if (line.find("setLocation") < line.length() && line.find("setLocation") < line.length() && line.find("toEast") < line.length()) {
			output += parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getEast()); \n";
		} else if (line.find("setLocation") < line.length() && line.find("toWest") < line.length()) {
			output += parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getWest()); \n";
		} else if (line.find("setLocation") < line.length()) {
			string location = getLocation(line);
			string item = getItem(line);
			if (location == "" && item == "") {
				cout << "Unreadable setLocation Command: \"" << line << "\"" << endl;
			} else if (line.find("setLocation") < line.length()
					&& line.find(parser->player->getVariableName()) < line.length()
					&& item == "" && location != "") {
				output += parser->player->getVariableName() + "->setLocation(" + location + ");\n";
			} else {
				output += location + "->addItem(" + item + ".getName(), &" + item + ");\n";
			}
		} else if (line.find("setNorth") < line.length() || line.find("setEast") < line.length()
				|| line.find("setWest") < line.length() || line.find("setSouth") < line.length()) {
			string location = getLocation(line);
			string command = "setNorth";
			if (line.find("setSouth") < line.length()) {
				command = "setSouth";
			} else if (line.find("setWest") < line.length()) {
				command = "setWest";
			} else if (line.find("setEast") < line.length()) {
				command = "setEast";
			}
			if (location != "") {
				size_t pos = line.find(location);
				line.replace(pos, location.length(), "");

				string location2 = getLocation(line);
				if (location != "") {
					size_t pos2 = line.find(location2);
					if (pos < pos2) {
						output += location + "->" + command + "(" + location2 + ");\n";
					} else {
						output += location2 + "->" + command + "(" + location + ");\n";
					}
				} else {
					cout << ONLY_ONE_LOCATION << endl;
				}
			} else {
				cout << NO_LOCATIONS << endl;
			}
		} else if (line.find("setAttribute") < line.length()) {
			string item = getItem(line);
			size_t start, end;
			start = line.find("setAttribute");
			end = line.find(";");
			if (line.substr(start+13, (end-start-13)).find('!') == 0) {
				output += item + ".setAttribute(" + '"' + line.substr(start+13, (end-start-13)) + '"' + ", true);\n";
				output += item + ".setAttribute(" + '"' + line.substr(start+14, (end-start-14)) + '"' + ", false);\n";
			} else {
				string sub = "!" + line.substr(start+13, (end-start-13));
				output += item + ".setAttribute(" + '"' + line.substr(start+13, (end-start-13)) + '"' + ", true);\n";
				output += item + ".setAttribute(" + '"' + sub + '"' + ", false);\n";
			}
		} else if (line.find("removeNorth") < line.length() || line.find("removeEast") < line.length()
				|| line.find("removeWest") < line.length() || line.find("removeSouth") < line.length()) {
			string location = getLocation(line);
			string command = "setNorth";
			if (line.find("removeSouth") < line.length()) {
				command = "setSouth";
			} else if (line.find("removeWest") < line.length()) {
				command = "setWest";
			} else if (line.find("removeEast") < line.length()) {
				command = "setEast";
			}
			if (location != "") {
				output += location + "->" + command + "(NULL);\n";
			} else {
				cerr << BAD_LOCATION << endl;
			}
		} else if (line.find("}") < line.length()) {
			output += "}\n";
		} else {
			cerr << UNKNOWN_COMMAND << line << "\"" << endl;
		}
	}
	return output;
}

string Compiler::getVerbSynonyms(string words) {
	string verbs = "verb == ";
	string temp;
	istringstream word(words);
	do {
		word >> temp;
		if (temp != "or" && temp != "") {
			verbs = verbs + '"' + temp + '"';
		} else if (temp != "") {
			verbs = verbs + " || verb == ";
		}
		temp = "";
	} while (word);
	return verbs;
}

Compiler::~Compiler() {

}
