#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameSettings.h"

namespace ApplesGame
{
	struct GameMenu
	{
		sf::Font font;

		// Menu text
		sf::Text textTitle;
		sf::Text textPlayExit;
		sf::Text textMode;
		sf::Text textApplesNum;

		sf::RenderWindow window;

		GameSettings gameSettings;

		std::unordered_map<std::string, int> records;
	};

	void HandleGameMenuEvent(GameMenu& gameMenu);
	void HandleKeyboardEvent(sf::Event::KeyEvent keyEvent, GameMenu& gameMenu);
	void InitMenu(GameMenu& gameMenu);
	void UpdateText(GameMenu& gameMenu, sf::Keyboard::Key key);
	void DrawMenuWindow(GameMenu& gameMenu);
	void LoadGame(GameMenu& gameMenu);
	void LoadExitDialog(GameMenu& gameMenu);
	void StartMenu();
}