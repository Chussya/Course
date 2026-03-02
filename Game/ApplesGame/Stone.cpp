#include "Game.h"
#include "Stone.h"

namespace ApplesGame
{
	void InitStone(Stone& stone, const Game& game, const sf::Texture& texture)
	{
		stone.pos = GetRandPosInScreen(SCREEN_WIDTH_GAME, SCREEN_HEIGHT_GAME);

		// Init sprite
		stone.sprite.setTexture(texture);
		SetSpriteSize(stone.sprite, STONE_SIZE, STONE_SIZE);
		SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);
	}

	void DrawStone(Stone& stone, sf::RenderWindow& window)
	{
		stone.sprite.setPosition(stone.pos.x, stone.pos.y);
		window.draw(stone.sprite);
	}

	bool IsStoneCollidedPlayer(Stone& stone, Position2D& playerPos)
	{
		return IsRectanglesCollide(playerPos, { PLAYER_SIZE, PLAYER_SIZE }, stone.pos, { STONE_SIZE, STONE_SIZE });
	}
}
