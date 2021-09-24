#pragma once
#include <xstring>
#include "../components/ConsoleInputReader.h"
#include "../components/Logger.h"

class Player {
public:
	Player(const std::string& string, ConsoleInputReader* input_reader, Logger* logger);
};
