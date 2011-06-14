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
			"#define CREDITS \"" + parser->gameCredits + "\"\n"
			"#define WELCOME_MESSAGE \"" + parser->initialDescription + "\"\n"
			"#define DEFAULT_RESPONSE \"" + parser->defaultResponse + "\"\n"
			"string toLower(string text);\n";

	// Start of main method
	output +=
			"int main(int argc, char **argv) {\n"
			"string username;\n"
			"string command;\n"
			"string command_word;\n"
			"string verb;\n"
			"string noun;\n"
			"string join;\n"
			"string second_noun;\n"
			"string prompt;\n"
			"int count;\n"
			"\n";

	// Create player
	output += "Player* " + parser->player->getVariableName() + " = new Player();\n\n";

	// Output locations
	map<string, Location*>::iterator it;
	for (it = parser->locations.begin(); it != parser->locations.end(); it++) {
		output += "Location* " + it->first + " = new Location(\"" + it->second->getName() + "\", \"" + it->second->getDescription() + "\", \"" + it->second->getVariableName() + "\");\n";
	}

	output += "\n";
	string inventory_name = INVENTORY_NAME;

	// Initialise Inventory
	output +=	"" + parser->player->getVariableName() + "->setLocation(" + parser->initialLocation->getVariableName() + ");"
			"" + parser->player->getVariableName() + "->setInventory(" + inventory_name + ");"
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

	// Output default attributes
	/*map<string, bool>::iterator at;
	for (at = parser->default_attribute_values.begin(); at != parser->default_attribute_values.end(); at++) {
		output += "Attribute* " + at->first + " = new Attribute(" + '"' + at->first + '"' + ");\n";
	}*/

	// Output Items
	map<string, Item*>::iterator objects;
	for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
		output += "Item " + objects->first + "(\"" + objects->second->getName() + "\", \"" + objects->second->getDescription() + "\", \"" + objects->second->getVariableName() + "\");\n";
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

	// Start of game loop and word reading
	output +=
			"cout << endl << \"\t\t\t\" << GAME_NAME << endl;\n"
			"cout << CREDITS << endl << endl;\n"
			"cout << WELCOME_MESSAGE << endl << endl;\n"
			"prompt = \"\\n>>> \";\n"
			"cout << " + parser->player->getVariableName() + "->getLocation()->printNameAndDescription() << endl;\n"
			"cout << " + parser->player->getVariableName() + "->getLocation()->listItems();\n"
			"\nwhile (true) { \n"
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
			"   command_word = \"\";\n"
			"   verb = \"\";\n"
			"   noun = \"\";\n"
			"   join = \"\";\n"
			"   second_noun = \"\";\n"
			"   count = 0;\n"
			"   do {\n"
			"      word >> command_word;\n"
			"      if (count == 0 && command_word != \"\") {\n"
			"           verb = command_word;\n"
			"           count++;\n"
			"      } else if (count == 1 && command_word != \"\") {\n"
			"           noun = command_word;\n"
			"           count++;\n"
			"      } else if (count == 2 && command_word != \"\") {\n"
			"           join = command_word;\n"
			"           count++;\n"
			"      } else if (count == 3 && command_word != \"\") {\n"
			"           second_noun = command_word;\n"
			"           count++;\n"
			"      } else if (count == 4 && command_word != \"\") {\n"
			"           count++;\n"
			"           break;\n"
			"      }\n"
			"      command_word = \"\";\n"
			"    } while (word);\n\n"
			"if (count == 3 || count > 4) {\n"
			"   cout << DEFAULT_RESPONSE << \" \" << command << \" here.\";\n"
			"	goto main_loop;\n"
			"}\n\n";

	// Single verb
	output += "if (count == 1) {\n\n";
	map<string, string>::iterator iterator;
	for (iterator = parser->default_location_verb_expressions.begin(); iterator != parser->default_location_verb_expressions.end(); iterator++) {
		string verbs = getSynonyms(iterator->first, "verb");
		output += "if (" + verbs + "){\n" + CompileSingleVerb(iterator->second) + "\ngoto main_loop;\n}\n";
	}

	// Verb and noun
	output += "} else if (count == 2){\n\n";
	for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
		output += "if ((" + parser->player->getVariableName() + "->getLocation()->getVariableName() == " + objects->second->getVariableName() + ".getLocation()->getVariableName()" + " "
				"|| " + parser->player->getVariableName() + "->getInventory()->hasItem(\"" + objects->second->getVariableName() + "\")) " +
				"&& (toLower(noun) == toLower(\"" + objects->second->getName() + "\"))) {\n"
				"" + CompileVerbNoun(objects->second) + ""
				"}\n\n";
	}

	// Verb, noun, join and noun
	output += "} else if (count == 4){\n\n";
	for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
		output += CompileVerbNounJoin(objects->second);
	}

	// End Verb, noun, join and noun
	output += "}\n";

	// Response to not knowing a command
	output += "cout << DEFAULT_RESPONSE << \" \" << command << \" here.\";\n\n";

	// End of game loop
	output += "}\n";

	// End of main method
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
			if (objects->second->getVariableName() == item) {
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
string Compiler::CompileVerbNoun(Item *item) {
	map<string, string> verbs = item->getVerbs();
	map<string, string>::reverse_iterator rit;
	string line, output = "";

	// Reverse iterate so that predefined item verbs get precedence over item default verbs.
	for (rit = verbs.rbegin(); rit != verbs.rend(); rit++) {
		string data = rit->second;

		// Replace inputItem
		size_t pos = data.find("inputItem");
		while (pos < data.size()) {
			data.replace(pos, 9, item->getVariableName());
			pos = data.find("inputItem");
		}

		// Make sure verb and noun pattern is not a verb, noun and join pattern.
		size_t found_join, found_item;
		found_join = rit->first.find("Join:");
		found_item = rit->first.find("Item:");
		if (found_join == string::npos && found_item == string::npos) {
			// Start verb
			string verbs = getSynonyms(rit->first, "verb");
			output += "if (" + verbs + ") {\n";
			istringstream lines(data);
			while (getline(lines, line)) {
				output += CompileVerb(line);
			}
			// End verb
			output += "goto main_loop;";
			output += "\n}\n";
		}
	}
	return output;
}

/* Compiles the verb, noun, join and noun pattern */
string Compiler::CompileVerbNounJoin(Item *item) {
	map<string, string> verbs = item->getVerbs();
	map<string, string>::reverse_iterator rit;
	string line, output = "";
	string object;

	// Reverse iterate so that predefined item verbs get precedence over item default verbs.
	for (rit = verbs.rbegin(); rit != verbs.rend(); rit++) {
		string data = rit->second;
		// Replace inputItem
		size_t pos = data.find("inputItem");
		while (pos < data.size()) {
			data.replace(pos, 9, item->getVariableName());
			pos = data.find("inputItem");
		}

		// Make sure verb is a verb, noun, join and noun pattern.
		size_t found_join, found_item;
		found_join = rit->first.find("Join:");
		found_item = rit->first.find("Item:");
		if (found_join != string::npos && found_item != string::npos) {
			// Start verb
			size_t start, end;
			start = rit->first.find("Join:");
			end = rit->first.find("Item:")-2;
			string joins = getSynonyms(rit->first.substr(start+6, end - start - 5), "join");
			string verbs = getSynonyms(rit->first.substr(0,start-1), "verb");
			object = rit->first.substr(end+8);
			string condition = "(" + verbs + ") && (" + joins + ")";
			output += "if (" + condition + " && " + object + ".getName() ==  second_noun) {\n";
			istringstream lines(data);
			while (getline(lines, line)) {
				output += CompileVerb(line);
			}
			// End verb
			output += "\n}\n";
			output += "goto main_loop;";
			output = "if ((" + parser->player->getVariableName() + "->getLocation()->getVariableName() == " + item->getVariableName() + ".getLocation()->getVariableName()" + " "
					"|| " + parser->player->getVariableName() + "->getInventory()->hasItem(\"" + item->getVariableName() + "\")) " +
					"&& (toLower(noun) == toLower(\"" + item->getName() + "\"))) {\n"
					"" + output + "\n";
		}
	}
	return output;
}

/* Compiles the verb expressions */
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
				if (line.find("getDescription") < line.length() && line.find(item) < line.length()) {
					output += "cout << " + location + "->getDescription();\n";
				} else {
					output += "cout << " + location + "->getName() << \".\";\n";
				}
			} else if (item != "") {
				if (line.find("getDescription") < line.length()) {
					output += "cout << " + item + ".getDescription();\n";
				} else {
					output += "cout << " + item + ".getName() << \".\";\n";
				}
			} else {
				cout << UNKNOWN_PRINT_STATEMENT << ":" << line << endl;
			}
		} else if (line.find("setDescription") < line.length()) {
			string location = getLocation(line);
			string item = getItem(line);
			size_t start, end;
			start = line.find("\"") + 1;
			end = line.find("\"", start);
			if (location != "") {
				output += location + "->setDescription(\"" + line.substr(start, end - start) + "\");";
			} else {
				output += item + ".setDescription(\"" + line.substr(start, end - start) + "\");";
			}
		} else if (line.find("if") < line.length()) {
			size_t open, close;
			open = line.find("(");
			close = line.find(")");
			if (open < line.length() && close < line.length()) {
				open++;
				string expression = line.substr(open, close - open);
				if (expression.find("hasItem") < expression.length()) {
					string location = getLocation(expression);
					string item = getItem(expression);
					if (location == "" || item == "") {
						cout << INCOMPLETE_EXPRESSION << endl;
					} else {
						output += "if (" + location + "->hasItem(" + item + ".getVariableName())) {\n";
					}
				} else if (expression.find("isItem") < expression.length()) {
					size_t start, end;
					string item = getItem(expression);
					start = expression.find("isItem") + 7;
					end = expression.find(")");
					string other_item = expression.substr(start, end - start);
					output += "if (" + item + "." + "getVariableName() == " + other_item + "." + "getVariableName()) {\n";
				} else if (expression.find("hasAttribute") < expression.length()) {
					string item = getItem(expression);
					size_t start, end;
					start = expression.find("hasAttribute");
					end = expression.find(")");
					if (expression.substr(start+13, (end-start-13)).find('!') == 0) {
						output += "if (" + item + "." + "hasAttribute(" + '"' + expression.substr(start+13, (end-start-13)) + '"' + ")) {\n";
					} else {
						output += "if (" + item + "." + "hasAttribute(" + '"' + expression.substr(start+13, (end-start-13)) + '"' + ")) {\n";
					}
				} else if (expression.find("canCarry") < expression.length()) {
					if (expression.find(parser->player->getVariableName()) < expression.length()) {
						output += "if (" + parser->player->getVariableName() + "->canCarry()) {\n";
					} else {
						cout << BAD_CARRIABLE_EXPRESSION << endl;
					}
				} else if (expression.find("inLocation") < expression.length()) {
					string location = getLocation(expression);
					string item = getItem(expression);
					if (location != "" && item != "") {
						output += "if (" + item + ".getLocation() == " + location + ") {\n";
					} else if (item != "") {
						size_t pos = expression.find(parser->player->getVariableName());
						if (pos < expression.length()) {
							output += "if (" + parser->player->getVariableName() + "->getInventory() == " + item + ".getLocation()) {\n";
						}
					} else if (location != "") {
						if (expression.find("hasNorth") < expression.length()){
							output += "if (" + parser->player->getVariableName() + "->getLocation()->hasNorth()) {\n";
						} else if(expression.find("hasSouth") < expression.length()) {
							output += "if (" + parser->player->getVariableName() + "->getLocation()->hasSouth()) {\n";
						} else if(expression.find("hasEast") < expression.length()) {
							output += "if (" + parser->player->getVariableName() + "->getLocation()->hasEast()) {\n";
						} else if(expression.find("hasWest") < expression.length()) {
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

string Compiler::getSynonyms(string words, string type) {
	string synonyms = type + " == ";
	string temp;
	istringstream word(words);
	do {
		word >> temp;
		if (temp != "or" && temp != "") {
			synonyms +=  '"' + temp + '"';
		} else if (temp != "") {
			synonyms += " || " + type + " == ";
		}
		temp = "";
	} while (word);
	return synonyms;
}

Compiler::~Compiler() {
}
