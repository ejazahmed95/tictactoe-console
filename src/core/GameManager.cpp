#include "GameManager.h"

GameManager::GameManager(GameConf conf, IInputReader* input_reader, ILogger* logger) {
	width_ = conf.width;
	height_ = conf.height;
	win_size_ = conf.win_size;
	input_reader_ = input_reader;
	logger_ = logger;

	p1_ = new Player(conf.player_one, Symbol::X, input_reader, logger);
	p2_ = new Player(conf.player_two, Symbol::O, input_reader, logger);
	state_ = GameState::INIT;
	current_turn_ = 0;
	info_ = MatchInfo{ p1_->name, MatchResult::UNDECIDED, "" };
	all_moves_ = std::vector<MoveInfo>{};

	// Initializing the grid
	grid_ = new Grid<Symbol>(width_, height_);
	for (int j = 0; j < height_; j++) {
		for (int i = 0; i < width_; i++) {
			grid_->setCell(Symbol::EMPTY, i, j);
		}
	}
}

GameManager::~GameManager() {
	delete p1_;
	delete p2_;
	delete grid_;
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
		_startNewTurn();
		Player* p = _getCurrentPlayer();
		_playMove(p);

		info_.result = _endTurn();

		if(info_.result == MatchResult::WIN){
			state_ = GameState::RESULT;
			info_.winner = p->name;
			logger_->info("Match ended, winner = " + info_.winner);
		} else if(info_.result == MatchResult::DRAW) {
			state_ = GameState::RESULT;
			logger_->info("Match ended in a draw");
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


void GameManager::_startNewTurn() {
	while (!all_moves_.empty()) {
		logger_->info("Press U to undo the move or any other character to start a new turn");
		const char in = input_reader_->readChar();
		if (in == 'u' || in == 'U') {
			undoMove();
		} else break;
	}
	Player* currentPlayer = _getCurrentPlayer();
	logger_->info(currentPlayer->name + "'s Turn. Input space separated integers for Row and Column (Ex: 2 2)");
}

void GameManager::_playMove(Player* player) {
	while(true) {
		MoveInfo move = player->getMove();
		auto cell = grid_->getCell(move.x - 1, move.y - 1);
		if (!grid_->isIndexValid(move.x - 1, move.y - 1) || cell != Symbol::EMPTY) {
			logger_->error("Invalid input for position, please input again");
			continue;
		}
		logger_->info("Applying move for " + player->name);
		grid_->setCell(player->symbol, move.x - 1, move.y - 1);
		all_moves_.push_back(move);
		return;
	}
}

void GameManager::undoMove() {
	if(all_moves_.empty()) {
		return;
	}
	MoveInfo info = all_moves_.back();
	grid_->setCell(Symbol::EMPTY, info.x - 1, info.y - 1);
	all_moves_.pop_back();
	current_turn_ = (current_turn_ + 1) % 2;
	logger_->info("Move Undone");
	_printBoard();
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
	logger_->info("\n");
	delete[] boundary;
}

int GameManager::getLargestSequence(MoveInfo move_info) const {
	const std::vector<std::pair<int, int>> directions{
		{1, 0}, {0, 1}, {1, 1}, {-1, 1}
	};
	int maxLength = 1, currLength = 1;
	for(const auto dir: directions) {
		currLength = 1;
		// Loop through one direction
		for(int x=move_info.x - 1 + dir.first, y = move_info.y - 1 + dir.second;
			grid_->isIndexValid(x, y) && grid_->getCell(x, y) == move_info.symbol;
			x+=dir.first, y+= dir.second) {
			currLength++;
		}

		// Loop through opposite direction
		for (int x = move_info.x - 1 - dir.first, y = move_info.y - 1 - dir.second;
			grid_->isIndexValid(x, y) && grid_->getCell(x, y) == move_info.symbol;
			x -= dir.first, y -= dir.second) {
			currLength++;
		}
		maxLength = std::max(maxLength, currLength);
	}
	return maxLength;
}

MatchResult GameManager::_endTurn() {
	current_turn_ = (current_turn_ + 1) % 2;
	if (all_moves_.size() >= width_ * height_ && info_.result == MatchResult::UNDECIDED) {
		info_.result = MatchResult::DRAW;
	}
	int seq = getLargestSequence(all_moves_.back());
	if(seq >= win_size_) {
		info_.result = MatchResult::WIN;
	}
	_printBoard();
	return info_.result;
}


