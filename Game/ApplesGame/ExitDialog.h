#pragma once

#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct GameExitDialog
	{
		sf::Font font;

		// Exit dialog text
		sf::Text textExit;

		sf::RenderWindow window;
	};

	int HandleWindowEvent(GameExitDialog& gameExitDialog);
	void InitGameExitDialog(GameExitDialog& gameExitDialog);
	void DrawGameExitDialogWindow(GameExitDialog& gameExitDialog);
	int ShowExitDialogWindow();
}