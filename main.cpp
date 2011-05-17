#include <iostream>
#include <fstream>
#include <cstdlib>
#include "comments.h"
#include "constants.h"
#include "fileio.h"
using namespace std;

void parse_file() {
   strip_file_comments();
}

int main(int argc, char* argv[]) {
   char* filename;
   // Check there is a file name specified
   if (argc != 2) {
      cout << ERROR_WRONG_ARGUMENTS;
      return EXIT_FAILURE;
   }
   filename = argv[1];
   // Open the file
   copy_file(filename, WORKING_FILENAME);
   parse_file();
   return EXIT_SUCCESS;
}
