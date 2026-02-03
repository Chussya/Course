#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		// Init state
		player.pos = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = game.gameSettings.gameMode & static_cast<int>(EGameMode::Speed) ? INITIAL_SPEED + 100.f : INITIAL_SPEED;
		player.acceleration = game.gameSettings.gameMode & static_cast<int>(EGameMode::Acceleration) ? INITIAL_ACCELERATION : 0.f;
		player.direction = PlayerDirection::Right;

		// Init sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.pos.x, player.pos.y);
		window.draw(player.sprite);
	}

	void RotatePlayer(Player& player, PlayerDirection newDirection)
	{
		if (player.direction != newDirection)
		{
			player.sprite.setRotation((float)newDirection);

			// Flip player's sprite per siding (left <-> right)
			int width = (int)player.sprite.getTexture()->getSize().x;
			int height = (int)player.sprite.getTexture()->getSize().y;

			if (newDirection == PlayerDirection::Left)
			{
				player.sprite.setTextureRect(sf::IntRect(0, height, width, -height));
			}
			if (newDirection == PlayerDirection::Right)
			{
				player.sprite.setTextureRect(sf::IntRect(0, 0, width, height));
			}
		}
	}
}
