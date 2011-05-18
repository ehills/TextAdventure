#include "Parser.h"
#include "constants.h"
#define NEWLINE_HACK "(*-*)"
#define NO_ERRORS 0
#define BAD_ATTRIBUTE "(*****@@@*@**@*@*)@*!)@*#!)#*!)*#)@*!)@*#!)*$!^%#&!%(&!@%!(&^!@%(#!&@^)"

// Tools for scanning data
string ParseStringData(string data, string attribute) {
    unsigned int start, end, size;
    start = data.find(attribute);
    if (start < data.size()) {
        start = data.find("\"", start) + 1;
        end = data.find("\"", start);
        size = end - start;
        return data.substr(start, size);
    }
    return BAD_ATTRIBUTE;
}

// Tools for scanning data
string stringTrim(string data) {
    unsigned int start, end;
    start = 0;
    end = data.length() - 1;
    while (start < end) {
        if (!isspace(data.at(start))) {
            break;
        }
        data = data.erase(start, 1);
        start++;
    }
    
    while (end > start) {
        if (!isspace(data.at(end))) {
            break;
        }
        data = data.erase(end, 1);
        end--;
    }
    return data;
}

string ParseVariableData(string data, string attribute) {
    unsigned int start, end, size;
    string ret;
    start = data.find(attribute);
    if (start < data.size()) {
        start = data.find("=", start) + 1;
        end = data.find(";", start);
        size = end - start;
        ret = stringTrim(data.substr(start, size));
        return ret;
    }
    return BAD_ATTRIBUTE;
}


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
    this->ParseLocations();
    this->ParseItems();
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

int Parser::ParseDefaults() {
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
            if (end < this->file_data.size()) {
                size = (end) - start;
                Location location;
                string location_name = stringTrim(this->file_data.substr(start + 9, size - 9));
                this->locations[location_name] = location;
            }
        }
        start = this->file_data.find("Location", end);
    }

    /*
     * Parse the Location details second time through
     */
    map<string, Location>::iterator it;
    for (it = this->locations.begin(); it != this->locations.end(); it++) {
        string search = "Location " + it->first + "{";
        start = this->file_data.find(search) + search.length();
        end = this->file_data.find("}", start);
        size = (end) - start;
        string data = this->file_data.substr(start, size);
        ParseLocation(data, it->second);
    }
    return NO_ERRORS;
}

int Parser::ParseItems() {
    // Find all block comments and remove
    unsigned int start, end, size;

    /*
     * Parse the Items first time through
     */
    start = this->file_data.find("Item");
    while (start < this->file_data.size()) {
        end = this->file_data.find("{", start);
        if (end < this->file_data.size()) {
            size = (end) - start;
            Item item;
            string item_name = stringTrim(this->file_data.substr(start + 5, size - 5));
            this->items[item_name] = item;
        }
        start = this->file_data.find("location", end);
    }

    /*
     * Parse the Item details second time through
     */
    map<string, Item>::iterator it;
    for (it = this->items.begin(); it != this->items.end(); it++) {
        string search = "Item " + it->first + "{";
        start = this->file_data.find(search) + search.length();
        end = this->file_data.find("}", start);
        size = (end) - start;
        string data = this->file_data.substr(start, size);
        ParseItem(data, it->second);
    }

    return NO_ERRORS;
}

// Parses the attributes

void Parser::ParseLocation(string data, Location location) {
    string attribute;
    Location link;
    
    // Parse Name
    attribute = ParseStringData(data, "name");
    if (attribute != BAD_ATTRIBUTE) {
        location.setName(attribute);
    } else {
        // Set error (No name for location)
    }

    // Parse Description
    attribute = ParseStringData(data, "description");
    if (attribute != BAD_ATTRIBUTE) {
        location.setDescription(attribute);
    } else {
        // Set error (No description for location)
    }

    // Parse Exits
    attribute = ParseVariableData(data, "north");
    if (attribute != BAD_ATTRIBUTE) {
        link = this->locations.at(attribute);
        location.setNorth(&link);
    }
    
    attribute = ParseVariableData(data, "south");
    if (attribute != BAD_ATTRIBUTE) {
        link = this->locations.at(attribute);
        location.setSouth(&link);
    }
    
    attribute = ParseVariableData(data, "east");
    if (attribute != BAD_ATTRIBUTE) {
        link = this->locations.at(attribute);
        location.setEast(&link);
    }
    
    attribute = ParseVariableData(data, "west");
    if (attribute != BAD_ATTRIBUTE) {
        link = this->locations.at(attribute);
        location.setWest(&link);
    }
}

// Parses the attributes
void Parser::ParseItem(string data, Item item) {
    string attribute;
    Location location;
    
    // Parse Name
    attribute = ParseStringData(data, "name");
    if (attribute != BAD_ATTRIBUTE) {
        item.setName(attribute);
    } else {
        // Set error (No name for location)
    }

    // Parse Description
    attribute = ParseStringData(data, "description");
    if (attribute != BAD_ATTRIBUTE) {
        item.setDescription(attribute);
    } else {
        // Set error (No description for location)
    }
    
}

/*
 * Deallocates the resources used
 *
 */
Parser::~Parser() {

}
