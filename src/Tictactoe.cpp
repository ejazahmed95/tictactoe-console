// Tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "components/ConsoleInputReader.h"
#include "components/Logger.h"
#include "core/GameManager.h"

void startGame() {
	// Create dependencies
	ILogger* logger = new Logger();
	IInputReader* inputReader = new ConsoleInputReader();

	logger->info("Welcome to Advanced Tic Tac Toe!!");
	logger->info("Provide space separated values for Width, Height and WinSize ( Ex: \"3 3 3\" for TicTacToe )");
	auto gameExited = false;
	while (!gameExited) {
		std::vector<int> dimensions = inputReader->readInts();
		if (dimensions.size() != 3) {
			logger->error("Invalid input, please try again");
			continue;
		}
		const int m = dimensions[0];
		const int n = dimensions[1];
		const int k = dimensions[2];

		// Initialise and start the game
		GameConf conf = GameConf{ m,n,k,"Player 1", "Player 2" };
		if (!GameManager::validateConf(conf)) {
			logger->error("Invalid inputs"); // Take the inputs again
			continue;
		}
		GameManager gm(conf, inputReader, logger);
		gm.start();

		// TODO: Ask if another game needs to be played
		gameExited = true;
	}
	logger->info("Thank You For Playing!!");
	// Cleaning up memory
	delete logger;
	delete inputReader;
}

int main() {
	startGame();
	_CrtDumpMemoryLeaks();
}
