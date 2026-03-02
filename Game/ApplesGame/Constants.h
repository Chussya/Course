#pragma once
#include <string>

namespace ApplesGame
{
	// Path

	const std::string RESOURCES_PATH = "Resources/";

	// Display

	const int SCREEN_WIDTH_GAME = 800;
	const int SCREEN_HEIGHT_GAME = 600;
	const int SCREEN_WIDTH_EDIT = 300;
	const int SCREEN_HEIGHT_EDIT = 100;

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

	// Leaderboard

	const char SYM_SEPARATE = '.';
	const char SYM_TITLE = '=';
	const unsigned int ROW_LENGTH = 50;
	const std::string PLAYER_INDEX = "Player";

	// Visual

	const int OUTLINE_THICKNESS = 1;
}