#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";

	// Display
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	// Game
	const float INITIAL_SPEED = 100.f;
	const float BONUS_SPEED = 100.f;
	const float INITIAL_ACCELERATION = 20.f;
	const float DELTA_TIME_CORRECT = 800.f;
	const float PLAYER_SIZE = 20.f;
	const int NUM_APPLES_MAX = 50;
	const int NUM_APPLES_MID = 25;
	const int NUM_APPLES_MIN = 1;
	const int NUM_STONES = 5;
	const float APPLE_SIZE = 20.f;
	const float STONE_SIZE = 20.f;

	// Leaderboards
	const char SYM_SEPARATE = '.';
	const char SYM_TITLE = '=';
	const unsigned int ROW_LENGTH = 50;

	enum class EGameMode
	{
		ApplesInfinity = 1 << 0,	// Num 1 ==> Apples Infinity
		Acceleration = 1 << 1,		// Num 2 ==> Acceleration Boost
		Speed = 1 << 2				// Num 3 ==> Speed Boost
	};
}