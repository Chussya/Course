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
		Death,
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

	// Event's functions
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);

	// Standard functions
	void InitGame(Game& game, GameSettings& gameSettings);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(sf::RenderWindow& window, Game& game);
	void DeinitializeGame(Game& game);

	// Game state logic
	void GameStatePlaying(Game& game, sf::RenderWindow& window, float currentTime);
	void GameStateDeath(Game& game);
	void GameStateGameOver(Game& game, sf::RenderWindow& window);
	void ChangeGameState(std::vector<GameState>& stack, GameState gameState);
	void AddGameState(std::vector<GameState>& stack, GameState gameState);
	void RemoveGameState(std::vector<GameState>& stack);
	GameState GetGameState(std::vector<GameState>& stack);

	// Main function. Returns game's state in the end of game
	int StartGame(GameSettings& gameSettings, int*& playerScore);
}