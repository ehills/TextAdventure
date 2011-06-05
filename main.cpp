#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include "constants.h"
#include "fileio.h"
#include "Compiler.h"
using namespace std;
//
//void handle_errors(list<string> errors) {
//    if (!errors.empty()) {
//        cerr << "------------ " << errors.size() << " Errors Found " << "------------\n";
//        while (!errors.empty()) {
//            string error = errors.back();
//            cerr << error << "\n\n";
//            errors.pop_back();
//        }
//    } else {
//        cout << "\nFile compiled without errors\n";
//    }
//}

int main(int argc, char* argv[]) {
    char* filename;
    // Check there is a file name specified
    if (argc != 2) {
        cerr << ERROR_WRONG_ARGUMENTS;
        return EXIT_FAILURE;
    }
    filename = argv[1];
    Compiler *compiler = new Compiler(filename);
    compiler->Compile();
    //cout << "Game compiled successfully.";
    return EXIT_SUCCESS;
}
