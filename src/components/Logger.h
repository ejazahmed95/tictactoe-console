#pragma once

#include <iostream>
#include "ILogger.h"

class Logger: ILogger {
public:
	Logger();
	~Logger();
	// void info(const char* message) override;
	void print(const std::string& string) override;
	void info(const std::string& string) override;
	void error(const std::string& message) override;
private:

};
