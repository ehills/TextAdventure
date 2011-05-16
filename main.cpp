#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
   string line;
   ifstream script;   if (argc != 2) {
      cout << "Please enter one command line argument as the path to the file\n";
      return EXIT_FAILURE;
   }
   
   script.open(argv[1]);
   if (script.is_open()) {
      cout << "OPENED " << argv[1] << " \n"; 
      while (script.good()) {
            getline (script,line);
            cout << line << endl;
      }
      script.close();
   } else {
      cout << "Unable to open " << argv[1] << "\n";
   }
   return EXIT_SUCCESS;
}
