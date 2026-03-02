#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Game;

	struct Apple
	{
		bool isEaten{ false };
		Position2D pos;
		sf::Sprite sprite;
	};

	void InitApple(Apple& apple, const Game& game, const sf::Texture& texture);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void RespawnApple(Apple& apple);
	void RemoveApple(Apple& apple);
	bool IsAppleCollidedPlayer(Apple& apple, Position2D& playerPos);
}