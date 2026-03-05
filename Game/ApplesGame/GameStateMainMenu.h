#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "ButtonItem.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		int* playerScore;
		int eventMask{ 0 };

		// Font

		sf::Font font;

		// Menu text

		sf::Text titleTxt;
		ButtonItem startBtn;
		ButtonItem leaderboardBtn;
		ButtonItem optionsBtn;
		ButtonItem exitBtn;

		std::unordered_map<std::string, int> records;
	};

	// Event's functions

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void HandleKeyboardEvent(const sf::Event::KeyEvent event, GameStateMainMenuData& data, Game& game);
	void HandleMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStateMainMenuData& data, Game& game);
	void HandleMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStateMainMenuData& data, Game& game);

	// Standard functions

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
}