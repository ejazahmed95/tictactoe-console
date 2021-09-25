#include "GameManager.h"

GameManager::GameManager(GameConf conf, ConsoleInputReader* input_reader, Logger* logger) {
	width_ = conf.width;
	height_ = conf.height;
	win_size_ = conf.win_size;
	input_reader_ = input_reader;
	logger_ = logger;
	total_moves_ = 0;

	p1_ = new Player(conf.player_one, Symbol::X, input_reader, logger);
	p2_ = new Player(conf.player_two, Symbol::O, input_reader, logger);
	state_ = GameState::INIT;
	current_turn_ = 0;
	info_ = MatchInfo{ p1_->name, MatchResult::UNDECIDED, "" };
}

GameManager::~GameManager() {
	delete p1_;
	delete p2_;
}

void GameManager::start() {
	if (state_ != GameState::INIT) {
		logger_->error("Invalid State Transition on game start: Current State = ");
		return;
	}
	logger_->info("Game Started:: GridSize = ");

	state_ = GameState::PLAYING;
	while (state_ != GameState::RESULT) {
		Player* p = _getCurrentPlayer();
		_startNewTurn(p);
		MoveInfo info = p->getMove();
		_playMove(p);
		info_.result = _endTurn();
		if(info_.result == MatchResult::WIN || info_.result == MatchResult::DRAW) {
			state_ = GameState::RESULT;
			if (info_.result == MatchResult::WIN) info_.winner = p->name;
		}
	}
}

bool GameManager::validateConf(GameConf& conf) {
	if (conf.width < 3 || conf.height < 3) return false;
	else if (conf.win_size > conf.width && conf.win_size > conf.height) return false;
	return true;
}

Player* GameManager::_getCurrentPlayer() {
	if (current_turn_ == 0) return p1_;
	else return p2_;
}

void GameManager::_startNewTurn(Player* player) {
	char output[50];
	sprintf_s(output, "%s, it's your turn", player->name.c_str());
	logger_->info(output);
}

void GameManager::_playMove(Player* player) {
	MoveInfo move = player->getMove();
	logger_->info("Applying move for " + player->name);
}

MatchResult GameManager::_endTurn() {
	current_turn_ = (current_turn_ + 1) % 2;
	total_moves_++;
	if (total_moves_ == width_ * height_ && info_.result == MatchResult::UNDECIDED) {
		info_.result = MatchResult::DRAW;
	}
	logger_->info("Turn completed");
	return info_.result;
}


