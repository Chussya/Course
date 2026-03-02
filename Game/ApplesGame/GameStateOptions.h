#pragma once
#include <SFML/Graphics.hpp>

#include "TextItem.h"
#include "ToggleButton.h"
#include "GameSettings.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateOptionsData
	{
		int eventMask{ 0 };

		// Fonts

		sf::Font font;

		// Texts

		sf::Text infApplesText;
		sf::Text accBoostText;
		sf::Text bonusSpeedText;
		sf::Text applesNumText;

		// Text items

		TextItem applesNumTextItem;

		// Buttons

		ToggleButton infApplesBtn;
		ToggleButton accBoostBtn;
		ToggleButton bonusSpeedBtn;
	};

	// Event's functions

	void HandleGameStateOptionsWindowEvent(GameStateOptionsData& data, Game& game, const sf::Event event);
	void HandleGameStateOptionsKeyboardEvent(sf::Event::KeyEvent event, GameStateOptionsData& data, Game& game);
	void HandleGameStateOptionsMouseMoveEvent(sf::Event::MouseMoveEvent event, GameStateOptionsData& data, Game& game);
	void HandleGameStateOptionsMouseClickEvent(sf::Event::MouseButtonEvent event, GameStateOptionsData& data, Game& game);

	// Standard functions

	void InitGameStateOptions(GameStateOptionsData& data, Game& game);
	void DrawGameStateOptions(GameStateOptionsData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateOptions(GameStateOptionsData& data, Game& game, float timeDelta);
	void ShutdownGameStateOptions(GameStateOptionsData& data, Game& game);
}