#ifndef ITEM_H_
#define ITEM_H_
#include <string>
using namespace std;

/* Item class stores all information relevant to a particular item object */
class Item {
    string name;
    string description;
public:
    Item(string name, string description);
    Item();
    string getName(void);
    void setName(string name);
    string getDescription(void);
    void setDescription(string description);
    ~Item();
};


#endif