#include <cassert>

#include "Game.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"
#include "GameStatePlaying.h"

namespace ApplesGame
{
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, true);
			}
			else if (event.key.code == sf::Keyboard::P)
			{
				PushGameState(game, GameStateType::Pause, true);
			}
		}
	}

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		/// Init textures
		assert(data.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(data.stoneTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));

		/// Init sounds
		InitSounds(data.sfx);

		// Init texts
		InitText(data.scoreText, "SCORES:", data.font, sf::Color::White, 20);

		InitText(data.movementNote, "Use arrows keys for move", data.font, sf::Color::White, 20);
		SetTextOrigin(data.movementNote, TextOrigin::RightTop);

		// Init player
		InitPlayer(data.player, game, data.playerTexture);

		// Init apples:
		data.apples.resize(game.gameSettings.numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, game, data.appleTexture);
		}

		// Init stones:
		data.stones.resize(NUM_STONES);
		for (Stone& stone : data.stones)
		{
			InitStone(stone, game, data.stoneTexture);
		}
		data.numEatenApples = 0;
		game.ptrPlayerScores = &data.numEatenApples;
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Texts
		window.draw(data.scoreText);
		data.scoreText.setPosition(0, 0);
		window.draw(data.movementNote);
		data.movementNote.setPosition(SCREEN_WIDTH_GAME - 1, 0);

		// Textures
		DrawPlayer(data.player, window);

		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}
		for (Stone& stone : data.stones)
		{
			DrawStone(stone, window);
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		// Check player's direction
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			BalancedPlayerRotation(data.player, PlayerDirection::Up);
			data.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			BalancedPlayerRotation(data.player, PlayerDirection::Right);
			data.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			BalancedPlayerRotation(data.player, PlayerDirection::Down);
			data.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			BalancedPlayerRotation(data.player, PlayerDirection::Left);
			data.player.direction = PlayerDirection::Left;
		}

		// Update player
		UpdatePlayer(data.player, timeDelta);

		// Check borders' collision:
		if (IsObjectColdidedBorders(data.player.pos))
		{
			PushGameState(game, GameStateType::GameOver, true);
			return;
		}

		// Check apples' collision
		for (Apple& apple : data.apples)
		{
			if (!apple.isEaten && IsAppleCollidedPlayer(apple, data.player.pos))
			{
				++data.numEatenApples;
				data.sfx.eatSound.play();

				// If not infinity mode - finish game
				if (!IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity))
					&& game.gameSettings.numApples == data.numEatenApples)
				{
					PushGameState(game, GameStateType::GameOver, true);
					return;
				}

				// Respawn apple
				if (IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity)))
				{
					RespawnApple(apple);
				}
				// Mark apple as eaten
				else
				{
					RemoveApple(apple);
				}

				// Speed up player
				if (IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration)))
				{
					SpeedUpPlayer(data.player, timeDelta);
				}
			}
		}

		// Check stones' collision:
		for (Stone& stone : data.stones)
		{
			if (IsStoneCollidedPlayer(stone, data.player.pos))
			{
				PushGameState(game, GameStateType::GameOver, true);
				return;
			}
		}

		// Update scores:
		data.scoreText.setString("SCORES: " + std::to_string(data.numEatenApples));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}
}