#pragma once

#include <SFML/Graphics.hpp>

#include "ButtonItem.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateExitDialogData
	{
		int eventMask{ 0 };

		// Font

		sf::Font font;

		// Text

		sf::Text textExit;

		// Buttons

		ButtonItem yesBtn;
		ButtonItem noBtn;
	};

	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event event);
	void HandleGameStateExitDialogKeyboardEvent(const sf::Event::KeyEvent event, GameStateExitDialogData& data, Game& game);
	void HandleGameStateExitDialogMouseMoveEvent(const sf::Event::MouseMoveEvent event, GameStateExitDialogData& data, Game& game);
	void HandleGameStateExitDialogMouseClickEvent(const sf::Event::MouseButtonEvent event, GameStateExitDialogData& data, Game& game);

	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float timeDelta);
	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game);
}