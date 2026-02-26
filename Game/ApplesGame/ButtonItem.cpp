#include "ButtonItem.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitButtonItem(ButtonItem& button, std::string text, sf::Font& font, sf::Color colorText, unsigned int charSize)
	{
		button.text.setFont(font);
		button.text.setFillColor(colorText);
		button.text.setString(text);
		button.text.setCharacterSize(charSize);
	}

	void SetButtonOrigin(ButtonItem& button, ButtonOrigin buttonOrigin)
	{
		sf::FloatRect localRect = button.text.getLocalBounds();

		switch (buttonOrigin)
		{
		case ApplesGame::ButtonOrigin::LeftTop:
			button.text.setOrigin(0.f, 0.f);
			break;
		case ApplesGame::ButtonOrigin::MidTop:
			button.text.setOrigin(localRect.width / 2.f, 0.f);
			break;
		case ApplesGame::ButtonOrigin::RightTop:
			button.text.setOrigin(localRect.width, 0.f);
			break;
		case ApplesGame::ButtonOrigin::Center:
			button.text.setOrigin(localRect.width / 2.f, localRect.height / 2.f);
			break;
		case ApplesGame::ButtonOrigin::LeftBottom:
			button.text.setOrigin(0.f, localRect.height);
			break;
		case ApplesGame::ButtonOrigin::MidBottom:
			button.text.setOrigin(localRect.width / 2.f, localRect.height);
			break;
		case ApplesGame::ButtonOrigin::RightBottom:
			button.text.setOrigin(localRect.width, localRect.height);
			break;
		default:
			button.text.setOrigin(0.f, 0.f);
			break;
		}
	}

	void SetButtonPosition(ButtonItem& button, float x, float y)
	{
		button.text.setPosition(x, y);
	}

	bool IsGotFocus(ButtonItem& button, Vector2D mousePos)
	{
		sf::FloatRect globalRect = button.text.getGlobalBounds();

		return globalRect.top <= mousePos.y && globalRect.top + globalRect.height >= mousePos.y
			&& globalRect.left <= mousePos.x && globalRect.left + globalRect.width >= mousePos.x;
	}

	void HighlightButton(ButtonItem& button, sf::Color& color)
	{
		button.isFocused = true;
		button.text.setOutlineColor(color);
		button.text.setOutlineThickness(OUTLINE_THICKNESS);
	}

	void UnhighlightButton(ButtonItem& button)
	{
		button.isFocused = false;
		button.text.setOutlineThickness(0);
	}
}