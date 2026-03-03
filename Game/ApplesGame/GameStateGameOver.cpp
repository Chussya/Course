#include "GameStateGameOver.h"

#include <string>
#include <cassert>

#include "Game.h"
#include "Record.h"
#include "UtilString.h"
#include "UtilGraphic.h"
#include "GameSettings.h"

namespace ApplesGame
{
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
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
		std::string tableOfLeaders;

		tableOfLeaders = stringCenter("LEADERBOARD", SYM_TITLE, ROW_LENGTH);
		tableOfLeaders.push_back('\n');

		for (auto record : records)
		{
			tableOfLeaders.append(stringFormat(record.first, std::to_string(record.second), SYM_SEPARATE, ROW_LENGTH)).push_back('\n');
		}

		std::string end = "";
		end.resize(ROW_LENGTH, '=');
		tableOfLeaders.append(end);

		// Init texts
		InitText(data.gameOverText, "GAME OVER", data.font, sf::Color::Red, 40);
		SetTextOrigin(data.gameOverText, TextOrigin::Center);

		InitText(data.menuText, "Menu", data.font, sf::Color::White, 20);
		SetTextOrigin(data.menuText, TextOrigin::Center);

		InitText(data.leaderBoardText, tableOfLeaders, data.recordsFont, sf::Color::White, 25);
		SetTextOrigin(data.leaderBoardText, TextOrigin::Center);
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		// Set position
		data.gameOverText.setPosition(SCREEN_WIDTH_GAME / 2, 100);
		data.menuText.setPosition(SCREEN_WIDTH_GAME / 2, SCREEN_HEIGHT_GAME - 50);
		data.leaderBoardText.setPosition(SCREEN_WIDTH_GAME / 2, SCREEN_HEIGHT_GAME / 2);

		// Draw game over window
		window.draw(data.gameOverText);
		window.draw(data.leaderBoardText);
		window.draw(data.menuText);
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta)
	{
		data.timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		data.gameOverText.setFillColor(gameOverTextColor);
	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}
}