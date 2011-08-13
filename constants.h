/* Description: Some constants for parsing the users game file */

#ifndef CONSTANTS_H_
#define CONSTATNS_H_

// ERRORS
#define ERROR_WRONG_ARGUMENTS "Please enter one command line argument as the path to the file.\n"
#define ERROR_BAD_FILE "The file specified was not able to be opened.\n"
#define ERROR_TEMP_FILE_NOT_OPEN "The temporary file was unavailable.\n"
#define ERROR_UNCLOSED_COMMENT "There is an unclosed multiple line comment.\n"
#define BAD_LOCATION "Cannot find your location "
#define NO_LOCATION_NAME "Your location must have a name."
#define NO_ITEM "Cannot find item."
#define NO_LOCATION_DESCRIPTION "Your location does not have a description."
#define NO_JOINED_LOCATION "You are trying to join to a location that does not exist: "
#define NO_ITEM_NAME "Your item does not have a name."
#define NO_ITEM_DESCRIPTION "Your item does not have a description."
#define NO_ITEM_LOCATION "Your item is not associated with a location."
#define UNKNOWN_COMMAND "Unreadable/Unknown Command: \""
#define UNKNOWN_PRINT_STATEMENT "Unknown/ill-formed Print Statement."
#define INCOMPLETE_EXPRESSION "Your expression is incomplete."
#define BAD_CARRIABLE_EXPRESSION "Your carry expression is wrong."
#define BAD_INLOCATION "Your inLocation statement is incorrect."
#define BAD_BOOLEAN "Your boolean (true/false) expression is incorrect."
#define BAD_BRACES "Your open and close braces are not syntactically correct."
#define ONLY_ONE_LOCATION "You need more than one Location."
#define NO_LOCATIONS "You do not have any Locations."
#define PARSER_FAIL "The Parser did not complete without errors."
#define FILE_DID_NOT_OPEN "The file specified was unable to be opened."
#define INCOMPLETE_HASATTRIBUTE "Need to use a valid item before hasAttribute."
#define INCOMPLETE_SETATTRIBUTE "Need to use a valid item before getAttribute."
#define BAD_INITIAL_LOCATION "Need to set initialLocation."
#define NO_LOCATION_VARIABLE_NAME "Locations must have a unique variable name eg. Location uniqueName {}"
#define NO_ITEM_VARIABLE_NAME "Items must have a unique variable name eg. Item uniqueName {}"
#define NO_PLAYER_VARIABLE_NAME "Player must have a variable name eg. Player name {}"
#define BAD_VERB_STRING "Verbs must contain a non empty verb string eg. Verb \"n\" {}"
#define MISSING_EQUALS_OPERATOR "This expression must assign a value with an '=' operator."
#define MISSING_SEMICOLON "This expression must end with a ';' character."
#define MISSING_QUOTES "Missing both quotes. This expression must contain an opening and closing quote."
#define MISSING_QUOTE "Missing a quote. This expression must contain an opening and closing quote."

#endif
