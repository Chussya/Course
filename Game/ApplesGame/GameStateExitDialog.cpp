#include "GameStateExitDialog.h"

#include <cassert>

#include "Game.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"
#include "GameSettings.h"

namespace ApplesGame
{
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			HandleGameStateExitDialogKeyboardEvent(event.key, data, game);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			HandleGameStateExitDialogMouseMoveEvent(event.mouseMove, data, game);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			HandleGameStateExitDialogMouseClickEvent(event.mouseButton, data, game);
		}
	}

	void HandleGameStateExitDialogKeyboardEvent(const sf::Event::KeyEvent event, GameStateExitDialogData& data, Game& game)
	{
		switch (event.code)
		{
		case sf::Keyboard::Y:
		{
			SwitchGameState(game, GameStateType::Exit);
			break;
		}
		case sf::Keyboard::N:
		{
			PopGameState(game);
			break;
		}
		default:
			break;
		}
	}

	void HandleGameStateExitDialogMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStateExitDialogData & data, Game & game)
	{
		Vector2D mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };

		if (IsGotFocus(data.yesBtn, mousePosition)
			|| IsGotFocus(data.noBtn, mousePosition))
		{
			TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		} else
		{
			TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
	}

	void HandleGameStateExitDialogMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStateExitDialogData & data, Game & game)
	{
		switch (event.button)
		{
		case sf::Mouse::Left:
		{
			if (data.yesBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				SwitchGameState(game, GameStateType::Exit);
			}
			else if (data.noBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				PopGameState(game);
			}
			break;
		}
		default:
			break;
		}
	}

	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		// Fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		// Texts
		InitText(data.textExit, "Do You want to exit?", data.font, sf::Color::Red, 60);
		SetTextOrigin(data.textExit, TextOrigin::Center);

		// Buttons
		InitElement(data.yesBtn, "YES", data.font, sf::Color::White, sf::Color::Yellow, 40);
		SetTextOrigin(data.yesBtn.text, TextOrigin::Center);

		InitElement(data.noBtn, "NO", data.font, sf::Color::White, sf::Color::Yellow, 40);
		SetTextOrigin(data.noBtn.text, TextOrigin::Center);
	}

	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window)
	{
		// Set postions
		data.textExit.setPosition(window.getSize().x / 2.f, 250.f);
		SetElementPosition(data.yesBtn, 200.f, 375.f);
		SetElementPosition(data.noBtn, 600.f, 375.f);

		// Draw
		window.draw(data.textExit);
		DrawElementOnWindow(data.yesBtn, window);
		DrawElementOnWindow(data.noBtn, window);
	}

	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float timeDelta)
	{
		if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused)))
		{
			if (data.yesBtn.isFocused)
			{
				HighlightElement(data.yesBtn);
			}
			else if (data.noBtn.isFocused)
			{
				HighlightElement(data.noBtn);
			}

			if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
			{
				// TODO: May be add click sound...
			}
		}
		else
		{
			UnhighlightElement(data.yesBtn);
			UnhighlightElement(data.noBtn);
		}
	}

	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		UnhighlightElement(data.yesBtn);
		UnhighlightElement(data.noBtn);
	}
}