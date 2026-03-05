#pragma once

#include <SFML/Graphics.hpp>
#include "ButtonItem.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateLeaderboardData
	{
		int eventMask{ 0 };

		// Font

		sf::Font font;
		sf::Font recordsFont;

		// Text

		sf::Text leaderBoardText;
		sf::Text titleText;

		// Buttons

		ButtonItem backBtn;
	};

	void HandleGameStateLeaderboardWindowEvent(GameStateLeaderboardData& data, Game& game, const sf::Event event);
	void HandleKeyboardEvent(const sf::Event::KeyEvent event, GameStateLeaderboardData& data, Game& game);
	void HandleMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStateLeaderboardData& data, Game& game);
	void HandleMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStateLeaderboardData& data, Game& game);

	void InitGameStateLeaderboard(GameStateLeaderboardData& data, Game& game);
	void DrawGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, float timeDelta);
	void ShutdownGameStateLeaderboard(GameStateLeaderboardData& data, Game& game);
}