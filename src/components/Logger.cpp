#include "Logger.h"

Logger::Logger() = default;

Logger::~Logger() = default;

void Logger::info(const std::string& message) {
	std::cout << message << std::endl;
}

void Logger::print(const std::string& message) {
	std::cout << message;
}

void Logger::error(const std::string& message) {
	std::cout << "===========ERROR=========" << std::endl;
	std::cout << message << std::endl;
	std::cout << "===========+++++=========" << std::endl;
}
