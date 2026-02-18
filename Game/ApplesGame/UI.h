#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace ApplesGame
{
	struct UI
	{
		sf::Font font;
		sf::Font recordsFont;
		sf::Text scoreText;
		sf::Text movementNote;
		sf::Text gameOverText;
		sf::Text leaderBoardText;
		sf::Text menuText;
	};

	void InitUI(UI& ui);
	void DrawUI(UI& ui, sf::RenderWindow& window);
	void DrawGameOver(UI& ui, sf::RenderWindow& window, std::unordered_map<std::string, int>& records);
	void UpdateScores(UI& ui, int numEatenApples);
}