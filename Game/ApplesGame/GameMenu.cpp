#include <cassert>
#include "StateGameOver.h"
#include "OptionsWindow.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"
#include "ExitDialog.h"
#include "Constants.h"
#include "GameMenu.h"
#include "Record.h"
#include "Game.h"

namespace ApplesGame
{
	void HandleGameMenuEvent(GameMenu& gameMenu)
	{
		while (gameMenu.window.isOpen())
		{
			sf::Event event;
			while (gameMenu.window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					gameMenu.window.close();

				if (event.type == sf::Event::KeyReleased)
				{
					HandleKeyboardEvent(event.key, gameMenu);
					gameMenu.isChanged = true;
				}
				if (event.type == sf::Event::MouseMoved)
				{
					HandleMouseMoveEvent(event.mouseMove, gameMenu);
					gameMenu.isChanged = true;
				}
				if (event.type == sf::Event::MouseButtonReleased)
				{
					HandleMouseClickEvent(event.mouseButton, gameMenu);
					gameMenu.isChanged = true;
				}
			}
			if (gameMenu.isChanged)
			{
				DrawMenuWindow(gameMenu);
			}
		}
	}

	void HandleKeyboardEvent(sf::Event::KeyEvent event, GameMenu& gameMenu)
	{
		switch (event.code)
		{
		case sf::Keyboard::Space: {
			StartPlayingGame(gameMenu);
			break;
		}
		case sf::Keyboard::Escape: {
			StartExitDialog(gameMenu);
			break;
		}
		default:
			break;
		}
	}

	void HandleMouseMoveEvent(sf::Event::MouseMoveEvent event, GameMenu& gameMenu)
	{
		Vector2D mousePosition = { static_cast<float>(event.x), static_cast<float>(event.y) };
		sf::Color clr;

		if (IsGotFocus(gameMenu.startBtn, mousePosition))
		{
			clr = sf::Color::Green;
			HighlightElement(gameMenu.startBtn, clr);
		}
		else
		{
			UnhighlightElement(gameMenu.startBtn);
		}

		if (IsGotFocus(gameMenu.modeBtn, mousePosition))
		{
			clr = sf::Color::Yellow;
			HighlightElement(gameMenu.modeBtn, clr);
		}
		else
		{
			UnhighlightElement(gameMenu.modeBtn);
		}

		if (IsGotFocus(gameMenu.exitBtn, mousePosition))
		{
			clr = sf::Color::Red;
			HighlightElement(gameMenu.exitBtn, clr);
		}
		else
		{
			UnhighlightElement(gameMenu.exitBtn);
		}
	}

	void HandleMouseClickEvent(sf::Event::MouseButtonEvent event, GameMenu& gameMenu)
	{
		switch (event.button)
		{
		case sf::Mouse::Left:
		{
			if (gameMenu.startBtn.isFocused)
			{
				UnhighlightElement(gameMenu.startBtn);
				StartPlayingGame(gameMenu);
			}
			else if (gameMenu.modeBtn.isFocused)
			{
				UnhighlightElement(gameMenu.modeBtn);
				StartOptionsWindow(gameMenu.gameSettings);
			}
			else if (gameMenu.exitBtn.isFocused)
			{
				UnhighlightElement(gameMenu.exitBtn);
				StartExitDialog(gameMenu);
			}
			break;
		}
		default:
			break;
		}
	}

	void InitMenu(GameMenu& gameMenu)
	{
		// Init UI
		gameMenu.window.create(sf::VideoMode(SCREEN_WIDTH_GAME / 2, SCREEN_HEIGHT_GAME / 2), "Apples Game");

		assert(gameMenu.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		gameMenu.titleTxt.setFont(gameMenu.font);
		gameMenu.titleTxt.setFillColor(sf::Color::White);
		gameMenu.titleTxt.setString("xXx APPLES GAME xXx");
		gameMenu.titleTxt.setCharacterSize(30);
		sf::FloatRect rctOfText = gameMenu.titleTxt.getLocalBounds();
		gameMenu.titleTxt.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameMenu.titleTxt.setPosition(gameMenu.window.getSize().x / 2.f, 30.f);

		InitElement(gameMenu.startBtn, "Play", gameMenu.font, sf::Color::White, 20);
		SetTextOrigin(gameMenu.startBtn.text, TextOrigin::Center);
		SetElementPosition(gameMenu.startBtn, gameMenu.window.getSize().x / 2.f, 100.f);

		InitElement(gameMenu.modeBtn, "Options", gameMenu.font, sf::Color::White, 20);
		SetTextOrigin(gameMenu.modeBtn.text, TextOrigin::Center);
		SetElementPosition(gameMenu.modeBtn, gameMenu.window.getSize().x / 2.f, 150.f);

		InitElement(gameMenu.exitBtn, "Exit", gameMenu.font, sf::Color::White, 20);
		SetTextOrigin(gameMenu.exitBtn.text, TextOrigin::Center);
		SetElementPosition(gameMenu.exitBtn, gameMenu.window.getSize().x / 2.f, 200.f);

		// Init Records
		InitRecord(gameMenu.records);
	}

	void DrawMenuWindow(GameMenu& gameMenu)
	{
		gameMenu.window.clear();
		gameMenu.window.draw(gameMenu.titleTxt);
		gameMenu.window.draw(gameMenu.startBtn.text);
		gameMenu.window.draw(gameMenu.modeBtn.text);
		gameMenu.window.draw(gameMenu.exitBtn.text);

		gameMenu.isChanged = false;

		gameMenu.window.display();
	}

	void DeinitializeMenu(GameMenu& gameMenu)
	{
		if (gameMenu.window.isOpen())
			gameMenu.window.close();

		if (!gameMenu.records.empty())
			gameMenu.records.clear();
	}

	void StartPlayingGame(GameMenu& gameMenu)
	{
		gameMenu.window.setVisible(false);

		int resultOfGame = StartGame(gameMenu.gameSettings, gameMenu.playerScore);
		
		switch (static_cast<GameState>(resultOfGame))
		{
		case GameState::GameOver: {
			// Acualize player's scores
			if (gameMenu.records[PLAYER_INDEX] < *gameMenu.playerScore)
			{
				gameMenu.records[PLAYER_INDEX] = *gameMenu.playerScore;
			}
			SortByScores(gameMenu.records);

			// Game over state
			ShowGameOverWindow(gameMenu.records);
		}
		default:
			break;
		}
		gameMenu.window.setVisible(true);
	}

	void StartExitDialog(GameMenu& gameMenu)
	{
		gameMenu.window.setVisible(false);

		switch (ShowExitDialogWindow())
		{
		case sf::Keyboard::Y: {
			gameMenu.window.close();
			break;
		}
		default:
			gameMenu.window.setVisible(true);
			break;
		}
	}

	void StartMenu()
	{
		int seed = (int)time(nullptr);
		srand(seed);

		GameMenu gameMenu;

		InitMenu(gameMenu);
		DrawMenuWindow(gameMenu);

		HandleGameMenuEvent(gameMenu);

		DeinitializeMenu(gameMenu);
	}
}