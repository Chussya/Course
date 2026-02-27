#include "ToggleButton.h"
#include "UtilBitMask.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitElement(ToggleButton& button, bool isOn, sf::Font& font, unsigned int charSize)
	{
		button.text.setFont(font);
		button.text.setFillColor(isOn ? button.greenClr : button.redClr);
		button.text.setString(isOn ? button.turnOn : button.turnOff);
		button.text.setCharacterSize(charSize);

		if (isOn) TurnOnMask(button.options, static_cast<int>(EToggleButtonOptions::IsTurnOn));
		else button.options = 0;
	}

	void OnClick(ToggleButton& button)
	{
		UpdateBitMask(button.options, static_cast<int>(EToggleButtonOptions::IsTurnOn));

		button.text.setFillColor(IsBitMaskOn(button.options, static_cast<int>(EToggleButtonOptions::IsTurnOn)) ? button.greenClr : button.redClr);
		button.text.setString(IsBitMaskOn(button.options, static_cast<int>(EToggleButtonOptions::IsTurnOn)) ? button.turnOn : button.turnOff);
	}

	void DrawElementOnWindow(ToggleButton& button, sf::RenderWindow& window)
	{
		window.draw(button.text);
	}

	sf::Color GetColor(ToggleButton& button)
	{
		return button.text.getFillColor();
	}

	void SetElementPosition(ToggleButton& button, float x, float y)
	{
		button.text.setPosition(x, y);
	}

	bool IsTurnedOn(ToggleButton& button)
	{
		return IsBitMaskOn(button.options, static_cast<int>(EToggleButtonOptions::IsTurnOn));
	}

	bool IsFocused(ToggleButton& button)
	{
		return IsBitMaskOn(button.options, static_cast<int>(EToggleButtonOptions::IsFocused));
	}

	bool IsGotFocus(ToggleButton& button, Vector2D mousePos)
	{
		bool isFocused = false;
		sf::FloatRect globalRect = button.text.getGlobalBounds();

		isFocused = globalRect.top <= mousePos.y && globalRect.top + globalRect.height >= mousePos.y
			&& globalRect.left <= mousePos.x && globalRect.left + globalRect.width >= mousePos.x;

		if (isFocused)
		{
			TurnOnMask(button.options, static_cast<int>(EToggleButtonOptions::IsFocused));
		} else
		{
			TurnOffMask(button.options, static_cast<int>(EToggleButtonOptions::IsFocused));
		}
		return isFocused;
	}

	void HighlightElement(ToggleButton& button)
	{
		button.text.setOutlineColor(IsBitMaskOn(button.options, static_cast<int>(EToggleButtonOptions::IsTurnOn)) ? button.greenClr : button.redClr);
		button.text.setOutlineThickness(OUTLINE_THICKNESS);
	}

	void UnhighlightElement(ToggleButton& button)
	{
		button.text.setOutlineThickness(0);
	}
}