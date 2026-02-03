#include <cassert>
#include "Constants.h"
#include "UI.h"

namespace ApplesGame
{
	void InitUI(UI& ui)
	{
		assert(ui.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

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
		ui.gameOverText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}

	void DrawUI(UI& ui, sf::RenderWindow& window)
	{
		window.draw(ui.scoreText);
		window.draw(ui.movementNote);
	}

	void DrawGameOver(UI& ui, sf::RenderWindow& window)
	{
		window.clear();
		window.draw(ui.gameOverText);
		window.display();
	}

	void UpdateScores(UI& ui, int numEatenApples)
	{
		ui.scoreText.setString("SCORES: " + std::to_string(numEatenApples));
	}
}