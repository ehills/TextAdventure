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
    
    for (it = parser.locations.begin(); it != parser.locations.end(); it++) {
        if (it->second.hasNorth()) {
            output += it->first + ".setNorth(&" + it->second.getNorth()->getName() + ");" + ";\n";
        }
        
    }
    cout << output << endl;
    
}

Compiler::~Compiler() {
    
}
