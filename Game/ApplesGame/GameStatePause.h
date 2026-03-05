#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "CustomElement.h"

namespace ApplesGame
{
	struct Game;

	struct GameStatePauseData
	{
		int eventMask{ 0 };

		// Font

		sf::Font font;

		// Text

		sf::Text textPause;

		// Buttons

		ButtonItem continueBtn;
		ButtonItem exitMenuBtn;

		// List Elements
		std::list<CustomElement> elementList;
	};

	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, const sf::Event event);
	void HandleGameStatePauseKeyboardEvent(const sf::Event::KeyEvent event, GameStatePauseData& data, Game& game);
	void HandleGameStatePauseMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStatePauseData& data, Game& game);
	void HandleGameStatePauseMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStatePauseData& data, Game& game);

	void InitGameStatePause(GameStatePauseData& data, Game& game);
	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStatePause(GameStatePauseData& data, Game& game, float timeDelta);
	void ShutdownGameStatePause(GameStatePauseData& data, Game& game);
}