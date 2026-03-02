#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace ApplesGame
{
	struct Game;

	struct GameStateGameOverData
	{
		float timeSinceGameOver = 0.f;

		// Font

		sf::Font font;
		sf::Font recordsFont;

		// Text

		sf::Text leaderBoardText;
		sf::Text gameOverText;
		sf::Text menuText;
	};

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& gameStateGameOver, Game& game, const sf::Event event);

	void InitGameStateGameOver(GameStateGameOverData& gameStateGameOver, Game& game);
	void DrawGameStateGameOver(GameStateGameOverData& gameStateGameOver, Game& game, sf::RenderWindow& window);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float timeDelta);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
}