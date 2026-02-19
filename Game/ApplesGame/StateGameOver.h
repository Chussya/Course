#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace ApplesGame
{
	struct StateGameOver
	{
		// Font
		sf::Font font;
		sf::Font recordsFont;

		// Text
		sf::Text leaderBoardText;
		sf::Text gameOverText;
		sf::Text menuText;

		// Window
		sf::RenderWindow window;
	};

	int HandleWindowEvent(StateGameOver& stateGameOver);
	void InitGameOver(StateGameOver& stateGameOver, std::unordered_map<std::string, int>& records);
	void DrawGameOverWindow(StateGameOver& stateGameOver);
	int ShowGameOverWindow(std::unordered_map<std::string, int>& records);
}