#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up = 270,
		Left = 180,
		Down = 90
	};

	struct Player
	{
		Position2D pos;
		float speed{ INITIAL_SPEED };
		float acceleration{ INITIAL_ACCELERATION };
		PlayerDirection direction{ PlayerDirection::Right };
		sf::Sprite sprite;
	};

	struct Game;

	void InitPlayer(Player& player, const Game& game);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
	void RotatePlayer(Player& player, PlayerDirection newDirection);
}