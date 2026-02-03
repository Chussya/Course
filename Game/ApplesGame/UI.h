#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct UI
	{
		sf::Font font;
		sf::Text scoreText;
		sf::Text movementNote;
		sf::Text gameOverText;
	};

	void InitUI(UI& ui);

	void DrawUI(UI& ui, sf::RenderWindow& window);

	void DrawGameOver(UI& ui, sf::RenderWindow& window);

	void UpdateScores(UI& ui, int numEatenApples);
}