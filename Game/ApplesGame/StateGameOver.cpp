#include <cassert>
#include <string>
#include "StateGameOver.h"
#include "GameSettings.h"
#include "Util.h"

namespace ApplesGame
{
	int HandleWindowEvent(StateGameOver& stateGameOver)
	{
		while (stateGameOver.window.isOpen())
		{
			sf::Event event;
			while (stateGameOver.window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					stateGameOver.window.close();

				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
				{
					stateGameOver.window.close();
					return static_cast<int>(event.key.code);
				}
			}
		}
		return 0;
	}

	void InitGameOver(StateGameOver& stateGameOver, std::unordered_map<std::string, int>& records)
	{
		// Init window
		stateGameOver.window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

		// Init fonts
		assert(stateGameOver.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));
		assert(stateGameOver.recordsFont.loadFromFile(RESOURCES_PATH + "Fonts/consola.ttf"));

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
		stateGameOver.gameOverText.setFont(stateGameOver.font);
		stateGameOver.gameOverText.setFillColor(sf::Color::Red);
		stateGameOver.gameOverText.setString("GAME OVER");
		stateGameOver.gameOverText.setCharacterSize(40);
		sf::FloatRect rctOfText = stateGameOver.gameOverText.getLocalBounds();
		stateGameOver.gameOverText.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		stateGameOver.gameOverText.setPosition(SCREEN_WIDTH / 2, 100);

		stateGameOver.menuText.setFont(stateGameOver.font);
		stateGameOver.menuText.setFillColor(sf::Color::White);
		stateGameOver.menuText.setString("Menu [Space]");
		stateGameOver.menuText.setCharacterSize(20);
		rctOfText = stateGameOver.menuText.getLocalBounds();
		stateGameOver.menuText.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		stateGameOver.menuText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);

		stateGameOver.leaderBoardText.setFont(stateGameOver.recordsFont);
		stateGameOver.leaderBoardText.setFillColor(sf::Color::White);
		stateGameOver.leaderBoardText.setString(tableOfLeaders);
		stateGameOver.leaderBoardText.setCharacterSize(20);
		rctOfText = stateGameOver.leaderBoardText.getLocalBounds();
		stateGameOver.leaderBoardText.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		stateGameOver.leaderBoardText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}

	void DrawGameOverWindow(StateGameOver& stateGameOver)
	{
		stateGameOver.window.clear();

		// Draw game over window
		stateGameOver.window.draw(stateGameOver.gameOverText);
		stateGameOver.window.draw(stateGameOver.leaderBoardText);
		stateGameOver.window.draw(stateGameOver.menuText);

		stateGameOver.window.display();
	}

	int ShowGameOverWindow(std::unordered_map<std::string, int>& records)
	{
		StateGameOver stateGameOver;

		InitGameOver(stateGameOver, records);
		DrawGameOverWindow(stateGameOver);

		return HandleWindowEvent(stateGameOver);
	}
}