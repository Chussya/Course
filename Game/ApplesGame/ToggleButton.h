#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	enum class EToggleButtonOptions
	{
		IsFocused = 1 << 0,
		IsTurnOn = 1 << 1,
	};

	struct ToggleButton
	{
		int options{ 0 };
		const std::string turnOff = "OFF";
		const std::string turnOn = "ON";
		const sf::Color redClr = sf::Color::Red;
		const sf::Color greenClr = sf::Color::Green;
		sf::Text text;
	};

	// Standard functions

	void InitElement(ToggleButton& button, bool isTurnOn, sf::Font& font, unsigned int charSize);
	void DrawElementOnWindow(ToggleButton& button, sf::RenderWindow& window);

	// Set properties/values functions
	
	void SetElementPosition(ToggleButton& button, float x, float y);

	// Get properties/values functions

	sf::Color GetColor(ToggleButton& button);

	// Common functions

	bool IsFocused(ToggleButton& button);
	bool IsGotFocus(ToggleButton& button, Vector2D mousePos);
	void HighlightElement(ToggleButton& button);
	void UnhighlightElement(ToggleButton& button);

	// Specials

	void OnClick(ToggleButton& button);
	bool IsTurnedOn(ToggleButton& button);
}