#include "Compiler.h"

/* Constructor */
Compiler::Compiler() {
}

void Compiler::Compile(char* filename) {
    Parser parser(filename);
    parser.ParseFile();
    
    // Setting up includes/defines
    string output = "\
#include <iostream>\n\
#include <cstdlib>\n\
#include <string>\n\
#include <sstream>\n\
#include \"Location.h\"\n\
#include \"Player.h\"\n\
using namespace std;\n\
#define WELCOME_MESSAGE \"" + parser.initialDescription + "\"\n\
#define QUIT_GAME \"quit\"\n\
\n\
int main(int argc, char **argv) {\n\
\tstring username;\n\
\tstring command;\n\
\tstring verb;\n\
\tstring noun;\n\
\tstring prompt;\n\
\tint count;\n\
\n";
    
    
    // Output locations  
    map<string, Location>::iterator it;
    for (it = parser.locations.begin(); it != parser.locations.end(); it++) {
        output += "\tLocation " + it->first + "(\"" + it->second.getName() + "\", \"" + it->second.getDescription() + "\");\n";
    }
    
    output += "\n";
    
    for (it = parser.locations.begin(); it != parser.locations.end(); it++) {
        Location location = it->second;
        if (location.hasNorth()) {
            output += "\t" + it->first + ".setNorth(&" + location.getNorth()->getName() + ");\n";
        }
        if (location.hasSouth()) {
            output += "\t" + it->first + ".setSouth(&" + location.getSouth()->getName() + ");\n";
        }
        if (location.hasEast()) {
            output += "\t" + it->first + ".setEast(&" + location.getEast()->getName() + ");\n";
        }
        if (location.hasWest()) {
            output += "\t" + it->first + ".setWest(&" + location.getWest()->getName() + ");\n";
        }
    }
    cout << output << endl;
    
}

Compiler::~Compiler() {
    
}
