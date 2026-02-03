#pragma once

#include "Constants.h"

namespace ApplesGame
{
	struct GameSettings
	{
		int numApples{ NUM_APPLES_MID };
		int gameMode = 0;
	};

	int ChangeGameMode(int gameMode, int newMode);
}
