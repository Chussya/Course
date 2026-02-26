#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameSettings.h"
#include "ButtonItem.h"

namespace ApplesGame
{
	struct GameMenu
	{
		bool isChanged = false;
		int* playerScore;

		// Font
		sf::Font font;

		// Menu text
		sf::Text titleTxt;
		ButtonItem startBtn;
		ButtonItem modeBtn;
		ButtonItem exitBtn;

		sf::RenderWindow window;

		GameSettings gameSettings;

		std::unordered_map<std::string, int> records;
	};

	// Event's functions
	void HandleGameMenuEvent(GameMenu& gameMenu);
	void HandleKeyboardEvent(sf::Event::KeyEvent keyEvent, GameMenu& gameMenu);
	void HandleMouseMoveEvent(sf::Event::MouseMoveEvent event, GameMenu& gameMenu);
	void HandleMouseClickEvent(sf::Event::MouseButtonEvent event, GameMenu& gameMenu);

	// Standard functions
	void InitMenu(GameMenu& gameMenu);
	void UpdateText(GameMenu& gameMenu, sf::Keyboard::Key key);
	void DrawMenuWindow(GameMenu& gameMenu);
	void DeinitializeMenu(GameMenu& gameMenu);

	// Windows functions
	void StartPlayingGame(GameMenu& gameMenu);
	void StartExitDialog(GameMenu& gameMenu);
	void StartMenu();
}