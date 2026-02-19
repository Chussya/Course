#include <cassert>
#include <string>
#include "Constants.h"
#include "Util.h"
#include "UI.h"

namespace ApplesGame
{
	void InitUI(UI& ui)
	{
		assert(ui.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));
		assert(ui.recordsFont.loadFromFile(RESOURCES_PATH + "Fonts/consola.ttf"));

		ui.scoreText.setFont(ui.font);
		ui.scoreText.setFillColor(sf::Color::White);
		ui.scoreText.setString("SCORES:");
		ui.scoreText.setCharacterSize(20);
		ui.scoreText.setPosition(0, 0);

		ui.movementNote.setFont(ui.font);
		ui.movementNote.setFillColor(sf::Color::White);
		ui.movementNote.setString("Use arrows keys for move");
		ui.movementNote.setCharacterSize(20);
		sf::FloatRect rctOfText = ui.movementNote.getLocalBounds();
		ui.movementNote.setOrigin(rctOfText.width, 0);
		ui.movementNote.setPosition(SCREEN_WIDTH - 1, 0);

		ui.gameOverText.setFont(ui.font);
		ui.gameOverText.setFillColor(sf::Color::Red);
		ui.gameOverText.setString("GAME OVER");
		ui.gameOverText.setCharacterSize(40);
		rctOfText = ui.gameOverText.getLocalBounds();
		ui.gameOverText.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		ui.gameOverText.setPosition(SCREEN_WIDTH / 2, 100);

		ui.menuText.setFont(ui.font);
		ui.menuText.setFillColor(sf::Color::White);
		ui.menuText.setString("Menu [Space]");
		ui.menuText.setCharacterSize(20);
		rctOfText = ui.menuText.getLocalBounds();
		ui.menuText.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		ui.menuText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);
	}

	void DrawUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.scoreText);
		window.draw(ui.movementNote);
	}

	void DrawGameOver(UI& ui, sf::RenderWindow& window, std::unordered_map<std::string, int>& records)
	{
		window.clear();
		
		// Init table
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

		// Init table records
		ui.leaderBoardText.setFont(ui.recordsFont);
		ui.leaderBoardText.setFillColor(sf::Color::White);
		ui.leaderBoardText.setString(tableOfLeaders);
		ui.leaderBoardText.setCharacterSize(20);
		sf::FloatRect rctOfText = ui.leaderBoardText.getLocalBounds();
		ui.leaderBoardText.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		ui.leaderBoardText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		// Draw game over window
		window.draw(ui.gameOverText);
		window.draw(ui.leaderBoardText);
		window.draw(ui.menuText);

		window.display();
	}

	void UpdateScores(UI& ui, int numEatenApples)
	{
		ui.scoreText.setString("SCORES: " + std::to_string(numEatenApples));
	}
}