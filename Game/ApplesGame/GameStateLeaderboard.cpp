#include "GameStateLeaderboard.h"

#include <string>
#include <cassert>

#include "Game.h"
#include "Record.h"
#include "UtilString.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"

namespace ApplesGame
{
	void HandleGameStateLeaderboardWindowEvent(GameStateLeaderboardData& data, Game& game, const sf::Event event)
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

	void HandleKeyboardEvent(const sf::Event::KeyEvent event, GameStateLeaderboardData& data, Game& game)
	{
		switch (event.code)
		{
		case sf::Keyboard::BackSpace:
		{
			SwitchGameState(game, GameStateType::MainMenu);
			break;
		}
		default:
			break;
		}
	}

	void HandleMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStateLeaderboardData& data, Game& game)
	{
		Vector2D mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };

		if (IsGotFocus(data.backBtn, mousePosition))
		{
			TurnOnMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
		else
		{
			TurnOffMask(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused));
		}
	}

	void HandleMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStateLeaderboardData& data, Game& game)
	{
		switch (event.button)
		{
		case sf::Mouse::Left:
		{
			if (data.backBtn.isFocused)
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

	void InitGameStateLeaderboard(GameStateLeaderboardData & data, Game & game)
	{
		// Init fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));
		assert(data.recordsFont.loadFromFile(RESOURCES_PATH + "Fonts/consola.ttf"));

		// Actualize records
		if (game.records["Player"] < *game.ptrPlayerScores)
		{
			game.records["Player"] = *game.ptrPlayerScores;
		}

		// Sort records
		Records records = SortByScores(game.records);

		// Leaderboard definition
		std::string tableOfLeaders = "";
		tableOfLeaders.resize(ROW_LENGTH, '=');
		tableOfLeaders.push_back('\n');

		for (auto record : records)
		{
			tableOfLeaders.append(stringFormat(record.first, std::to_string(record.second), SYM_SEPARATE, ROW_LENGTH)).push_back('\n');
		}

		std::string end = "";
		end.resize(ROW_LENGTH, '=');
		tableOfLeaders.append(end);

		// Init texts
		InitText(data.titleText, "LEADERBOARD", data.font, sf::Color::Blue, 40);
		SetTextOrigin(data.titleText, TextOrigin::Center);

		InitElement(data.backBtn, "Back", data.font, sf::Color::White, sf::Color::Yellow, 30);
		SetTextOrigin(data.backBtn.text, TextOrigin::Center);

		InitText(data.leaderBoardText, tableOfLeaders, data.recordsFont, sf::Color::White, 25);
		SetTextOrigin(data.leaderBoardText, TextOrigin::Center);
	}

	void DrawGameStateLeaderboard(GameStateLeaderboardData & data, Game & game, sf::RenderWindow & window)
	{
		// Set position
		data.titleText.setPosition(SCREEN_WIDTH_GAME / 2, 100);
		data.leaderBoardText.setPosition(SCREEN_WIDTH_GAME / 2, SCREEN_HEIGHT_GAME / 2);
		SetElementPosition(data.backBtn, SCREEN_WIDTH_GAME / 2, SCREEN_HEIGHT_GAME - 50);

		// Draw game over window
		window.draw(data.titleText);
		window.draw(data.leaderBoardText);
		DrawElementOnWindow(data.backBtn, window);
	}

	void UpdateGameStateLeaderboard(GameStateLeaderboardData & data, Game & game, float timeDelta)
	{
		if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnFocused)))
		{
			if (data.backBtn.isFocused)
			{
				HighlightElement(data.backBtn);
			}

			if (IsBitMaskOn(data.eventMask, static_cast<int>(EGameWindowEvent::OnClick)))
			{
				// TODO: May be add click sound...
			}
		}
		else
		{
			UnhighlightElement(data.backBtn);
		}
	}

	void ShutdownGameStateLeaderboard(GameStateLeaderboardData & data, Game & game)
	{
		UnhighlightElement(data.backBtn);
	}
}