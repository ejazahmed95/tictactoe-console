#pragma once
#include <string>

struct GameConf {
	// Board Parameters
	int width;
	int height;
	int win_size;

	// Players Details
	std::string player_one;
	std::string player_two;
};


enum class GameState {
	INIT = 1, PLAYING = 2, RESULT = 3, COMPLETED = 4
};

enum class Symbol {
	X = 1, O = 2
};

struct MoveInfo {
	Symbol symbol;
	int x, y;
};

enum class MatchResult {
	WIN = 1, DRAW = 2, UNDECIDED = 3
};

struct MatchInfo {
	std::string start_player;
	MatchResult result = MatchResult::UNDECIDED;
	std::string winner;
};