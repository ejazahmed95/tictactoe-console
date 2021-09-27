#include "GameConfig.h"

inline std::string enumToString(GameState state) {
	switch (state) {
	case GameState::INIT: return "INIT";
	case GameState::PLAYING: return "PLAYING";
	case GameState::RESULT: return "RESULT";
	case GameState::COMPLETED: return "COMPLETED";
	default: return "UNKNOWN";
	}
}

inline std::string enumToString(MatchResult m) {
	switch (m) {
	case MatchResult::WIN: return "WIN";
	case MatchResult::DRAW: return "DRAW";
	default: return "UNDEFINED";
	}
};