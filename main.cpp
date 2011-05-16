#include <iostream>
#include <fstream>
#include <cstdlib>
#include "comments.h"
using namespace std;

int main(int argc, char* argv[]) {
   string line;
   bool in_comment = false;
   ifstream script;

   // Check there is a file name specified
   if (argc != 2) {
      cout << "Please enter one command line argument as the path to the file\n";
      return EXIT_FAILURE;
   }

   // Open the file
   script.open(argv[1]);
   if (script.is_open()) {
      while (script.good()) {
            getline(script, line);
            strip_comments(&line, &in_comment);
            if (!line.empty()) {
               cout << line << endl;
            }
      }
      script.close();
   } else {
      cout << "Unable to open " << argv[1] << "\n";
   }
   return EXIT_SUCCESS;
}
