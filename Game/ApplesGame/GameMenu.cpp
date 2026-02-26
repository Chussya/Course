#include <cassert>
#include "StateGameOver.h"
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
			UpdateText(gameMenu, event.code);
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
			HighlightButton(gameMenu.startBtn, clr);
		}
		else
		{
			UnhighlightButton(gameMenu.startBtn);
		}

		if (IsGotFocus(gameMenu.modeBtn, mousePosition))
		{
			clr = sf::Color::Yellow;
			HighlightButton(gameMenu.modeBtn, clr);
		}
		else
		{
			UnhighlightButton(gameMenu.modeBtn);
		}

		if (IsGotFocus(gameMenu.exitBtn, mousePosition))
		{
			clr = sf::Color::Red;
			HighlightButton(gameMenu.exitBtn, clr);
		}
		else
		{
			UnhighlightButton(gameMenu.exitBtn);
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
				UnhighlightButton(gameMenu.startBtn);
				StartPlayingGame(gameMenu);
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
		gameMenu.window.create(sf::VideoMode(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "Apples Game");

		assert(gameMenu.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		gameMenu.titleTxt.setFont(gameMenu.font);
		gameMenu.titleTxt.setFillColor(sf::Color::White);
		gameMenu.titleTxt.setString("xXx APPLES GAME xXx");
		gameMenu.titleTxt.setCharacterSize(30);
		sf::FloatRect rctOfText = gameMenu.titleTxt.getLocalBounds();
		gameMenu.titleTxt.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameMenu.titleTxt.setPosition(gameMenu.window.getSize().x / 2.f, 30.f);

		InitButtonItem(gameMenu.startBtn, "Play", gameMenu.font, sf::Color::White, 20);
		SetButtonOrigin(gameMenu.startBtn, ButtonOrigin::Center);
		SetButtonPosition(gameMenu.startBtn, gameMenu.window.getSize().x / 2.f, 100.f);

		InitButtonItem(gameMenu.modeBtn, "Options", gameMenu.font, sf::Color::White, 20);
		SetButtonOrigin(gameMenu.modeBtn, ButtonOrigin::Center);
		SetButtonPosition(gameMenu.modeBtn, gameMenu.window.getSize().x / 2.f, 150.f);

		InitButtonItem(gameMenu.exitBtn, "Exit", gameMenu.font, sf::Color::White, 20);
		SetButtonOrigin(gameMenu.exitBtn, ButtonOrigin::Center);
		SetButtonPosition(gameMenu.exitBtn, gameMenu.window.getSize().x / 2.f, 200.f);

		// Init Records
		InitRecord(gameMenu.records);
	}

	void UpdateText(GameMenu& gameMenu, sf::Keyboard::Key key)
	{
		switch (key)
		{
		//case sf::Keyboard::Down: {
		//	gameMenu.textApplesNum.setString("Apples Num[Down/Up]: "
		//		+ std::to_string(gameMenu.gameSettings.numApples == NUM_APPLES_MIN ? NUM_APPLES_MIN : --gameMenu.gameSettings.numApples));
		//	break;
		//}
		//case sf::Keyboard::Up: {
		//	gameMenu.textApplesNum.setString("Apples Num[Down/Up]: "
		//		+ std::to_string(gameMenu.gameSettings.numApples == NUM_APPLES_MAX ? NUM_APPLES_MAX : ++gameMenu.gameSettings.numApples));
		//	break;
		//}
		//case sf::Keyboard::Left: {
		//	gameMenu.gameSettings.numApples = 20;
		//	gameMenu.textApplesNum.setString("Apples Num[Down/Up]: " + std::to_string(gameMenu.gameSettings.numApples));
		//	break;
		//}
		//case sf::Keyboard::Right: {
		//	gameMenu.gameSettings.numApples = NUM_APPLES_MAX;
		//	gameMenu.textApplesNum.setString("Apples Num[Down/Up]: " + std::to_string(gameMenu.gameSettings.numApples));
		//	break;
		//}
		case sf::Keyboard::Num1: {
			gameMenu.gameSettings.gameMode = ChangeGameMode(gameMenu.gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity));
			break;
		}
		case sf::Keyboard::Num2: {
			gameMenu.gameSettings.gameMode = ChangeGameMode(gameMenu.gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration));
			break;
		}
		case sf::Keyboard::Num3: {
			gameMenu.gameSettings.gameMode = ChangeGameMode(gameMenu.gameSettings.gameMode, static_cast<int>(EGameMode::Speed));
			break;
		}
		default:
			break;
		}

		std::string gameModeText{};

		if (gameMenu.gameSettings.gameMode & static_cast<int>(EGameMode::ApplesInfinity))
		{
			gameModeText = "ApplesInf;";
		}
		if (gameMenu.gameSettings.gameMode & static_cast<int>(EGameMode::Acceleration))
		{
			gameModeText += "Acceleration+;";
		}
		if (gameMenu.gameSettings.gameMode & static_cast<int>(EGameMode::Speed))
		{
			gameModeText += "Speed+;";
		}
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