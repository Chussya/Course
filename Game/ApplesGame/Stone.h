#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Stone
	{
		Position2D pos;
		sf::Sprite sprite;
	};

	struct Game;

	void InitStone(Stone& stone, const Game& game, const sf::Texture& texture);
	void DrawStone(Stone& stone, sf::RenderWindow& window);
	bool IsStoneCollidedPlayer(Stone& stone, Position2D& playerPos);
}