#include "Parser.h"
#include "constants.h"
#include "parsetools.cpp"
#include "Player.h"

#define NEWLINE_HACK "(*-*)"

/* Constructor */
Parser::Parser(char* filename) {
    ifstream file;
    string line;
    string data;
    file.open(filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            data += line;
            data += NEWLINE_HACK;
        }
        file.close();
    }
    this->file_data = data;
}

list<string> Parser::ParseFile(void) {
    /*if (this->stripComments() > NO_ERRORS) {
    } else if (this->ParseDefaults() > NO_ERRORS) {
    } else if (this->ParseLocations() > NO_ERRORS) {
    } else if (this->ParseItems() > NO_ERRORS) {
    }*/
    this->stripComments();
    this->ParseAttributes();
    this->ParseDefaults();
    this->ParseLocations();
    this->ParseItems();
    this->ParsePlayer();

    string location_name = ParseVariableData(this->file_data, "initialLocation");
    if (this->locations.count(location_name) > 0) {
        this->initialLocation = this->locations.find(location_name)->second;
    } else {
        cout << "BAD INITIAL LOCATION" << endl;
    }



    return this->errors;
}

int Parser::stripComments() {
    // Find all block comments and remove
    unsigned int start, end, size;

    start = this->file_data.find("/*");
    while (start < this->file_data.size()) {
        end = this->file_data.find("*/");
        if (end < this->file_data.size()) {
            size = (end + 2) - start;
            this->file_data.replace(start, size, "");
        } else {
            /* Find Line number and report error */
            string error_message = ERROR_UNCLOSED_COMMENT;
            this->errors.push_front(error_message);
            return this->errors.size();
        }
        start = this->file_data.find("/*");
    }

    // Remove Line Comments
    start = this->file_data.find("//");
    while (start < this->file_data.size()) {
        end = this->file_data.find(NEWLINE_HACK, start);
        size = (end + 5) - start;
        this->file_data.replace(start, size, "");
        start = this->file_data.find("//");
    }

    // Fix Newline Hack (replace with \n)
    start = this->file_data.find(NEWLINE_HACK);
    while (start < this->file_data.size()) {
        this->file_data.replace(start, 5, "\n");
        start = this->file_data.find(NEWLINE_HACK);
    }
    return NO_ERRORS;
}

int Parser::ParseAttributes() {
    unsigned int start, end;
    string attribute;
    start = this->file_data.find("Attribute ");
    while (start < this->file_data.size()) {
        start += 10;
        end = this->file_data.find(";", start);
        attribute = stringTrim(this->file_data.substr(start, end - start));
        this->default_attribute_values[attribute] = false;
        start = this->file_data.find("Attribute ", start);
    }
    return NO_ERRORS;
}

int Parser::ParseDefaults() {
    unsigned int start, end;
    string data;
    start = this->file_data.find("ItemDefaults");
    if (start < this->file_data.size()) {
        // Parse verb expressions
        start = this->file_data.find("{", start) + 1;
        end = ParseEndBrace(start, this->file_data);
        data = this->file_data.substr(start, end - start);
        default_verb_expressions = ParseVerbs(data);

        // Parse All attributes
        map<string, bool>::iterator it;
        for (it = this->default_attribute_values.begin(); it != this->default_attribute_values.end(); it++) {
            string attribute = it->first;
            unsigned int pos = this->file_data.find(attribute, start);
            if (pos < end) {
                if (this->file_data.at(pos - 1) != '!') {
                    this->default_attribute_values[attribute] = true;
                }
            }
        }

        // REMOVE DEFAULT DATA TO AVOID COLLISION OF ITEM
        start = this->file_data.find("ItemDefaults");
        this->file_data.replace(start, end + 1 - start, "");

    }

    start = this->file_data.find("LocationDefaults");
    if (start < this->file_data.size()) {
        // Parse verb expressions
        start = this->file_data.find("{", start) + 1;
        end = ParseEndBrace(start, this->file_data);
        data = this->file_data.substr(start, end - start);
        default_location_verb_expressions = ParseVerbs(data);

        // REMOVE DEFAULT DATA TO AVOID COLLISION OF ITEM
        start = this->file_data.find("LocationDefaults");
        this->file_data.replace(start, end + 1 - start, "");

    }

    this->initialDescription = ParseStringData(this->file_data, "initialDescription");
    return NO_ERRORS;
}

int Parser::ParseLocations() {
    // Find all block comments and remove
    unsigned int start, end, size;
    /*
     * Parse the Location names first time through
     */
    start = this->file_data.find("Location");
    while (start < this->file_data.size()) {

        if (this->file_data.at(start - 1) == 'l') {
            end = start + 9;
        } else {
            end = this->file_data.find("{", start);
            if (end < this->file_data.size() && end < this->file_data.find(";", start)) {
                start += 9;
                size = (end) - start;
                Location* location = new Location();
                string location_name = stringTrim(this->file_data.substr(start, size));
                location->setVariableName(location_name);
                this->file_data.replace(start, size, location_name + " ");
                this->locations[location_name] = location;
                
            }
        }
        if (end < this->file_data.size()) {
            start = this->file_data.find("Location", end);
        } else {
            break;
        }
    }
    /*
     * Parse the Location details second time through
     */
    map<string, Location*>::iterator it;
    for (it = this->locations.begin(); it != this->locations.end(); it++) {
        string search = "Location " + it->first + " {";
        start = this->file_data.find(search) + search.length();
        if (start < this->file_data.size()) {
            end = ParseEndBrace(start, this->file_data);
            size = (end) - start;
            string data = this->file_data.substr(start, size);
            ParseLocation(data, it->second);
        } else {
            cout << "BAD LOCATION" << endl;
        }
    }
    return NO_ERRORS;
}

