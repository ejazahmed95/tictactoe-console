#pragma once
#include "GameConfig.h"
#include "../components/ConsoleInputReader.h"
#include "../components/Logger.h"
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
	void _startNewTurn(Player* player);
	void _playMove(Player* player);
	MatchResult _endTurn();

private:
	int width_, height_, win_size_;
	ConsoleInputReader* input_reader_;
	Logger* logger_;
	Player *p1_, *p2_;
	GameState state_;
	int total_moves_;
	int current_turn_;
	MatchInfo info_;
};
