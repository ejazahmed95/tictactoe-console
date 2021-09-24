// Tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "components/ConsoleInputReader.h"
#include "components/Logger.h"
#include "core/GameManager.h"

int main() {

	// Create dependencies
	const auto logger = new Logger();
	const auto inputReader = new ConsoleInputReader();

	logger->info("Welcome to Advanced Tic Tac Toe!!");
	logger->info("Print the");
	auto gameExited = false;
	while(!gameExited) {
		int m, n, k;
		std::cin >> m >> n >> k;
		auto gm = new GameManager(m, n, k, inputReader, logger);
	}

	logger->info("Thank You!!");

	// Cleaning up memory
	delete logger;
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
