#include "GameSettings.h"

namespace ApplesGame
{
    int ChangeGameMode(int gameMode, int newMode)
    {
		return gameMode & newMode ?
            gameMode &= ~newMode :
            gameMode |= newMode;
    }
}
