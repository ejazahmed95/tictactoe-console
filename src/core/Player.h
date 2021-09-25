#pragma once

#include "GameConfig.h"
#include "../components/ConsoleInputReader.h"
#include "../components/Logger.h"

class Player {
public:
	Player(const std::string& name, Symbol symbol, ConsoleInputReader* input_reader, Logger* logger)
		:name(name), symbol(symbol), input_(input_reader), logger_(logger) {}
	MoveInfo getMove();
	const std::string name;
	const Symbol symbol;
private:
	ConsoleInputReader* input_;
	Logger* logger_;
};
