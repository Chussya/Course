#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameSettings.h"

namespace ApplesGame
{
	struct GameMenu
	{
		sf::Font font;

		sf::Text textTitle;
		sf::Text textPlayExit;
		sf::Text textMode;
		sf::Text textApplesNum;

		sf::RenderWindow window;

		GameSettings gameSettings;

		std::unordered_map<std::string, int> records;
	};

	void InitMenu(GameMenu& gameMenu);
	void UpdateText(GameMenu& gameMenu, sf::Keyboard::Key key);
	void DrawWindow(GameMenu& gameMenu);
	void StartMenu();
}