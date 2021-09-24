#include "GameManager.h"

GameManager::GameManager(GameConf conf, ConsoleInputReader* input_reader, Logger* logger) {
	width_ = conf.width;
	height_ = conf.height;
	win_size_ = conf.win_size;
	input_reader_ = input_reader;
	logger_ = logger;

	p1 = new Player(conf.player_one, input_reader, logger);
	p2 = new Player(conf.player_two, input_reader, logger);
}

void GameManager::start() {
	if (state_ != GameState::INIT) {
		logger_->error("Invalid State Transition on game start: Current State = ");
		return;
	}
	logger_->info("Game Started:: GridSize = ");


}
