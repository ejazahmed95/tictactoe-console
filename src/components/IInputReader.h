#pragma once
#include <string>
#include <vector>

class IInputReader {
public:
	virtual ~IInputReader() = default;
	virtual std::vector<std::string> readWords() const = 0;	
	virtual std::vector<int> readInts() const = 0;			
	virtual std::string read_string() const = 0;			
	virtual char readChar() const = 0;						
};														
