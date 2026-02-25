#include "ButtonItem.h"

namespace ApplesGame
{
	void InitButtonItem(ButtonItem& button, std::string text, sf::Font font, sf::Color colorText, unsigned int charSize)
	{
		button.text.setFont(font);
		button.text.setFillColor(colorText);
		button.text.setString(text);
		button.text.setCharacterSize(charSize);
		//sf::FloatRect rect = button.text.getLocalBounds();
		//button.blockSize = &rect;
	}

	void SetButtonOrigin(ButtonItem& button, ButtonOrigin buttonOrigin)
	{
		switch (buttonOrigin)
		{
		case ApplesGame::ButtonOrigin::LeftTop:
			button.text.setOrigin(0.f, 0.f);
			break;
		case ApplesGame::ButtonOrigin::MidTop:
			button.text.setOrigin(button.blockSize->width / 2.f, 0.f);
			break;
		case ApplesGame::ButtonOrigin::RightTop:
			button.text.setOrigin(button.blockSize->width, 0.f);
			break;
		case ApplesGame::ButtonOrigin::Center:
			button.text.setOrigin(button.blockSize->width / 2.f, button.blockSize->height / 2.f);
			break;
		case ApplesGame::ButtonOrigin::LeftBottom:
			button.text.setOrigin(0.f, button.blockSize->height);
			break;
		case ApplesGame::ButtonOrigin::MidBottom:
			button.text.setOrigin(button.blockSize->width / 2.f, button.blockSize->height);
			break;
		case ApplesGame::ButtonOrigin::RightBottom:
			button.text.setOrigin(button.blockSize->width, button.blockSize->height);
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
		return button.blockSize->top <= mousePos.y && button.blockSize->height >= mousePos.y
			&& button.blockSize->left <= mousePos.x && button.blockSize->width >= mousePos.x;
	}

	void HighlightButton(ButtonItem& button, sf::Color color)
	{
		button.text.setOutlineColor(color);
	}
}