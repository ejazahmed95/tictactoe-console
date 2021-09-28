#include "Player.h"

MoveInfo Player::getMove() {
	// logger_->info("Click U for undo move, and M for move");
	// std::string move = input_->read_string();
	while(true) {
		auto coords = input_->readInts();
		if (coords.size() != 2) {
			logger_->error("invalid inputs for coordinates");
			continue;
		}
		return MoveInfo{ symbol, coords[1], coords[0]};
	}
}
