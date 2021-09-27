// Tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// #include "Tictactoe.h"
#include "components/ConsoleInputReader.h"
#include "components/Logger.h"
#include "core/GameManager.h"


int main() {

	// Create dependencies
	const auto logger = new Logger();
	const auto inputReader = new ConsoleInputReader();

	logger->info("Welcome to Advanced Tic Tac Toe!!");
	logger->info("Provide space separated values for Width, Height and WinSize");
	auto gameExited = false;
	while(!gameExited) {
		std::vector<int> dimensions = inputReader->readInts();
		if(dimensions.size() != 3) {
			logger->error("Invalid input, please try again");
			continue;
		}
		const int m = dimensions[0];
		const int n = dimensions[1];
		const int k = dimensions[2];

		GameConf conf = GameConf{m,n,k,"Ejaz", "Tehas"};
		if(!GameManager::validateConf(conf)) {
			logger->error("Invalid inputs");
			continue;
		}

		auto gm = new GameManager(GameConf{m,n,k,"Ejaz","Tehas"}, inputReader, logger);
		gm->start();

		// TODO: Ask if another game needs to be played
		gameExited = true;
	}
	logger->info("Thank You For Playing!!");
	// Cleaning up memory
	delete logger;
	delete inputReader;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
