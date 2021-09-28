#pragma once
#include "GameConfig.h"
#include "../components/ConsoleInputReader.h"
#include "../components/Logger.h"
#include "../components/Grid.h"
#include "Player.h"

// delegate for handling moves from the player class
class IMoveHandler {
};

class GameManager: IMoveHandler {
public:
	GameManager(GameConf conf, ConsoleInputReader* input_reader, Logger* logger);
	~GameManager();
	void start();
	static bool validateConf(GameConf& conf);

private:
	Player* _getCurrentPlayer();
	void undoMove();
	void _startNewTurn();
	void _playMove(Player* player);
	void _printBoard();
	int getLargestSequence(MoveInfo move_info) const;
	MatchResult _endTurn();

private:
	unsigned int width_, height_, win_size_;
	ConsoleInputReader* input_reader_;
	Logger* logger_;
	Player *p1_, *p2_;
	GameState state_;
	int total_moves_;
	int current_turn_;
	MatchInfo info_;
	Grid<Symbol>* grid_;
	std::vector<MoveInfo> all_moves_;
};
