#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Compiler.h"
//#define INVENTORY_NAME "a_name_no_one_would_pick_ever_to_avoid_variable_names_overlapping"
#define INVENTORY_NAME "inventory"

void ltrim(string& str) {
    string::size_type pos = 0;
    while (pos < str.size() && isspace(str[pos])) pos++;
    str.erase(0, pos);
}

void rtrim(string& str) {
    string::size_type pos = str.size();
    while (pos > 0 && isspace(str[pos - 1])) pos--;
    str.erase(pos);
}

void btrim(string& str) {
    ltrim(str);
    rtrim(str);
}

/* Constructor */
Compiler::Compiler(char* filename) {
    this->parser = new Parser(filename);
    parser->ParseFile();
}

void Compiler::Compile() {
    string inventory_name = INVENTORY_NAME;


    // Setting up includes/defines
    string output = "\
#include <iostream>\n\
#include <cstdlib>\n\
#include <string>\n\
#include <sstream>\n\
#include \"Location.h\"\n\
#include \"Item.h\"\n\
#include \"Player.h\"\n\
using namespace std;\n\
#define WELCOME_MESSAGE \"" + parser->initialDescription + "\"\n\
#define QUIT_GAME \"quit\"\n";

    // START OF MAIN METHOD        
    output += "\
int main(int argc, char **argv) {\n\
    string username;\n\
    string command;\n\
    string verb;\n\
    string noun;\n\
    string prompt;\n\
    int count;\n\
    \n";


    // Output locations  
    map<string, Location*>::iterator it;

    for (it = parser->locations.begin(); it != parser->locations.end(); it++) {
        output += "Location " + it->first + "(\"" + it->second->getName() + "\", \"" + it->second->getDescription() + "\");\n";
    }

    output += "\n";


    for (it = parser->locations.begin(); it != parser->locations.end(); it++) {
        Location *location = it->second;
        if (location->hasNorth()) {
            output += "" + it->first + ".setNorth(&" + (location->getNorth()->getVariableName()) + ");\n";
        }
        if (location->hasSouth()) {
            output += "" + it->first + ".setSouth(&" + (location->getSouth()->getVariableName()) + ");\n";
        }
        if (location->hasEast()) {
            output += "" + it->first + ".setEast(&" + location->getEast()->getVariableName() + ");\n";
        }
        if (location->hasWest()) {
            output += "" + it->first + ".setWest(&" + location->getWest()->getVariableName() + ");\n";
        }
    }

    // Output Player/Inventory
    output += "Location " + inventory_name + "(\"Inventory\", \"Description of the inventory\");"
            "Player* " + parser->player->getVariableName() + " = new Player();"
            "" + parser->player->getVariableName() + "->setLocation(&" + parser->initialLocation->getVariableName() + ");"
            "" + parser->player->getVariableName() + "->setInventory(&" + inventory_name + ");"
            "" + parser->player->getVariableName() + "->setMaxItems(" + parser->player->getMaxItemsString() + ");";

    // Output Items
    map<string, Item*>::iterator objects;
    for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
        output += "Item " + objects->first + "(\"" + objects->second->getName() + "\", \"" + objects->second->getDescription() + "\");\n";
        output += objects->second->getLocation()->getVariableName() + ".addItem(\"" + objects->second->getName() + "\", &" + objects->first + ");\n";
        output += objects->first + ".setLocation(&" + objects->second->getLocation()->getVariableName() + ");\n";
    }

    // START OF GAME LOOP AND WORD READING
    output += ""
            "cout << WELCOME_MESSAGE << endl;"
            "prompt = \"\\n>>> \";"
            "cout << " + parser->player->getVariableName() + "->getLocation()->getDescription() << endl;"
            "while (true) {"
            "   main_loop:"
            "   cout << prompt;"
            "   getline(cin, command);"
            "   istringstream word(command);"
            "   verb = \"\";"
            "   noun = \"\";"
            "   count = 0;"
            "   while (word) {"
            "      if (count > 2) {"
            "           cout << \"I do not understand your command. Enter 2 words at most, a verb followed by a noun\" << endl;"
            "           goto main_loop;"
            "      }"
            "      if (count == 0) {"
            "           word >> verb;"
            "      } else {"
            "           word >> noun;"
            "      }"
            "      count++;"
            "   }";

    //QUIT GAME METHOD
    output += "\
    if (command == QUIT_GAME) {\n\
        quit_loop:\n\
        string quit = \"\";\n\
        cout << \"Do you really want to quit?: [y]or[n] \";\
        cout.flush();\n\
	cin >> quit;\n\
	cin.ignore();\n\
	if (quit == \"y\") {\n\
        	cout << \"Thanks for playing!\" << endl;\n\
                break;\n\
	} else if (quit == \"n\") {\n\
                goto main_loop;\n\
	} else {\n\
		goto quit_loop;\n\
	}\n\
    }";


    // SINGLE VERB 
    output += "\
    if (count == 2) {\n";

    // DIRECTIONS 
    output += "\n\
        if ((verb == \"i\") || (verb == \"inventory\") || (verb == \"invent\")) {\n\
                cout << " + parser->player->getVariableName() + "->getInventory()->listItems() << endl;\n\
                cout << " + parser->player->getVariableName() + "->getNumberOfItems() << \"/\" << " + parser->player->getVariableName() + "->getMaxItems() << endl;\n\
                goto main_loop;\n\
        }\n\n\
        if(verb==\"north\") {\n\
            if (!" + parser->player->getVariableName() + "->getLocation()->hasNorth()) {\n\
                cout << \"Sorry you can not go North\" << endl;\n\
                goto main_loop;\n\
            } else {\n\
                " + parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getNorth());\n\
                cout << " + parser->player->getVariableName() + "->getLocation()->getDescription() << endl;\n\
                goto main_loop;\n\
            }\n\
        }\n\n\
        if(verb==\"south\") {\n\
            if (!" + parser->player->getVariableName() + "->getLocation()->hasSouth()) {\n\
                cout << \"Sorry you can not go South\" << endl;\n\
                goto main_loop;\n\
            } else {\n\
                " + parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getSouth());\n\
                cout << " + parser->player->getVariableName() + "->getLocation()->getDescription() << endl;\n\
                goto main_loop;\n\
            }\n\
        }\n\n\
        if(verb==\"west\") {\n\
            if (!" + parser->player->getVariableName() + "->getLocation()->hasWest()) {\n\
                cout << \"Sorry you can not go West\" << endl;\n\
                goto main_loop;\n\
            } else {\n\
                " + parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getWest());\n\
                cout << " + parser->player->getVariableName() + "->getLocation()->getDescription() << endl;\n\
                goto main_loop;\n\
            }\n\
        }\n\
        if(verb==\"east\") {\n\
            if (!" + parser->player->getVariableName() + "->getLocation()->hasEast()) {\n"
            "                cout << \"Sorry you can not go East\" << endl;\n\
                goto main_loop;\n\
            } else {\n\
                " + parser->player->getVariableName() + "->setLocation(" + parser->player->getVariableName() + "->getLocation()->getEast());\n\
                cout << " + parser->player->getVariableName() + "->getLocation()->getDescription() << endl;\n\
                goto main_loop;\n\
            }\n\
        }";

    // VERBS
    map<string, string>::iterator iterator;
    for (iterator = parser->default_location_verb_expressions.begin(); iterator != parser->default_location_verb_expressions.end(); iterator++) {
        output += "if (verb==\"" + iterator->first + "\"){\n" + CompileSingleVerb(iterator->second) + "\ngoto main_loop;}\n";
    }


    output += "cout << \"I don't know how to \" << verb << \" here\" << endl;\n";

    // SINGLE VERB END / VERB NOUN START
    output += "} else {\n";

    for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
        output += "if (" + parser->player->getVariableName() + "->getLocation()->hasItem(\"" + objects->second->getName() + "\") || " + parser->player->getVariableName() + "->getInventory()->hasItem(\"" + objects->second->getName() + "\")) {\n"
                "" + CompileNounVerb(objects->second) + ""
                "goto main_loop;\n"
                "}";
    }
    output += "cout << \"I can't find a \" << noun << \" here\" << endl;\n";
    //  VERB NOUN END
    output += "}\n";

    // END OF GAME LOOP             
    output += "}\n";

    // END OF MAIN METHOD            
    output += "}";
    
    ofstream file;
    file.open("output/compiled_game.cpp", ios::out|ios::trunc);
    if (file.is_open()) {
        file << output;
        file.flush();
        file.close();
    }

}

