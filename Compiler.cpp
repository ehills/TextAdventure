#include "Compiler.h"
//#define INVENTORY_NAME "a_name_no_one_would_pick_ever_to_avoid_variable_names_overlapping"
#define INVENTORY_NAME "inventory"

/* Constructor */
Compiler::Compiler() {
}

void Compiler::Compile(char* filename) {
    Parser* parser = new Parser(filename);
    parser->ParseFile();
    string inventory_name = INVENTORY_NAME;


    // Setting up includes/defines
    string output = "\
#include <iostream>\n\
#include <cstdlib>\n\
#include <string>\n\
#include <sstream>\n\
#include \"Location.h\"\n\
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
        output += "\tLocation " + it->first + "(\"" + it->second->getName() + "\", \"" + it->second->getDescription() + "\");\n";
    }

    output += "\n";


    for (it = parser->locations.begin(); it != parser->locations.end(); it++) {
        Location *location = it->second;
        if (location->hasNorth()) {
            output += "\t" + it->first + ".setNorth(&" + (location->getNorth()->getVariableName()) + ");\n";
        }
        if (location->hasSouth()) {
            output += "\t" + it->first + ".setSouth(&" + (location->getSouth()->getVariableName()) + ");\n";
        }
        if (location->hasEast()) {
            output += "\t" + it->first + ".setEast(&" + location->getEast()->getVariableName() + ");\n";
        }
        if (location->hasWest()) {
            output += "\t" + it->first + ".setWest(&" + location->getWest()->getVariableName() + ");\n";
        }
    }

    // Output Player/Inventory
    output += "\n\
    Location " + inventory_name + "(\"Inventory\", \"Description of the inventory\");\n\
    Player* player = new Player();\n\
    player->setLocation(&" + parser->initialLocation->getVariableName() + ");\
    player->setInventory(" + inventory_name + ");\n\
    player->setMaxItems(" + "8" + ");\n";


    // START OF GAME LOOP AND WORD READING
    output += "\
    cout << WELCOME_MESSAGE << endl;\n\n\
    prompt = \">>> \";\n\
    \n\
    cout << player->getLocation()->getDescription() << endl;\n\
    while (true) {\n\
        main_loop:\n\
        cout << prompt;\n\
        getline(cin, command);\n\
        istringstream word(command);\n\
        verb = \"\";\n\
        noun = \"\";\n\
        count = 0;\n\
        while (word) {\n\
            if (count > 2) {\n\
            cout << \"I do not understand your command. Enter 2 words at most, a verb followed by a noun\" << endl;\n\
            goto main_loop;\n\
            }\n\
            if (count == 0) {\n\
            word >> verb;\n\
            } else {\n\
            word >> noun;\n\
            }\n\
            count++;\n\
        }\n";

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
        
    
    // DIRECTIONS 
    output += "\
    if (count == 2) {\n\
        if(verb==\"north\") {\n\
            if (!player->getLocation()->hasNorth()) {\n\
                cout << \"Sorry you can not go North\" << endl;\n\
                goto main_loop;\n\
            } else {\n\
                player->setLocation(player->getLocation()->getNorth());\n\
                cout << player->getLocation()->getDescription() << endl;\n\
                goto main_loop;\n\
            }\n\
        }\n\n\
        if(verb==\"south\") {\n\
            if (!player->getLocation()->hasSouth()) {\n\
                cout << \"Sorry you can not go South\" << endl;\n\
                goto main_loop;\n\
            } else {\n\
                player->setLocation(player->getLocation()->getSouth());\n\
                cout << player->getLocation()->getDescription() << endl;\n\
                goto main_loop;\n\
            }\n\
        }\n\n\
        if(verb==\"west\") {\n\
            if (!player->getLocation()->hasWest()) {\n\
                cout << \"Sorry you can not go West\" << endl;\n\
                goto main_loop;\
            } else {\
                player->setLocation(player->getLocation()->getWest());\n\
                cout << player->getLocation()->getDescription() << endl;\n\
                goto main_loop;\
            }\n\
        }\n\
        if(verb==\"east\") {\n\
            if (!player->getLocation()->hasEast()) {\n\
                cout << \"Sorry you can not go East\" << endl;\n\
                goto main_loop;\n\
            } else {\n\
                 player->setLocation(player->getLocation()->getEast());\n\
                cout << player->getLocation()->getDescription() << endl;\n\
                goto main_loop;\n\
            }\n\
        }\n\
    }\n";
    
    // END OF GAME LOOP             
    output += "}\n";

    // END OF MAIN METHOD            
    output += "}";
    cout << output << endl;

}

Compiler::~Compiler() {

}
