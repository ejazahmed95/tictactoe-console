#pragma once
#include <string>

struct GameConf {
	// Board Parameters
	int width;
	int height;
	int win_size;

	// Players Details
	std::string player_one;
	std::string player_two;
};
