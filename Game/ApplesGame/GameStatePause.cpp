#include "GameStatePause.h"

#include <cassert>

#include "Game.h"
#include "Math.h"
#include "UtilBitMask.h"
#include "UtilGraphic.h"

namespace ApplesGame
{
	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			HandleGameStatePauseKeyboardEvent(event.key, data, game);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			HandleGameStatePauseMouseMoveEvent(event.mouseMove, data, game);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			HandleGameStatePauseMouseClickEvent(event.mouseButton, data, game);
		}
	}

	void HandleGameStatePauseKeyboardEvent(const sf::Event::KeyEvent event, GameStatePauseData& data, Game& game)
	{
		switch (event.code)
		{
		case sf::Keyboard::Space:
		{
			PopGameState(game);
			break;
		}
		case sf::Keyboard::Escape:
		{
			SwitchGameState(game, GameStateType::MainMenu);
			break;
		}
		default:
			break;
		}
	}

	void HandleGameStatePauseMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStatePauseData & data, Game & game)
	{
		Vector2D mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };

		if (IsGotFocus(data.continueBtn, mousePosition)
			|| IsGotFocus(data.exitMenuBtn, mousePosition))
		{
			TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
		else
		{
			TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
	}

	void HandleGameStatePauseMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStatePauseData & data, Game & game)
	{
		switch (event.button)
		{
		case sf::Mouse::Left:
		{
			if (data.continueBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				PopGameState(game);
			}
			else if (data.exitMenuBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				SwitchGameState(game, GameStateType::MainMenu);
			}
			break;
		}
		default:
			break;
		}
	}

	void InitGameStatePause(GameStatePauseData & data, Game & game)
	{
		// Fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		// Texts
		InitText(data.textPause, "GAME PAUSE", data.font, sf::Color::Yellow, 60);
		SetTextOrigin(data.textPause, TextOrigin::Center);

		// Buttons
		InitElement(data.continueBtn, "CONTINUE", data.font, sf::Color::White, sf::Color::Yellow, 40);
		SetTextOrigin(data.continueBtn.text, TextOrigin::Center);

		InitElement(data.exitMenuBtn, "MENU", data.font, sf::Color::White, sf::Color::Yellow, 40);
		SetTextOrigin(data.exitMenuBtn.text, TextOrigin::Center);
	}

	void DrawGameStatePause(GameStatePauseData & data, Game & game, sf::RenderWindow & window)
	{
		// Set postions
		data.textPause.setPosition(window.getSize().x / 2.f, 250.f);
		SetElementPosition(data.continueBtn, 200.f, 375.f);
		SetElementPosition(data.exitMenuBtn, 600.f, 375.f);

		// Draw
		window.draw(data.textPause);
		DrawElementOnWindow(data.continueBtn, window);
		DrawElementOnWindow(data.exitMenuBtn, window);
	}

	void UpdateGameStatePause(GameStatePauseData & data, Game & game, float timeDelta)
	{
		if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused)))
		{
			if (data.continueBtn.isFocused)
			{
				HighlightElement(data.continueBtn);
			}
			else if (data.exitMenuBtn.isFocused)
			{
				HighlightElement(data.exitMenuBtn);
			}

			if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
			{
				// TODO: May be add click sound...
			}
		}
		else
		{
			UnhighlightElement(data.continueBtn);
			UnhighlightElement(data.exitMenuBtn);
		}
	}

	void ShutdownGameStatePause(GameStatePauseData & data, Game & game)
	{
		UnhighlightElement(data.continueBtn);
		UnhighlightElement(data.exitMenuBtn);
	}
}