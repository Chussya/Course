#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "GameSettings.h"
#include "Record.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "UI.h"
#include "SFX.h"

namespace ApplesGame
{
	enum class GameState
	{
		None = 0,
		Playing,
		GameOver,
	};

	struct Game
	{
		// Global data
		std::vector<GameState> gameStateStack;
		int numEatenApples{ 0 };
		GameSettings gameSettings;

		Player player;
		std::vector<Apple> apples;
		std::vector<Stone> stones;

		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;

		// Sound
		SFX sfx;

		// UI
		UI ui;
	};

	void InitGame(Game& game, GameSettings& gameSettings);
	void PushGameState(std::vector<GameState>& game, GameState gameState);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(sf::RenderWindow& window, Game& game);
	void GameOver(sf::RenderWindow& window, Game& game, std::unordered_map<std::string, int> records);
	void DeinitializeGame(Game& game);
	int StartGame(int seed, GameSettings& gameSettings, std::unordered_map<std::string, int>& records);
}