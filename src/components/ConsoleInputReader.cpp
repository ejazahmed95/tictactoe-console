#include "ConsoleInputReader.h"

#include <iostream>
#include <string>

using std::string;
using std::vector;

vector<string> ConsoleInputReader::readWords() {
	string line;
	getline(std::cin, line);
	vector<string> words{};
	words.push_back(line);
	return words;
}
