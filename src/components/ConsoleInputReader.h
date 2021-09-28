#pragma once
#include <string>
#include <vector>
#include "IInputReader.h"

class ConsoleInputReader: public IInputReader {
public:
	std::vector<std::string> readWords() const override;
	std::vector<int> readInts() const override;
	std::string read_string() const override;
	char readChar() const override;
};
