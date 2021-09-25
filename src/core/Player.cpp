#include "Player.h"

MoveInfo Player::getMove() {
	auto words = input_->readWords();
	for(const std::string &s: words) {
		logger_->info("INPUT:: " + s);
	}
	return MoveInfo{ symbol, 0, 0 };
}
