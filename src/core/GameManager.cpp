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

	// Initializing the grid
	grid_ = new Grid<Symbol>(width_, height_);
	for (int j = 0; j < height_; j++) {
		for (int i = 0; i < width_; i++) {
			grid_->setCell(Symbol::UNDEFINED, i, j);
		}
	}
}

GameManager::~GameManager() {
	delete p1_;
	delete p2_;
	// delete grid_;
}

void GameManager::start() {
	if (state_ != GameState::INIT) {
		logger_->error("Invalid State Transition on game start: Current State = ");
		return;
	}
	logger_->info("Game Started:: GridSize = " + std::to_string(width_) + " x " + std::to_string(height_));
	_printBoard();

	state_ = GameState::PLAYING;
	while (state_ != GameState::RESULT) {
		Player* p = _getCurrentPlayer();
		_startNewTurn(p);
		if(!_playMove(p)) {
			continue;
		}
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

bool GameManager::_playMove(Player* player) {
	MoveInfo move = player->getMove();
	auto cell = grid_->getCell(move.x - 1, move.y - 1);
	if(cell != Symbol::UNDEFINED) {
		logger_->error("Position already marked as::" + enumToString(cell));
		return false;
	}
	logger_->info("Applying move for " + player->name);
	grid_->setCell(player->symbol, move.x - 1, move.y - 1);
	return true;
}

void GameManager::_printBoard() {
	char* boundary = new char[width_*3 + 1];
	boundary[width_ * 3] = '\0';
	memset(boundary, '=', sizeof(char) * 3 * width_);
	logger_->info(boundary);
	for (int j = 0; j < height_; j++) {
		for (int i = 0; i < width_; i++) {
			auto cell = grid_->getCell(i, j);
			logger_->print(" " + enumToString(cell) + " ");
		}
		logger_->print("\n");
	}
	logger_->info(boundary);
	delete[] boundary;
}

MatchResult GameManager::_endTurn() {
	current_turn_ = (current_turn_ + 1) % 2;
	total_moves_++;
	if (total_moves_ == width_ * height_ && info_.result == MatchResult::UNDECIDED) {
		info_.result = MatchResult::DRAW;
	}
	logger_->info("Turn completed");
	_printBoard();
	return info_.result;
}


