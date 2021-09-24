#pragma once
#include "GameConfig.h"
#include "Player.h"
#include "../components/ConsoleInputReader.h"
#include "../components/Logger.h"


enum class GameState {
	INIT = 1, PLAYING = 2, RESULT = 3, COMPLETED = 4
};

enum Symbol {
	X, O
};

struct MoveInfo {
	Symbol symbol;
	int x, y;
};

// delegate for handling moves from the player class
class IMoveHandler {
};

class GameManager: IMoveHandler {
public:
	GameManager(GameConf conf, ConsoleInputReader* input_reader, Logger* logger);
	void start();
private:
	int width_, height_, win_size_;
	ConsoleInputReader* input_reader_;
	Logger* logger_;
	Player* p1, *p2;
	GameState state_;
};
