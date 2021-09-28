#pragma once
#include <string>
#include <vector>

class ConsoleInputReader {
public:
	std::vector<std::string> readWords() const;
	std::vector<int> readInts() const;
	std::string read_string() const;
	char readChar() const;
};
