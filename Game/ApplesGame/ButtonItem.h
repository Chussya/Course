#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	enum class ButtonOrigin
	{
		LeftTop = 0,
		MidTop,
		RightTop,
		Center,
		LeftBottom,
		MidBottom,
		RightBottom,
	};

	struct ButtonItem
	{
		sf::Text text;
		sf::FloatRect* blockSize = nullptr;
	};

	void InitButtonItem(ButtonItem& button, std::string text, sf::Font font, sf::Color colorText, unsigned int charSize);
	void SetButtonOrigin(ButtonItem& button, ButtonOrigin buttonOrigin);
	void SetButtonPosition(ButtonItem& button, float x, float y);
	bool IsGotFocus(ButtonItem& button, Vector2D mousePos);
	void HighlightButton(ButtonItem& button, sf::Color color);
}