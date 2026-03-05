#include <cassert>
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"
#include "Game.h"

namespace ApplesGame
{
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			HandleKeyboardEvent(event.key, data, game);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			HandleMouseMoveEvent(event.mouseMove, data, game);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			HandleMouseClickEvent(event.mouseButton, data, game);
		}
	}

	void HandleKeyboardEvent(const sf::Event::KeyEvent event, GameStateMainMenuData& data, Game& game)
	{
		switch (event.code)
		{
		case sf::Keyboard::Space: {
			SwitchGameState(game, GameStateType::Playing);
			break;
		}
		case sf::Keyboard::Escape: {
			PushGameState(game, GameStateType::ExitDialog, true);
			break;
		}
		default:
			break;
		}
	}

	void HandleMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStateMainMenuData& data, Game& game)
	{
		Vector2D mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
		
		if (IsGotFocus(data.startBtn, mousePosition)
			|| IsGotFocus(data.leaderboardBtn, mousePosition)
			|| IsGotFocus(data.optionsBtn, mousePosition)
			|| IsGotFocus(data.exitBtn, mousePosition))
		{
			TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
		else
		{
			TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
	}

	void HandleMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStateMainMenuData& data, Game& game)
	{
		switch (event.button)
		{
		case sf::Mouse::Left:
		{
			if (data.startBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				SwitchGameState(game, GameStateType::Playing);
			}
			else if (data.leaderboardBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				SwitchGameState(game, GameStateType::Leaderboard);
			}
			else if (data.optionsBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				SwitchGameState(game, GameStateType::Options);
			}
			else if (data.exitBtn.isFocused)
			{
				TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick));
				PushGameState(game, GameStateType::ExitDialog, true);
			}
			break;
		}
		default:
			break;
		}
	}

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// Fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		// Texts
		InitText(data.titleTxt, "xXx APPLES GAME xXx", data.font, sf::Color::White, 60);
		SetTextOrigin(data.titleTxt, TextOrigin::Center);

		InitElement(data.startBtn, "Play", data.font, sf::Color::White, sf::Color::Green, 50);
		SetTextOrigin(data.startBtn.text, TextOrigin::Center);

		InitElement(data.leaderboardBtn, "Leaderboard", data.font, sf::Color::White, sf::Color::Blue, 50);
		SetTextOrigin(data.leaderboardBtn.text, TextOrigin::Center);

		InitElement(data.optionsBtn, "Options", data.font, sf::Color::White, sf::Color::Yellow, 50);
		SetTextOrigin(data.optionsBtn.text, TextOrigin::Center);

		InitElement(data.exitBtn, "Exit", data.font, sf::Color::White, sf::Color::Red, 50);
		SetTextOrigin(data.exitBtn.text, TextOrigin::Center);
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		// Set positions
		data.titleTxt.setPosition(window.getSize().x / 2.f, 30.f);
		SetElementPosition(data.startBtn, window.getSize().x / 2.f, 160.f);
		SetElementPosition(data.leaderboardBtn, window.getSize().x / 2.f, 260.f);
		SetElementPosition(data.optionsBtn, window.getSize().x / 2.f, 360.f);
		SetElementPosition(data.exitBtn, window.getSize().x / 2.f, 460.f);

		// Draw elements
		window.draw(data.titleTxt);
		DrawElementOnWindow(data.startBtn, window);
		DrawElementOnWindow(data.leaderboardBtn, window);
		DrawElementOnWindow(data.optionsBtn, window);
		DrawElementOnWindow(data.exitBtn, window);
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta)
	{
		if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused)))
		{
			if (data.startBtn.isFocused)
			{
				HighlightElement(data.startBtn);
			}
			else if (data.leaderboardBtn.isFocused)
			{
				HighlightElement(data.leaderboardBtn);
			}
			else if (data.optionsBtn.isFocused)
			{
				HighlightElement(data.optionsBtn);
			}
			else if (data.exitBtn.isFocused)
			{
				HighlightElement(data.exitBtn);
			}

			if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
			{
				// TODO: May be add click sound...
			}
		}
		else
		{
			UnhighlightElement(data.startBtn);
			UnhighlightElement(data.leaderboardBtn);
			UnhighlightElement(data.optionsBtn);
			UnhighlightElement(data.exitBtn);
		}
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		UnhighlightElement(data.startBtn);
		UnhighlightElement(data.leaderboardBtn);
		UnhighlightElement(data.optionsBtn);
		UnhighlightElement(data.exitBtn);
	}
}