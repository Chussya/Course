#pragma once
#include <SFML/Graphics.hpp>
#include "TextItem.h"
#include "ToggleButton.h"
#include "GameSettings.h"

namespace ApplesGame
{
	struct OptionsWindow
	{
		bool isChanged = false;

		// Fonts

		sf::Font font;

		// Texts

		sf::Text infApplesText;
		sf::Text accBoostText;
		sf::Text bonusSpeedText;
		sf::Text applesNumText;

		// Text items

		TextItem applesNumTextItem;

		// Buttons

		ToggleButton infApplesBtn;
		ToggleButton accBoostBtn;
		ToggleButton bonusSpeedBtn;

		// Window
		sf::RenderWindow window;
	};

	// Event's functions

	void HandleOptionsWindowEvent(OptionsWindow& optionsWindow);
	void HandleKeyboardEvent(sf::Event::KeyEvent event, OptionsWindow& optionsWindow);
	void HandleMouseMoveEvent(sf::Event::MouseMoveEvent event, OptionsWindow& optionsWindow);
	void HandleMouseClickEvent(sf::Event::MouseButtonEvent event, OptionsWindow& optionsWindow);

	// Standard functions

	void InitOptionsWindow(OptionsWindow& optionsWindow, GameSettings& gameSettings);
	void DrawOptionsWindow(OptionsWindow& optionsWindow);

	void StartOptionsWindow(GameSettings& gameSettings);
}