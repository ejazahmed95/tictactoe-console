#pragma once

class ILogger {
public:
	virtual ~ILogger() = default;
	virtual void print(const std::string&) = 0;
	virtual void info(const std::string&) = 0;
	virtual void error(const std::string&) = 0;
private:
	
};

