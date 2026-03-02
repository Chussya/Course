#include "GameStateOptions.h"

#include <cassert>

#include "Game.h"
#include "Constants.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"

namespace ApplesGame
{
	void HandleGameStateOptionsWindowEvent(GameStateOptionsData& data, Game& game, const sf::Event event)
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			HandleGameStateOptionsKeyboardEvent(event.key, data, game);
			break;
		case sf::Event::MouseMoved:
		{
			HandleGameStateOptionsMouseMoveEvent(event.mouseMove, data, game);
		}
		case sf::Event::MouseButtonReleased:
			HandleGameStateOptionsMouseClickEvent(event.mouseButton, data, game);
			break;
		default:
			break;
		}
	}

	void HandleGameStateOptionsKeyboardEvent(sf::Event::KeyEvent event, GameStateOptionsData& data, Game& game)
	{
		if (event.code == sf::Keyboard::Escape)
		{
			SwitchGameState(game, GameStateType::MainMenu);
		}
	}

	void HandleGameStateOptionsMouseMoveEvent(sf::Event::MouseMoveEvent event, GameStateOptionsData& data, Game& game)
	{
		Vector2D mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };

		if (IsGotFocus(data.infApplesBtn, mousePosition)
			|| IsGotFocus(data.accBoostBtn, mousePosition)
			|| IsGotFocus(data.bonusSpeedBtn, mousePosition)
			|| IsGotFocus(data.applesNumTextItem, mousePosition))
		{
			TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		} else
		{
			TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
	}

	void HandleGameStateOptionsMouseClickEvent(sf::Event::MouseButtonEvent event, GameStateOptionsData& data, Game& game)
	{
		Vector2D mousePos = { static_cast<float>(event.x), static_cast<float>(event.y) };

		switch (event.button)
		{
		case sf::Mouse::Left:
		{
			if (IsFocused(data.infApplesBtn))
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
			}
			else if (IsFocused(data.accBoostBtn))
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
			}
			else if (IsFocused(data.bonusSpeedBtn))
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
			}
			else if (IsFocused(data.applesNumTextItem))
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
			}
			break;
		}
		default:
			break;
		}
	}

	void InitGameStateOptions(GameStateOptionsData& data, Game& game)
	{
		// Init fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		/// Init elements
		// Init texts
		InitText(data.infApplesText, "Infinity apples:", data.font, sf::Color::White, 60);
		InitText(data.accBoostText, "Acceleration boost:", data.font, sf::Color::White, 60);
		InitText(data.bonusSpeedText, "Bonus speed:", data.font, sf::Color::White, 60);
		InitText(data.applesNumText, "Number of apples:", data.font, sf::Color::White, 60);

		// Init text items
		InitElement(data.applesNumTextItem, std::to_string(game.gameSettings.numApples), data.font, sf::Color::White, 60);

		// Init buttons
		InitElement(data.infApplesBtn, IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity)), data.font, 60);
		InitElement(data.accBoostBtn, IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration)), data.font, 60);
		InitElement(data.bonusSpeedBtn, IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::Speed)), data.font, 60);

		/// Special settings
		SetNumericOnly(data.applesNumTextItem, true);
		SetMinValue(data.applesNumTextItem, NUM_APPLES_MIN);
		SetMaxValue(data.applesNumTextItem, NUM_APPLES_MAX);
	}

	void DrawGameStateOptions(GameStateOptionsData& data, Game& game, sf::RenderWindow& window)
	{
		/// Set position block
		// Set texts' positions
		data.infApplesText.setPosition(10.f, 20.f);
		data.accBoostText.setPosition(10.f, 100.f);
		data.bonusSpeedText.setPosition(10.f, 180.f);
		data.applesNumText.setPosition(10.f, 260.f);

		// Set text items' positions
		SetTextOrigin(data.applesNumTextItem.text, TextOrigin::RightTop);
		SetElementPosition(data.applesNumTextItem, 790.f, 260.f);

		// Set buttons' positions
		SetTextOrigin(data.infApplesBtn.text, TextOrigin::RightTop);
		SetElementPosition(data.infApplesBtn, 790.f, 20.f);
		SetTextOrigin(data.accBoostBtn.text, TextOrigin::RightTop);
		SetElementPosition(data.accBoostBtn, 790.f, 100.f);
		SetTextOrigin(data.bonusSpeedBtn.text, TextOrigin::RightTop);
		SetElementPosition(data.bonusSpeedBtn, 790.f, 180.f);

		// Draw texts
		window.draw(data.infApplesText);
		window.draw(data.accBoostText);
		window.draw(data.bonusSpeedText);
		window.draw(data.applesNumText);

		// Draw text items
		DrawElementOnWindow(data.applesNumTextItem, window);

		// Draw buttons
		DrawElementOnWindow(data.infApplesBtn, window);
		DrawElementOnWindow(data.accBoostBtn, window);
		DrawElementOnWindow(data.bonusSpeedBtn, window);
	}

	void UpdateGameStateOptions(GameStateOptionsData& data, Game& game, float timeDelta)
	{
		if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused)))
		{
			if (IsFocused(data.infApplesBtn))
			{
				HighlightElement(data.infApplesBtn);

				if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
				{
					OnClick(data.infApplesBtn);
					UpdateBitMask(game.gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity));
					TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				}
			}
			else if (IsFocused(data.accBoostBtn))
			{
				HighlightElement(data.accBoostBtn);

				if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
				{
					OnClick(data.accBoostBtn);
					UpdateBitMask(game.gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration));
					TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				}
			}
			else if (IsFocused(data.bonusSpeedBtn))
			{
				HighlightElement(data.bonusSpeedBtn);

				if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
				{
					OnClick(data.bonusSpeedBtn);
					UpdateBitMask(game.gameSettings.gameMode, static_cast<int>(EGameMode::Speed));
					TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				}
			}
			else if (IsFocused(data.applesNumTextItem))
			{
				HighlightElement(data.applesNumTextItem);

				if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
				{
					EditElement(data.applesNumTextItem);
					game.gameSettings.numApples = std::stoi(GetValue(data.applesNumTextItem));
					TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				}
			}
		}
		else
		{
			TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
			UnhighlightElement(data.infApplesBtn);
			UnhighlightElement(data.accBoostBtn);
			UnhighlightElement(data.bonusSpeedBtn);
			UnhighlightElement(data.applesNumTextItem);
		}
	}

	void ShutdownGameStateOptions(GameStateOptionsData& data, Game& game)
	{
		UnhighlightElement(data.infApplesBtn);
		UnhighlightElement(data.accBoostBtn);
		UnhighlightElement(data.bonusSpeedBtn);
		UnhighlightElement(data.applesNumTextItem);
	}
}