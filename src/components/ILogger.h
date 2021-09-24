#pragma once

class ILogger {
public:
	virtual ~ILogger();
	virtual void info(const std::string&) = 0;
	virtual void error(const std::string&) = 0;
private:
	
};