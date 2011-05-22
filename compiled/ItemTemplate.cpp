/**
 * Class: ItemTemplate
 * File: ItemTemplate.cpp
 * Date: May 17 2011
 * Description: This is the file that will be used for the Item template
 **/

/* Constructor */

#include <string>
#include <iostream>
using namespace std;

class Item {
   string name;
   string description;
public:
   Item(string name, string description) {
      this->name = name;
      this->description = description;
   }
   Item(){}
   string getName(void) {
      return this->name;
   }

   void setName(string name) {
      this->name = name;
   }

   string getDescription(void) {
      return this->description;
   }

   void setDescription(string description) {
      this->description = description;
   }  

   void print() {
      cout << this->name << ", " << this->description << endl;
   }   

   ~Item(void) {
   }
};
