#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct UI
	{
		// Font
		sf::Font font;

		// Text
		sf::Text scoreText;
		sf::Text movementNote;
	};

	void InitUI(UI& ui);
	void DrawUI(UI& ui, sf::RenderWindow& window);
	void UpdateScores(UI& ui, int numEatenApples);
}