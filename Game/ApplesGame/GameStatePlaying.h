#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "SFX.h"

namespace ApplesGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// State data

		int numEatenApples{ 0 };
		Player player;
		std::vector<Apple> apples;
		std::vector<Stone> stones;

		// Resources

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;

		// Sound

		SFX sfx;

		// Font

		sf::Font font;

		// Text

		sf::Text scoreText;
		sf::Text movementNote;
	};

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, sf::Event event);

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
}