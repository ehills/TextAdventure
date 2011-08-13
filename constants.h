/* Description: Some constants for parseing the users game file */

#ifndef CONSTANTS_H_
#define CONSTATNS_H_

// ERRORS
#define ERROR_WRONG_ARGUMENTS "Please enter one command line argument as the path to the file\n"
#define ERROR_BAD_FILE "The file specified was not able to be opened.\n"
#define ERROR_TEMP_FILE_NOT_OPEN "The temporary file was unavailable.\n"
#define ERROR_UNCLOSED_COMMENT "There is an unclosed multiline comment.\n"
#define BAD_LOCATION "Cannot find your location."
#define NO_LOCATION_NAME "Your location must have a name."
#define NO_ITEM "Cannot find item."
#define NO_LOCATION_DESCRIPTION "Your location does not have a description."
#define NO_JOINED_LOCATION "You are trying to join to a room that does not exist."
#define NO_ITEM_NAME "Your item does not have a name."
#define NO_ITEM_DESCRIPTION "Your item does not have a description."
#define NO_ITEM_LOCATION "Your item is not associated with a location."
#define UNKNOWN_COMMAND "Unreadable/Unknown Command: \""
#define UNKNOWN_PRINT_STATEMENT "Unknown/Illformed Print Statement."
#define INCOMPLETE_EXPRESSION "Your expression is incomplete."
#define BAD_CARRIABLE_EXPRESSION "Your carry expression is wrong."
#define BAD_INLOCATION "Your inLocation statement is incorrect."
#define BAD_BOOLEAN "Your boolean (true/false) expression is incorrect."
#define BAD_BRACES "Your braces {, } are not sentactically correct."
#define ONLY_ONE_LOCATION "You need more than one Location."
#define NO_LOCATIONS "You do not have any Locations."
#define PARSER_FAIL "The Parser did not complete without errors."
#define FILE_DID_NOT_OPEN "The file specified was unable to be opened"
#define NO_DEFAULT_ATTRIBUTE "There is no default attribute for that item's attribute"
#define NO_INVENTORY "Need to set Location inventory in game file"
#define INCOMPLETE_HASATTRIBUTE "Need to use a valid item before hasAttribute"
#define INCOMPLETE_SETATTRIBUTE "Need to use a valid item before getAttribute"
#endif