string Compiler::getItem(string expression) {
    string item = "";
    map<string, Item*>::iterator objects;
    for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
        if (expression.find(objects->first) < expression.length()) {
            item = objects->first;
            break;
        }
    }
    return item;
}

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

string Compiler::CompileSingleVerb(string commands) {
    string line, output = "";
    istringstream lines(commands);
    while (getline(lines, line)) {
        btrim(line);
        if (line.length() > 0) {
            if (line.compare("describe;") == 0) {
                output += "cout << " + parser->player->getVariableName() + "->getLocation()->getDescription() << endl;\n";
            } else if (line.compare("list;") == 0) {
                output += "cout << " + parser->player->getVariableName() + "->getLocation()->listItems() << endl;\n";
            } else if (line.compare("gameOver;") == 0) {
                output += "break;\n";
            } else if (line.find("print ") < line.length()) {
                size_t start, end;
                start = line.find_first_of("\"") + 1;
                end = line.find_last_of("\"");
                output += "cout << \"" + line.substr(start, end - start) + "\" << endl;\n";
            } else {
                cerr << "Unreadable/Unknown Command: \"" << line << "\"" << endl;
            }
        }
    }
    return output;
}

string Compiler::CompileNounVerb(Item *item) {
    map<string, string> verbs = item->getVerbs();
    map<string, string>::iterator it;
    string line, output = "";
    for (it = verbs.begin(); it != verbs.end(); it++) {
        string data = it->second;

        // REPLACE inputItem
        size_t pos = data.find("inputItem");
        while (pos < data.size()) {
            data.replace(pos, 9, item->getVariableName());
            pos = data.find("inputItem");
        }

        // START VERB
        output += "if (verb == \"" + it->first + "\") {\n";
        istringstream lines(data);
        while (getline(lines, line)) {
            btrim(line);
            if (line.length() > 0) {
                if (line.compare("describe;") == 0) {
                    output += "cout << " + parser->player->getVariableName() + "->getLocation()->getDescription() << endl;\n";
                } else if (line.compare("list;") == 0) {
                    output += "cout << " + parser->player->getVariableName() + "->getLocation()->listItems() << endl;\n";
                } else if (line.compare("gameOver;") == 0) {
                    output += "break;\n";
                } else if (line.find("print \"") < line.length()) {
                    size_t start, end;
                    start = line.find_first_of("\"") + 1;
                    end = line.find_last_of("\"");
                    output += "cout << \"" + line.substr(start, end - start) + "\";\n";
                } else if (line.find("print ") < line.length()) {
                    string object = getLocation(line);
                    if (object != "") {
                        object = getItem(line);
                    }
                    if (object != "") {
                        if (line.find(".description()") < line.length()) {
                            output += "cout << " + object + ".getName() << endl;\n";
                        } else {
                            output += "cout << " + object + ".getDescription() << endl;\n";
                        }
                    }
                    // ERROR UNKNOWN PRINT STATEMENT

                } else if (line.find("setDescription") < line.length()) {
                    string location = getLocation(line);
                    size_t start, end;
                    start = line.find("\"") + 1;
                    end = line.find("\"", start);
                    output += location + ".setDescription(\"" + line.substr(start, end - start) + "\");";
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
                                // BAD EXPRESSION
                            } else {
                                output += "if (" + location + "->hasItem(" + item + ".getName())) {\n";
                            }
                        } else if (line.find("canCarry") < line.length()) {
                            if (line.find(parser->player->getVariableName()) < line.length()) {
                                output += "if (" + parser->player->getVariableName() + "->canCarry()) {\n";
                            } else {
                                // BAD CAN CARRY EXPRESSION
                            }
                        } else if (line.find("inLocation") < line.length()) {
                            string location = getLocation(expression);
                            string item = getItem(expression);
                            if (location == "" && item == "") {
                                 output += "if (" + item + "->getLocation() == &" + location +") {\n";
                            } else if (location == "") {
                                size_t pos = line.find(parser->player->getVariableName());
                                if (pos < line.length()) {
                                    output += "if (" + parser->player->getVariableName() + "->getInventory() == " + item + ".getLocation()) {\n";
                                }
                            } else if (item == "") {
                                size_t pos = line.find(parser->player->getVariableName());
                                if (pos < line.length()) {
                                    output += "if (" + parser->player->getVariableName() + "->getLocation() == &" + location +") {\n";
                                }
                            } else {
                               // BAD INLOCATION BOOLEAN
                            }
                        } else {
                            //ERROR BAD BOOLEAN
                        }
                    } else {
                        // ERROR BAD BRACES
                    }
                } else if (line.find("else") < line.length()) {
                    output += "} else {";
                } else if (line.find("setLocation") < line.length()) {
                    string location = getLocation(line);
                    string item = getItem(line);

                    if (location == "" || item == "") {
                        cerr << "Unreadable setLocation Command: \"" << line << "\"" << endl;
                    } else {
                        output += location + "->addItem(" + item + ".getName(), &" + item + ");\n";
                    }
                } else if (line.find("setNorth") < line.length() || line.find("setEast") < line.length() 
                        || line.find("setWest") < line.length() || line.find("setSouth") < line.length()) {
                    cerr << "Set" << endl;
                    string location = getLocation(line);
                    string command = "setNorth";
                    if (line.find("setSouth") < line.length()) {
                        command = "setSouth";
                    } else if (line.find("setWest") < line.length()) {
                        command = "setWest";
                    }  else if (line.find("setEast") < line.length()) {
                        command = "setEast";
                    } 
                    if (location == "") {
                        size_t pos = line.find(location);
                        line.replace(pos, location.length(), "");

                        string location2 = getLocation(line);
                        if (location == "") {
                            size_t pos2 = line.find(location2);
                            if (pos < pos2) {
                                cerr << "aSDASASDASD" << endl;
                                output += location + "->" + command + "(&" + location2 + ");\n";
                            } else {
                                cerr << "ADSADSADASDASDASDAS" << endl;
                                output += location2 + "->" + command + "(&" + location + ");\n";
                            }
                        } else {
                             cerr << "ONE LOCATION" << endl;
                            // ERROR ONLY ONE LOCATION
                        }
                    } else {
                        cerr << "NO LOCATION" << endl;
                        // ERROR ONLY NO LOCATIONS
                    }
                } else if (line.find("removeNorth") < line.length() || line.find("removeEast") < line.length() 
                        || line.find("removeWest") < line.length() || line.find("removeSouth") < line.length()) {
                    cerr << "Remove" << endl;
                    string location = getLocation(line);
                    string command = "setNorth";
                    if (line.find("removeNorth") < line.length()) {
                        command = "setSouth";
                    } else if (line.find("removeWest") < line.length()) {
                        command = "setWest";
                    }  else if (line.find("removeEast") < line.length()) {
                        command = "setEast";
                    } 
                    if (location == "") {
                        output += location + "->" + command + "(NULL);\n";
                    } else {
                        cerr << "NO LOCATION" << endl;
                    }
                } else if (line.find("}") < line.length()) {
                    output += "}\n";
                } else {
                    cerr << "Unreadable/Unknown Command: \"" << line << "\"" << endl;
                }
            }
        }
        // END VERB
        output += "goto main_loop;";
        output += "}\n";
    }
    output += "cout << \"Sorry you can not \" << verb << \"on\" << \"" + item->getName() + "\" << endl;\n";
    return output;
}

Compiler::~Compiler() {

}
