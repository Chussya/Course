#include <cassert>
#include "ExitDialog.h"

namespace ApplesGame
{
	int HandleWindowEvent(GameExitDialog& gameExitDialog)
	{
		while (gameExitDialog.window.isOpen())
		{
			sf::Event event;
			while (gameExitDialog.window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					gameExitDialog.window.close();

				if (event.type == sf::Event::KeyReleased
					&& (event.key.code == sf::Keyboard::Y || event.key.code == sf::Keyboard::N))
				{
					gameExitDialog.window.close();
					return static_cast<int>(event.key.code);
				}
			}
		}
		return static_cast<int>(sf::Keyboard::N);
	}

	void InitGameExitDialog(GameExitDialog& gameExitDialog)
	{
		// Init UI
		gameExitDialog.window.create(sf::VideoMode(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "Apples Game");

		assert(gameExitDialog.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		gameExitDialog.textExit.setFont(gameExitDialog.font);
		gameExitDialog.textExit.setFillColor(sf::Color::White);
		gameExitDialog.textExit.setCharacterSize(20);
		gameExitDialog.textExit.setString("Do You want exit?\nYes [Y]\t\t\tNo [N]");
		sf::FloatRect rctOfText = gameExitDialog.textExit.getLocalBounds();
		gameExitDialog.textExit.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameExitDialog.textExit.setPosition(gameExitDialog.window.getSize().x / 2.f, gameExitDialog.window.getSize().y / 2.f);
	}

	void DrawGameExitDialogWindow(GameExitDialog& gameExitDialog)
	{
		gameExitDialog.window.clear();
		gameExitDialog.window.draw(gameExitDialog.textExit);
		gameExitDialog.window.display();
	}

	int ShowExitDialogWindow()
	{
		GameExitDialog gameExitDialog;

		InitGameExitDialog(gameExitDialog);
		DrawGameExitDialogWindow(gameExitDialog);

		return HandleWindowEvent(gameExitDialog);
	}
}