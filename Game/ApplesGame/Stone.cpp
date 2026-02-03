#include "Game.h"
#include "Stone.h"

namespace ApplesGame
{
	void InitStone(Stone& stone, const Game& game)
	{
		for (int i = 0; i < NUM_STONES; ++i)
		{
			stone.pos = GetRandPosInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

			// Init sprite
			stone.sprite.setTexture(game.stoneTexture);
			SetSpriteSize(stone.sprite, APPLE_SIZE, APPLE_SIZE);
			SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);
		}
	}

	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.pos.x, stone.pos.y);
		window.draw(stone.sprite);
	}
}
