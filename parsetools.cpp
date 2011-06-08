using namespace std;
#define NO_ERRORS 0
#define BAD_ATTRIBUTE "(*****@@@*@**@*@*)@*!)@*#!)#*!)*#)@*!)@*#!)*$!^%#&!%(&!@%!(&^!@%(#!&@^)"


/* Tools for scanning data */

inline bool validAttribute(string attribute) {
	return attribute.compare(BAD_ATTRIBUTE) != 0;
}

string ParseStringData(string data, string attribute, string default_return=BAD_ATTRIBUTE) {
	unsigned int start, end, size;
	start = data.find(attribute);
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
