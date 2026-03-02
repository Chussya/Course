#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	enum class ETextItemOptions
	{
		IsFocused = 1 << 0,
		isEditMode = 1 << 1,
		isNumericOnly = 1 << 2,
		isCharOnly = 1 << 3,
	};

	struct TextItem
	{
		int minValue{ 0 };
		int maxValue{ 100 };

		int options{ 0 };
		sf::Text text;
	};

	// Standard functions

	void InitElement(TextItem& textItem, std::string s, sf::Font& font, sf::Color colorText, unsigned int charSize);
	void DrawElementOnWindow(TextItem& textItem, sf::RenderWindow& window);

	// Set properties/values functions

	void SetMinValue(TextItem& textItem, int minValue);
	void SetMaxValue(TextItem& textItem, int maxValue);
	void SetNumericOnly(TextItem& textItem, bool isOnly);
	void SetCharOnly(TextItem& textItem, bool isOnly);
	void SetElementPosition(TextItem& textItem, float x, float y);

	// Get properties/values functions

	std::string GetValue(TextItem& textItem);
	sf::Color GetColor(TextItem& textItem);

	// Common functions

	void DisableOnlyMode(TextItem& textItem);
	bool IsFocused(TextItem& button);
	bool IsGotFocus(TextItem& textItem, Vector2D mousePos);
	void HighlightElement(TextItem& textItem);
	void HighlightElement(TextItem& textItem, sf::Color& color);
	void UnhighlightElement(TextItem& textItem);

	// Specials

	void EditElement(TextItem& textItem);
}