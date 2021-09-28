#pragma once
#include "GameConfig.h"
#include "../components/Grid.h"
#include "../components/ILogger.h"
#include "../components/IInputReader.h"
#include "Player.h"

// delegate for handling moves from the player class
class IMoveHandler {
};

class GameManager {
public:
	GameManager(GameConf conf, IInputReader* input_reader, ILogger* logger);
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
	IInputReader* input_reader_;
	ILogger* logger_;
	Player *p1_, *p2_;
	GameState state_;
	int current_turn_;
	MatchInfo info_;
	Grid<Symbol>* grid_;
	std::vector<MoveInfo> all_moves_;
};
