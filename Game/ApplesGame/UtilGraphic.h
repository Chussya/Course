#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	enum class TextOrigin
	{
		LeftTop = 0,
		MidTop,
		RightTop,
		Center,
		LeftBottom,
		MidBottom,
		RightBottom,
	};

	void InitText(sf::Text& text, std::string s, sf::Font& font, sf::Color colorText, unsigned int charSize);
	void SetTextOrigin(sf::Text& text, TextOrigin textOrigin);
}