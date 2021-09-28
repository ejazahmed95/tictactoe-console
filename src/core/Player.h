#pragma once

#include "GameConfig.h"
#include "../components/ConsoleInputReader.h"
#include "../components/Logger.h"

class Player {
public:
	Player(const std::string& name, Symbol symbol, IInputReader* input_reader, ILogger* logger)
		:name(name), symbol(symbol), input_(input_reader), logger_(logger) {}
	MoveInfo getMove();
	const std::string name;
	const Symbol symbol;
private:
	IInputReader* input_;
	ILogger* logger_;
};
