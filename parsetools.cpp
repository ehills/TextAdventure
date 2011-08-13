/* Tools for scanning data */

using namespace std;
#define NO_ERRORS 0
#define BAD_ATTRIBUTE "(*****@@@*@**@*@*)@*!)@*#!)#*!)*#)@*!)@*#!)*$!^%#&!%(&!@%!(&^!@%(#!&@^)"

inline bool validAttribute(string attribute) {
	return attribute.compare(BAD_ATTRIBUTE) != 0;
}

string ParseStringData(string data, string attribute, string default_return=BAD_ATTRIBUTE) {
	unsigned int start, end, size;
	start = data.find(attribute);
	// Check expressions for valid syntax.
	if (data.find("\n", start) < data.length()) {
		int newline = data.find("\n", start);
		string expression = data.substr(start, newline-start);
		// check for missing = operator.
		if (expression.find("=") == string::npos) {
			cerr << MISSING_EQUALS_OPERATOR << "\n" << expression << "\n\n";
		}
		// Check for missing semicolon.
		if (expression.find(";") == string::npos) {
			cerr << MISSING_SEMICOLON << "\n" << expression << "\n\n";
		}
		// Check two missing quotes.
		if (expression.find("\"") == string::npos) {
			cerr << MISSING_QUOTES << "\n" << expression << "\n\n" << endl;
		}
		// Check for one missing quote.
		if (expression.find("\"") != string::npos && expression.find("\"", (expression.find("\"")+1)) == string::npos) {
			cerr << MISSING_QUOTE << "\n" << expression << "\n\n" << endl;
		}
	}
	if (start < data.size()) {
		start = data.find("\"", start) + 1;
		end = data.find("\"", start);
		size = end - start;
		return data.substr(start, size);
	}
	return default_return;
}

string stringTrim(string data) {
	unsigned int start, end;
	start = 0;
	while (start < data.length()) {
		if (!isspace(data.at(start))) {
			break;
		}
		data.replace(start, 1, "");
		start++;
	}
	end = data.length() - 1;
	while (end > 0) {
		if (!isspace(data.at(end))) {
			break;
		}
		data.replace(end, 1, "");
		end--;
	}
	return data;
}

string ParseVariableData(string data, string attribute) {
	unsigned int start, end, size;
	string ret;
	start = data.find(attribute);
	// Check expressions for valid syntax.
	if (data.find("\n", start) < data.length()) {
		int newline = data.find("\n", start);
		string expression = data.substr(start, newline-start);
		// check for missing = operator.
		if (expression.find("=") == string::npos) {
			cerr << MISSING_EQUALS_OPERATOR << "\n" << expression << "\n\n";
		}
		// Check for missing semicolon.
		if (expression.find(";") == string::npos) {
			cerr << MISSING_SEMICOLON << "\n" << expression << "\n\n";
		}
	}
	if (start < data.size()) {
		start = data.find("=", start) + 1;
		end = data.find(";", start);
		size = end - start;
		ret = (data.substr(start, size));
		ret = stringTrim(ret);
		return ret;
	}
	return BAD_ATTRIBUTE;
}

unsigned int ParseEndBrace(unsigned int start, string data) {
	unsigned int another, end, temp;
	int count = 1;
	temp = start;
	while (count > 0) {
		another = data.find("{", temp);
		end = data.find("}", temp);

		if (another < end && another < data.size()) {
			temp = another + 1;
			count++;
		} else {
			temp = end + 1;
			count--;
		}
	}
	return end;
}

map<string, string> ParseVerbs(string data) {
	map<string, string> rules;
	unsigned int start, end, size;
	start = data.find("Verb ");
	while (start < data.size()) {
		// Parse Verb name
		start = data.find("\"", start) + 1;
		end = data.find("\"", start);
		size = end - start;
		string name = data.substr(start, size);
		// Check for verb string
		if (start == 0 || size == 0) {
			cerr << BAD_VERB_STRING << endl;
		}
		// Parse Verb actions
		start = data.find("{", end) + 1;
		end = ParseEndBrace(start, data);
		size = end - start;
		string actions = data.substr(start, size);
		rules[name] = actions;

		start = data.find("Verb ", end);
	}
	return rules;
}
