#include "Player.h"

#include "Game.h"
#include "UtilGraphic.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game, const sf::Texture& texture)
	{
		// Init state
		player.pos = { SCREEN_WIDTH_GAME / 2.f, SCREEN_HEIGHT_GAME / 2.f };
		player.speed = game.gameSettings.gameMode & static_cast<int>(EGameMode::Speed) ? INITIAL_SPEED + 100.f : INITIAL_SPEED;
		player.acceleration = game.gameSettings.gameMode & static_cast<int>(EGameMode::Acceleration) ? INITIAL_ACCELERATION : 0.f;
		player.direction = PlayerDirection::Right;

		// Init sprite
		player.sprite.setTexture(texture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			BalancedPlayerRotation(player, PlayerDirection::Right);
			break;
		}
		case PlayerDirection::Up:
		{
			BalancedPlayerRotation(player, PlayerDirection::Up);
			break;
		}
		case PlayerDirection::Left:
		{
			BalancedPlayerRotation(player, PlayerDirection::Left);
			break;
		}
		case PlayerDirection::Down:
		{
			BalancedPlayerRotation(player, PlayerDirection::Down);
			break;
		}
		default:
			break;
		}
		player.sprite.setPosition(player.pos.x, player.pos.y);
		window.draw(player.sprite);
	}

	void UpdatePlayer(Player& player, float timeDelta)
	{
		// Move player:
		switch (player.direction)
		{
		case PlayerDirection::Right: {
			player.pos.x += player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Up: {
			player.pos.y -= player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Left: {
			player.pos.x -= player.speed * timeDelta;
			break;
		}
		case PlayerDirection::Down: {
			player.pos.y += player.speed * timeDelta;
			break;
		}
		default:
			// Nothing to do...
			break;
		}
	}

	void SpeedUpPlayer(Player& player, float timeDelta)
	{
		player.speed += (player.acceleration * timeDelta * DELTA_TIME_CORRECT);
	}
}
