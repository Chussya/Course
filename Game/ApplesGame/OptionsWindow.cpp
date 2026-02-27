#include <cassert>
#include "OptionsWindow.h"
#include "Constants.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"

namespace ApplesGame
{
	void HandleOptionsWindowEvent(OptionsWindow& optionsWindow)
	{
		while (optionsWindow.window.isOpen())
		{
			sf::Event event;
			while (optionsWindow.window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					optionsWindow.window.close();
					break;
				case sf::Event::KeyReleased:
					HandleKeyboardEvent(event.key, optionsWindow);
					break;
				case sf::Event::MouseMoved:
				{
					HandleMouseMoveEvent(event.mouseMove, optionsWindow);
					optionsWindow.isChanged = true;
				}
				case sf::Event::MouseButtonReleased:
					HandleMouseClickEvent(event.mouseButton, optionsWindow);
					optionsWindow.isChanged = true;
					break;
				default:
					break;
				}
			}
			if (optionsWindow.isChanged)
			{
				DrawOptionsWindow(optionsWindow);
			}
		}
	}

	void HandleKeyboardEvent(sf::Event::KeyEvent event, OptionsWindow& optionsWindow)
	{
		if (event.code == sf::Keyboard::Escape)
		{
			optionsWindow.window.close();
		}
	}

	void HandleMouseMoveEvent(sf::Event::MouseMoveEvent event, OptionsWindow& optionsWindow)
	{
		Vector2D mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
		sf::Color clr;

		if (IsGotFocus(optionsWindow.infApplesBtn, mousePosition))
		{
			HighlightElement(optionsWindow.infApplesBtn);
		} else
		{
			UnhighlightElement(optionsWindow.infApplesBtn);
		}

		if (IsGotFocus(optionsWindow.accBoostBtn, mousePosition))
		{
			HighlightElement(optionsWindow.accBoostBtn);
		} else
		{
			UnhighlightElement(optionsWindow.accBoostBtn);
		}

		if (IsGotFocus(optionsWindow.bonusSpeedBtn, mousePosition))
		{
			HighlightElement(optionsWindow.bonusSpeedBtn);
		} else
		{
			UnhighlightElement(optionsWindow.bonusSpeedBtn);
		}

		if (IsGotFocus(optionsWindow.applesNumTextItem, mousePosition))
		{
			clr = GetColor(optionsWindow.applesNumTextItem);
			HighlightElement(optionsWindow.applesNumTextItem, clr);
		} else
		{
			UnhighlightElement(optionsWindow.applesNumTextItem);
		}
	}

	void HandleMouseClickEvent(sf::Event::MouseButtonEvent event, OptionsWindow& optionsWindow)
	{
		Vector2D mousePos = { static_cast<float>(event.x), static_cast<float>(event.y) };

		switch (event.button)
		{
		case sf::Mouse::Left:
		{
			if (IsFocused(optionsWindow.infApplesBtn))
			{
				UnhighlightElement(optionsWindow.infApplesBtn);
				OnClick(optionsWindow.infApplesBtn);
				HighlightElement(optionsWindow.infApplesBtn);
			}
			else if (IsFocused(optionsWindow.accBoostBtn))
			{
				UnhighlightElement(optionsWindow.accBoostBtn);
				OnClick(optionsWindow.accBoostBtn);
				HighlightElement(optionsWindow.accBoostBtn);
			}
			else if (IsFocused(optionsWindow.bonusSpeedBtn))
			{
				UnhighlightElement(optionsWindow.bonusSpeedBtn);
				OnClick(optionsWindow.bonusSpeedBtn);
				HighlightElement(optionsWindow.bonusSpeedBtn);
			}
			else if (IsFocused(optionsWindow.applesNumTextItem))
			{
				UnhighlightElement(optionsWindow.applesNumTextItem);
				EditElement(optionsWindow.applesNumTextItem);
				HighlightElement(optionsWindow.applesNumTextItem);
			}
			break;
		}
		default:
			break;
		}
	}

	void InitOptionsWindow(OptionsWindow& optionsWindow, GameSettings& gameSettings)
	{
		// Init Window
		optionsWindow.window.create(sf::VideoMode(SCREEN_WIDTH_OPTIONS, SCREEN_HEIGHT_OPTIONS), "Apples Game Options");

		// Init fonts
		assert(optionsWindow.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		/// Init elements
		// Init texts
		InitText(optionsWindow.infApplesText, "Infinity apples:", optionsWindow.font, sf::Color::White, 20);
		InitText(optionsWindow.accBoostText, "Acceleration boost:", optionsWindow.font, sf::Color::White, 20);
		InitText(optionsWindow.bonusSpeedText, "Bonus speed:", optionsWindow.font, sf::Color::White, 20);
		InitText(optionsWindow.applesNumText, "Number of apples:", optionsWindow.font, sf::Color::White, 20);

		// Init text items
		InitElement(optionsWindow.applesNumTextItem, std::to_string(gameSettings.numApples), optionsWindow.font, sf::Color::White, 20);

		// Init buttons
		InitElement(optionsWindow.infApplesBtn, IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity)), optionsWindow.font, 20);
		InitElement(optionsWindow.accBoostBtn, IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration)), optionsWindow.font, 20);
		InitElement(optionsWindow.bonusSpeedBtn, IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::Speed)), optionsWindow.font, 20);

		/// Set position block
		// Set texts' positions
		optionsWindow.infApplesText.setPosition(10.f, 20.f);
		optionsWindow.accBoostText.setPosition(10.f, 50.f);
		optionsWindow.bonusSpeedText.setPosition(10.f, 80.f);
		optionsWindow.applesNumText.setPosition(10.f, 110.f);

		// Set text items' positions
		SetTextOrigin(optionsWindow.applesNumTextItem.text, TextOrigin::RightTop);
		SetElementPosition(optionsWindow.applesNumTextItem, 290.f, 110.f);

		// Set buttons' positions
		SetTextOrigin(optionsWindow.infApplesBtn.text, TextOrigin::RightTop);
		SetElementPosition(optionsWindow.infApplesBtn, 290.f, 20.f);
		SetTextOrigin(optionsWindow.accBoostBtn.text, TextOrigin::RightTop);
		SetElementPosition(optionsWindow.accBoostBtn, 290.f, 50.f);
		SetTextOrigin(optionsWindow.bonusSpeedBtn.text, TextOrigin::RightTop);
		SetElementPosition(optionsWindow.bonusSpeedBtn, 290.f, 80.f);

		/// Special settings
		SetNumericOnly(optionsWindow.applesNumTextItem, true);
		SetMinValue(optionsWindow.applesNumTextItem, NUM_APPLES_MIN);
		SetMaxValue(optionsWindow.applesNumTextItem, NUM_APPLES_MAX);

		optionsWindow.isChanged = true;
	}

	void DrawOptionsWindow(OptionsWindow& optionsWindow)
	{
		optionsWindow.window.clear();

		// Draw texts
		optionsWindow.window.draw(optionsWindow.infApplesText);
		optionsWindow.window.draw(optionsWindow.accBoostText);
		optionsWindow.window.draw(optionsWindow.bonusSpeedText);
		optionsWindow.window.draw(optionsWindow.applesNumText);

		// Draw text items
		DrawElement(optionsWindow.applesNumTextItem, optionsWindow.window);

		// Draw buttons
		DrawElementOnWindow(optionsWindow.infApplesBtn, optionsWindow.window);
		DrawElementOnWindow(optionsWindow.accBoostBtn, optionsWindow.window);
		DrawElementOnWindow(optionsWindow.bonusSpeedBtn, optionsWindow.window);

		optionsWindow.isChanged = false;

		optionsWindow.window.display();
	}

	void StartOptionsWindow(GameSettings& gameSettings)
	{
		OptionsWindow optionsWindow;

		InitOptionsWindow(optionsWindow, gameSettings);
		HandleOptionsWindowEvent(optionsWindow);

		// Actualize settings
		if ((IsTurnedOn(optionsWindow.infApplesBtn) && !IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity)))
			|| (!IsTurnedOn(optionsWindow.infApplesBtn) && IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity))))
		{
			UpdateBitMask(gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity));
		}
		if ((IsTurnedOn(optionsWindow.accBoostBtn) && !IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration)))
			|| (!IsTurnedOn(optionsWindow.accBoostBtn) && IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration))))
		{
			UpdateBitMask(gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration));
		}
		if ((IsTurnedOn(optionsWindow.bonusSpeedBtn) && !IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::Speed)))
			|| (!IsTurnedOn(optionsWindow.bonusSpeedBtn) && IsBitMaskOn(gameSettings.gameMode, static_cast<int>(EGameMode::Speed))))
		{
			UpdateBitMask(gameSettings.gameMode, static_cast<int>(EGameMode::Speed));
		}
		gameSettings.numApples = std::stoi(GetValue(optionsWindow.applesNumTextItem));
	}
}