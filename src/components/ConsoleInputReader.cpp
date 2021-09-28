#include "ConsoleInputReader.h"

#include <iostream>
#include <string>
#include <conio.h>

using std::string;
using std::vector;

vector<string> ConsoleInputReader::readWords() const {
	string line;
	getline(std::cin, line);
	vector<string> words{};
	int startIndex = 0, endIndex = 0;
	for(const char c: line) {
		if(c == ' ') {
			if(startIndex != endIndex) {
				words.push_back(line.substr(startIndex, static_cast<long long>(endIndex) - startIndex));
			}
			startIndex = endIndex + 1;
		}
		endIndex++;
	}
	if(startIndex < endIndex) {
		words.push_back(line.substr(startIndex, endIndex));
	}
	return words;
}

vector<int> ConsoleInputReader::readInts() const {
	vector<std::string> words = readWords();
	vector<int> ints{};
	for(auto& w: words) {
		ints.push_back(stoi(w));
	}
	return ints;
}

std::string ConsoleInputReader::read_string() const {
	std::string word;
	getline(std::cin, word);
	return word;
}

char ConsoleInputReader::readChar() const {
	const char ch = _getch();
	return ch;
}
