#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct ButtonItem
	{
		bool isFocused{ false };
		sf::Text text;
	};

	// Standard functions

	void InitElement(ButtonItem& button, std::string text);
	void InitElement(ButtonItem& button, std::string text, sf::Font& font, sf::Color colorText, unsigned int charSize);
	void DrawElementOnWindow(ButtonItem& button, sf::RenderWindow& window);

	// Set properties/values functions

	void SetElementPosition(ButtonItem& button, float x, float y);

	// Get properties/values functions

	sf::Color GetColor(ButtonItem& button);

	// Common functions

	bool IsGotFocus(ButtonItem& button, Vector2D mousePos);
	void HighlightElement(ButtonItem& button, sf::Color& color);
	void UnhighlightElement(ButtonItem& button);
}