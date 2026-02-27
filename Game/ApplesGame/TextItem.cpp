#include "TextItem.h"
#include "Constants.h"
#include "UtilBitMask.h"
#include "UtilGraphic.h"

namespace ApplesGame
{
	void InitElement(TextItem& textItem, std::string s, sf::Font& font, sf::Color colorText, unsigned int charSize)
	{
		textItem.text.setFont(font);
		textItem.text.setFillColor(colorText);
		textItem.text.setString(s);
		textItem.text.setCharacterSize(charSize);

		textItem.options = 0;
	}

	void SetMinValue(TextItem& textItem, int minValue)
	{
		textItem.minValue = minValue;
	}

	void SetMaxValue(TextItem& textItem, int maxValue)
	{
		textItem.maxValue = maxValue;
	}

	void SetNumericOnly(TextItem& textItem, bool isOnly)
	{
		isOnly
			? TurnOnMask(textItem.options, static_cast<int>(ETextItemOptions::isNumericOnly))
			: TurnOffMask(textItem.options, static_cast<int>(ETextItemOptions::isNumericOnly));
	}

	void SetCharOnly(TextItem& textItem, bool isOnly)
	{
		isOnly
			? TurnOnMask(textItem.options, static_cast<int>(ETextItemOptions::isCharOnly))
			: TurnOffMask(textItem.options, static_cast<int>(ETextItemOptions::isCharOnly));
	}

	std::string GetValue(TextItem& textItem)
	{
		return textItem.text.getString();
	}

	void DisableOnlyMode(TextItem& textItem)
	{
		TurnOffMask(textItem.options, static_cast<int>(ETextItemOptions::isNumericOnly));
		TurnOffMask(textItem.options, static_cast<int>(ETextItemOptions::isCharOnly));
	}

	sf::Color GetColor(TextItem& textItem)
	{
		return textItem.text.getFillColor();
	}

	void SetElementPosition(TextItem& textItem, float x, float y)
	{
		textItem.text.setPosition(x, y);
	}

	void DrawElement(TextItem& textItem, sf::RenderWindow& window)
	{
		window.draw(textItem.text);
	}

	bool IsFocused(TextItem& button)
	{
		return IsBitMaskOn(button.options, static_cast<int>(ETextItemOptions::IsFocused));
	}

	bool IsGotFocus(TextItem& textItem, Vector2D mousePos)
	{
		bool isFocused = false;
		sf::FloatRect globalRect = textItem.text.getGlobalBounds();

		isFocused = globalRect.top <= mousePos.y && globalRect.top + globalRect.height >= mousePos.y
			&& globalRect.left <= mousePos.x && globalRect.left + globalRect.width >= mousePos.x;

		if (isFocused)
		{
			TurnOnMask(textItem.options, static_cast<int>(ETextItemOptions::IsFocused));
		}
		else
		{
			TurnOffMask(textItem.options, static_cast<int>(ETextItemOptions::IsFocused));
		}

		return isFocused;
	}

	void HighlightElement(TextItem& textItem)
	{
		textItem.text.setOutlineColor(textItem.text.getFillColor());
		textItem.text.setOutlineThickness(OUTLINE_THICKNESS);
	}

	void HighlightElement(TextItem& textItem, sf::Color& color)
	{
		textItem.text.setOutlineColor(color);
		textItem.text.setOutlineThickness(OUTLINE_THICKNESS);
	}

	void UnhighlightElement(TextItem& textItem)
	{
		textItem.text.setOutlineThickness(0);
	}

	void EditElement(TextItem& textItem)
	{
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH_EDIT, SCREEN_HEIGHT_EDIT), "Text editor");

		TurnOnMask(textItem.options, static_cast<int>(ETextItemOptions::isEditMode));
		
		sf::Text text = textItem.text;
		std::string s = text.getString();
		sf::Font font = *text.getFont();

		InitText(text, s, font, sf::Color::White, 40);
		SetTextOrigin(text, TextOrigin::Center);
		text.setPosition(SCREEN_WIDTH_EDIT / 2.f, SCREEN_HEIGHT_EDIT / 2.f);

		window.display();

		while (window.isOpen() && IsBitMaskOn(textItem.options, static_cast<int>(ETextItemOptions::isEditMode)))
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					TurnOffMask(textItem.options, static_cast<int>(ETextItemOptions::isEditMode));
					break;
				}
				else if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Enter)
					{
						TurnOffMask(textItem.options, static_cast<int>(ETextItemOptions::isEditMode));

						if (s.empty())
						{
							text.setString(std::to_string(textItem.minValue));
						}
						textItem.text.setString(text.getString());
						break;
					} else if (event.key.code == sf::Keyboard::BackSpace)
					{
						if (s.length() > 0)
						{
							s.pop_back();
							text.setString(s);
						}
					}
				}
				else if (event.type == sf::Event::TextEntered)
				{
					if (IsBitMaskOn(textItem.options, static_cast<int>(ETextItemOptions::isNumericOnly)))
					{
						char c = (char)event.text.unicode;

						if (std::isdigit(c))
						{
							s += c;

							if (std::stoi(s) > textItem.maxValue)
							{
								s = std::to_string(textItem.maxValue);
							} else if (std::stoi(s) < textItem.minValue)
							{
								s = std::to_string(textItem.minValue);
							}
							text.setString(s);
						}
					}
				}
				window.clear();
				window.draw(text);
				window.display();
			}
		}
	}
}