#pragma once

class ILogger {
public:
	virtual void info(const std::string&) = 0;
	virtual void error(const std::string&) = 0;
private:
	
};