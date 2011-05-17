#include "Parser.h"
#include "constants.h"
#define NEWLINE_HACK "(*-*)"
#define NO_ERRORS 0

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
            data += "(*-*)";
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

    start = this->file_data.find("Location");
    while (start < this->file_data.size()) {
        if (this->file_data.at(start - 1) == 'l') {
             end = start + 9;
        } else {
            end = this->file_data.find("{", start);
            if (end < this->file_data.size()) {
                size = (end) - start;
                cout << this->file_data.substr(start + 9, size - 9) << "\n";
                /*
                 * ADD TO LOCATION MAP
                 * 
                 * THEN LOOP AGAIN TO ADD DETAILS (DUE TO REFERENCING ISSUE)
                 */
            }
        }
        start = this->file_data.find("Location", end);
    }

    return NO_ERRORS;
}

int Parser::ParseItems() {
   /* // Find all block comments and remove
    unsigned int start, end, size;

    start = this->file_data.find("Item");
    while (start < this->file_data.size()) {
        end = this->file_data.find("{", start);
        if (end < this->file_data.size()) {
            size = (end) - start;
            cout << this->file_data.substr(start + 4, size - 4) << "\n";
            / *
             * ADD TO ITEM MAP
             * 
             * THEN LOOP AGAIN TO ADD DETAILS (DUE TO REFERENCING ISSUE)
             * /
        }
        start = this->file_data.find("location", end);
    }*/

    return NO_ERRORS;
}

/*
 * Deallocates the resources used
 *
 */
Parser::~Parser() {

}
