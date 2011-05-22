#include <sstream>
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
            "" + parser->player->getVariableName() + "->setMaxItems(" + "8" + ");";

    // Output Items
    map<string, Item*>::iterator objects;
    for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
        output += "Item " + objects->first + "(\"" + objects->second->getName() + "\", \"" + objects->second->getDescription() + "\");\n";
        output += "// " +objects->first + ".setLocation(&" + objects->second->getLocation()->getVariableName() + ");\n";
        output += objects->second->getLocation()->getVariableName() + ".addItem(\"" + objects->second->getName() + "\", " + objects->first + ");\n";
    }

    // START OF GAME LOOP AND WORD READING
    output += ""
            "cout << WELCOME_MESSAGE << endl;"
            "prompt = \">>> \";"
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
                cout << " + parser->player->getVariableName() + "->getInventory()->listItems();\n\
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
                "cerr << \"hit object in room\" << endl;\n"
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
    cout << output << endl;

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
        output += "cerr << \"DOING " + it->first + "\" << endl;\n";
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
                } else if (line.find("print " + item->getVariableName()) < line.length()) {
                    output += "cout << " + item->getVariableName();
                    if (line.find(".description()") < line.length()) {
                        output += ".getDescription()";
                    } else {
                        output += ".getName()";
                    }
                    output += ";\n";
                }  else if (line.find("setLocation") < line.length()) {
                    string location, item = "";
                    map<string, Item*>::iterator objects;
                    for (objects = parser->items.begin(); objects != parser->items.end(); objects++) {
                        if (line.find(objects->first) < line.length()) {
                            item = objects->first;
                            break;  
                        }
                    }
                    map<string, Location*>::iterator locations;
                    for (locations = parser->locations.begin(); locations != parser->locations.end(); locations++) {
                        if (line.find(locations->first) < line.length()) {
                            location = locations->first;
                            break;  
                        }
                    }
                    if (location == "") {
                        if (line.find(parser->player->getVariableName()) < line.length()) {
                            location = parser->player->getVariableName() + "->getInventory()";
                        } else if (line.find("currentLocation") < line.length()) {
                            location = parser->player->getVariableName() + "->getLocation()";  
                        }
                    }
                    if (location == "" || item == "") {
                        cerr << "Unreadable setLocation Command: \"" << line << "\"" << endl;
                    } else {
                        cerr << location << "->addItem(" << item << ".getName(), " << item << ");\n";
                        output += location + "->addItem(" + item + ".getName(), " + item + ");\n";
                    }
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
