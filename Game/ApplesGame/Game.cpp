#include <cassert>
#include "Game.h"
#include "Record.h"

namespace ApplesGame
{
	void InitGame(Game& game, GameSettings& gameSettings)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));

		// Init settings
		game.gameSettings = gameSettings;

		// Init sounds
		InitSounds(game.sfx);

		// Init text scores
		InitUI(game.ui);

		// Init player
		InitPlayer(game.player, game);

		// Init apples:
		game.apples.resize(game.gameSettings.numApples);
		for (Apple& apple : game.apples)
		{
			InitApple(apple, game);
		}

		// Init stones:
		game.stones.resize(NUM_STONES);
		for (Stone& stone : game.stones)
		{
			InitStone(stone, game);
		}

		// Game cicle:
		game.isFinished = false;
		game.numEatenApples = 0;
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			RotatePlayer(game.player, PlayerDirection::Right);
			game.player.direction = PlayerDirection::Right;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			RotatePlayer(game.player, PlayerDirection::Up);
			game.player.direction = PlayerDirection::Up;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			RotatePlayer(game.player, PlayerDirection::Left);
			game.player.direction = PlayerDirection::Left;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			RotatePlayer(game.player, PlayerDirection::Down);
			game.player.direction = PlayerDirection::Down;
		}

		// Move player:
		switch (game.player.direction)
		{
		case PlayerDirection::Right: {
			game.player.pos.x += game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up: {
			game.player.pos.y -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left: {
			game.player.pos.x -= game.player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down: {
			game.player.pos.y += game.player.speed * deltaTime;
			break;
		}
		default:
			// Nothing to go...
			break;
		}

		// Check apples' collision:
		for (Apple& apple : game.apples)
		{
			if (apple.pos.x >= 0 && IsCirclesCollide(game.player.pos, PLAYER_SIZE / 2.f, apple.pos, APPLE_SIZE / 2.f))
			{
				UpdateScores(game.ui, ++game.numEatenApples);

				game.sfx.eatSound.play();

				// If not infinity mode - finish game
				if (!(game.gameSettings.gameMode & static_cast<int>(EGameMode::ApplesInfinity))
					&& game.numEatenApples == game.gameSettings.numApples)
				{
					game.isFinished = true;
					break;
				}

				// Acceleration boost
				if (game.gameSettings.gameMode & static_cast<int>(EGameMode::Acceleration))
				{
					game.player.speed += (game.player.acceleration * deltaTime * DELTA_TIME_CORRECT);
				}

				// Respawn apple
				if (game.gameSettings.gameMode & static_cast<int>(EGameMode::ApplesInfinity))
				{
					InitApple(apple, game);
				}
				// Hide apple
				else
				{
					apple.pos = { -10.f, -10.f };
				}
			}
		}

		// Check borders' collision:
		if (game.player.pos.y - PLAYER_SIZE / 2.f <= 0 || game.player.pos.y + PLAYER_SIZE / 2.f >= SCREEN_HEIGHT
			|| game.player.pos.x - PLAYER_SIZE / 2.f <= 0 || game.player.pos.x + PLAYER_SIZE / 2.f >= SCREEN_WIDTH)
		{
			game.isFinished = true;
			return;
		}

		// Check stones' collision:
		for (Stone& stone : game.stones)
		{
			if (IsRectanglesCollide(game.player.pos, { PLAYER_SIZE, PLAYER_SIZE }, stone.pos, { STONE_SIZE, STONE_SIZE }))
			{
				game.isFinished = true;
				break;
			}
		}
	}

	void DrawGame(sf::RenderWindow& window, Game& game)
	{
		// Draw objects:
		for (Apple& apple : game.apples)
		{
			DrawApple(apple, window);
		}
		for (Stone& stone : game.stones)
		{
			DrawStone(stone, window);
		}
		DrawPlayer(game.player, window);
		DrawUI(game.ui, window);
	}

	void GameOver(sf::RenderWindow& window, Game& game, std::unordered_map<std::string, int> records)
	{
		DrawGameOver(game.ui, window, records);
		PlaySoundUntilEnd(game.sfx.deathSound);
	}

	void DeinitializeGame(Game& game)
	{
		game.apples.clear();
		game.stones.clear();
	}

	int StartGame(int seed, GameSettings& gameSettings, std::unordered_map<std::string, int>& records)
	{
		// Init window
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

		// Game initialization
		Game game;
		InitGame(game, gameSettings);

		// Init game time:
		sf::Clock gameClock;
		float lastTime{ gameClock.getElapsedTime().asSeconds() };

		// Main loop
		while (window.isOpen() && !game.isFinished)
		{
			// Calculate time delta
			float currentTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = currentTime - lastTime;

			lastTime = currentTime;

			// Read events
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					break;
				}
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					break;
				}
			}

			// Update game state
			UpdateGame(game, deltaTime);

			window.clear();

			// Draw game
			DrawGame(window, game);

			window.display();
		}

		// Game over
		if (game.isFinished)
		{
			// Actualise array
			if (records["Player"] < game.numEatenApples)
			{
				records["Player"] = game.numEatenApples;
			}
			SortByScores(records);

			GameOver(window, game, records);

			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();

					if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
					{
						window.close();
					}
				}
			}
		}

		// Denitialization
		DeinitializeGame(game);

		return 0;
	}
}