int Parser::ParsePlayer() {
    // Find all block comments and remove
    unsigned int start, end, size;
    string attribute, data;
    /*
     * Parse the Items first time through
     */
    start = this->file_data.find("Player ");
    if (start < this->file_data.size()) {
        end = this->file_data.find("{", start);
        if (end < this->file_data.size()) {
            start += 7;
            size = (end) - start;
            player = new Player();
            attribute = stringTrim(this->file_data.substr(start, size));
            player->setVariableName(attribute);
            end++;
            data = this->file_data.substr(end, ParseEndBrace(end, this->file_data));
            attribute = ParseStringData(data, "name");
            player->setName(attribute);
            
            attribute = ParseStringData(data, "description");
            player->setDescription(attribute);
            
            attribute = ParseVariableData(data, "carryLimit");
            player->setMaxItems(atoi(attribute.c_str()));
        }
    }

    return NO_ERRORS;
}

int Parser::ParseItems() {
    // Find all block comments and remove
    unsigned int start, end, size;

    /*
     * Parse the Items first time through
     */
    start = this->file_data.find("Item ");
    while (start < this->file_data.size()) {
        end = this->file_data.find("{", start);
        if (end < this->file_data.size()) {
            if (this->file_data.at(start - 1) != 't') {

                start += 5;
                size = (end) - start;
                Item *item = new Item();
                string item_name = stringTrim(this->file_data.substr(start, size));
                this->file_data.replace(start, size, item_name + " ");
                item->setVariableName(item_name);
                this->items[item_name] = item;
            }
        }
        start = this->file_data.find("Item ", end);
    }

    /*
     * Parse the Item details second time through
     */
    map<string, Item*>::iterator it;
    for (it = this->items.begin(); it != this->items.end(); it++) {
        string search = "Item " + it->first + " {";
        start = this->file_data.find(search) + search.length();
        if (start < this->file_data.size()) {
            end = ParseEndBrace(start, this->file_data);
            size = (end) - start;
            string data = this->file_data.substr(start, size);
            ParseItem(data, it->second);
        } else {
            cout << "BAD ITEM" << endl;

        }
    }

    return NO_ERRORS;
}

void Parser::ParseLocation(string data, Location *location) {
    string attribute;
    Location *link;
    unsigned int start, end;
    // Parse Name
    attribute = ParseStringData(data, "name");
    if (validAttribute(attribute)) {
        location->setName(attribute);
        start = data.find("name");
        end = data.find(";", start) + 1;
        data.replace(start, end - start, "");
    } else {
        // Set error (No name for location)
    }

    // Parse Description(string attribute)
    attribute = ParseStringData(data, "description");
    if (validAttribute(attribute)) {
        location->setDescription(attribute);
        start = data.find("description");
        end = data.find(";", start) + 1;
        data.replace(start, end - start, "");
    } else {
        // Set error (No description for location)
    }
    // Parse Exits
    attribute = ParseVariableData(data, "north");
    if (validAttribute(attribute)) {
        if (this->locations.count(attribute) > 0) {
            link = this->locations.at(attribute);
            location->setNorth(link);
        } else {
            cerr << "location not in map " << attribute << endl;
        }
    }

    attribute = ParseVariableData(data, "south");
    if (validAttribute(attribute)) {
        if (this->locations.count(attribute) > 0) {
            link = this->locations.at(attribute);
            location->setSouth(link);
        } else {
            cerr << "location not in map " << attribute << endl;
        }
    }

    attribute = ParseVariableData(data, "east");
    if (validAttribute(attribute)) {
        if (this->locations.count(attribute) > 0) {
            link = this->locations.at(attribute);
            location->setEast(link);
        } else {
            cerr << "location not in map " << attribute << endl;
        }
    }

    attribute = ParseVariableData(data, "west");
    if (validAttribute(attribute)) {
        if (this->locations.count(attribute) > 0) {
            link = this->locations.at(attribute);
            location->setWest(link);
        } else {
            cerr << "location not in map " << attribute << endl;
        }
    }
    //this->locations[location->getVariableName()] = *location;
}

void Parser::ParseItem(string data, Item *item) {
    string attribute;
    // Parse Name
    attribute = ParseStringData(data, "name");
    if (validAttribute(attribute)) {
        item->setName(attribute);
    } else {
        // Set error (No name for location)
    }
    // Parse Description
    attribute = ParseStringData(data, "description");
    if (validAttribute(attribute)) {
        item->setDescription(attribute);
    } else {
        // Set error (No description for location)
    }
    // Parse Description
    attribute = ParseVariableData(data, "location");
    if (validAttribute(attribute)) {
        if (this->locations.count(attribute) > 0) {
            item->setLocation(this->locations.at(attribute));
        } else {
            cerr << "location not in map " << attribute << endl;
        }
    } else {
        // Set error (No description for location)
    }

    item->addVerbs(this->default_verb_expressions);
    item->addVerbs(ParseVerbs(data));


    map<string, bool>::iterator it;
    unsigned int start, end;
    start = 0;
    end = data.size();
    map<string, bool> attributes(this->default_attribute_values);
    for (it = attributes.begin(); it != attributes.end(); it++) {
        string attribute = it->first;
        unsigned int pos = data.find(attribute, start);
        if (pos < end) {
            if (pos - 1 > 0 && data.at(pos - 1) != '!') {
                attributes[attribute] = true;
            }
        }
    }
    item->setAttributes(attributes);
}

Parser::~Parser() {

}
