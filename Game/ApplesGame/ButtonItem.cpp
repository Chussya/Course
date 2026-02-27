#include "ButtonItem.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitElement(ButtonItem& button, std::string text)
	{
		button.text.setString(text);
	}

	void InitElement(ButtonItem& button, std::string text, sf::Font& font, sf::Color colorText, unsigned int charSize)
	{
		button.text.setFont(font);
		button.text.setFillColor(colorText);
		button.text.setString(text);
		button.text.setCharacterSize(charSize);
	}

	void DrawElementOnWindow(ButtonItem& button, sf::RenderWindow& window)
	{
		window.draw(button.text);
	}

	sf::Color GetColor(ButtonItem& button)
	{
		return button.text.getFillColor();
	}

	void SetElementPosition(ButtonItem& button, float x, float y)
	{
		button.text.setPosition(x, y);
	}

	bool IsGotFocus(ButtonItem& button, Vector2D mousePos)
	{
		sf::FloatRect globalRect = button.text.getGlobalBounds();

		button.isFocused = globalRect.top <= mousePos.y && globalRect.top + globalRect.height >= mousePos.y
			&& globalRect.left <= mousePos.x && globalRect.left + globalRect.width >= mousePos.x;

		return button.isFocused;
	}

	void HighlightElement(ButtonItem& button, sf::Color& color)
	{
		button.text.setOutlineColor(color);
		button.text.setOutlineThickness(OUTLINE_THICKNESS);
	}

	void UnhighlightElement(ButtonItem& button)
	{
		button.text.setOutlineThickness(0);
	}
}