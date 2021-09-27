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
	UNDEFINED = 0,
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

inline std::string enumToString(Symbol s) {
	switch (s) {
	case Symbol::UNDEFINED: return "-";
	case Symbol::X: return "X";
	case Symbol::O: return "O";
	default: return "UNKNOWN";
	}
};

inline std::string enumToString(GameState);
// inline std::string enumToString(Symbol);
inline std::string enumToString(MatchResult);
