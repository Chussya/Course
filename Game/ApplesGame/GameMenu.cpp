#include <cassert>
#include "Constants.h"
#include "GameMenu.h"
#include "Game.h"

namespace ApplesGame
{
	void InitMenu(GameMenu& gameMenu)
	{
		gameMenu.window.create(sf::VideoMode(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "Apples Game");

		gameMenu.font;
		assert(gameMenu.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		gameMenu.textTitle.setFont(gameMenu.font);
		gameMenu.textTitle.setFillColor(sf::Color::White);
		gameMenu.textTitle.setString("xXx APPLES GAME xXx");
		gameMenu.textTitle.setCharacterSize(30);
		sf::FloatRect rctOfText = gameMenu.textTitle.getLocalBounds();
		gameMenu.textTitle.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameMenu.textTitle.setPosition(gameMenu.window.getSize().x / 2.f, 30.f);

		gameMenu.textMode.setFont(gameMenu.font);
		gameMenu.textMode.setFillColor(sf::Color::White);
		gameMenu.textMode.setString("Mode[1-3]: ");
		gameMenu.textMode.setCharacterSize(20);
		rctOfText = gameMenu.textMode.getLocalBounds();
		gameMenu.textMode.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameMenu.textMode.setPosition(gameMenu.window.getSize().x / 2.f, 100.f);

		gameMenu.textApplesNum.setFont(gameMenu.font);
		gameMenu.textApplesNum.setFillColor(sf::Color::White);
		gameMenu.textApplesNum.setString("Apples Num[Down/Up]: " + std::to_string(gameMenu.gameSettings.numApples));
		gameMenu.textApplesNum.setCharacterSize(20);
		rctOfText = gameMenu.textApplesNum.getLocalBounds();
		gameMenu.textApplesNum.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameMenu.textApplesNum.setPosition(gameMenu.window.getSize().x / 2.f, 140.f);

		gameMenu.textPlayExit.setFont(gameMenu.font);
		gameMenu.textPlayExit.setFillColor(sf::Color::White);
		gameMenu.textPlayExit.setCharacterSize(20);
		gameMenu.textPlayExit.setString("Play [Space]\t\t\tExit [Esc]");
		rctOfText = gameMenu.textPlayExit.getLocalBounds();
		gameMenu.textPlayExit.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameMenu.textPlayExit.setPosition(gameMenu.window.getSize().x / 2.f, 180.f);
	}

	void UpdateText(GameMenu& gameMenu, sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Down: {
			gameMenu.textApplesNum.setString("Apples Num[Down/Up]: "
				+ std::to_string(gameMenu.gameSettings.numApples == NUM_APPLES_MIN ? NUM_APPLES_MIN : --gameMenu.gameSettings.numApples));
			break;
		}
		case sf::Keyboard::Up: {
			gameMenu.textApplesNum.setString("Apples Num[Down/Up]: "
				+ std::to_string(gameMenu.gameSettings.numApples == NUM_APPLES_MAX ? NUM_APPLES_MAX : ++gameMenu.gameSettings.numApples));
			break;
		}
		case sf::Keyboard::Left: {
			gameMenu.gameSettings.numApples = 20;
			gameMenu.textApplesNum.setString("Apples Num[Down/Up]: " + std::to_string(gameMenu.gameSettings.numApples));
			break;
		}
		case sf::Keyboard::Right: {
			gameMenu.gameSettings.numApples = NUM_APPLES_MAX;
			gameMenu.textApplesNum.setString("Apples Num[Down/Up]: " + std::to_string(gameMenu.gameSettings.numApples));
			break;
		}
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

		gameMenu.textMode.setString("Mode[1-3]: " + gameModeText);
	}

	void DrawWindow(GameMenu& gameMenu)
	{
		gameMenu.window.clear();
		gameMenu.window.draw(gameMenu.textTitle);

		sf::FloatRect rctOfText = gameMenu.textMode.getLocalBounds();
		gameMenu.textMode.setOrigin(rctOfText.width / 2.f, rctOfText.height / 2.f);
		gameMenu.textMode.setPosition(gameMenu.window.getSize().x / 2.f, 100.f);

		gameMenu.window.draw(gameMenu.textMode);
		gameMenu.window.draw(gameMenu.textApplesNum);
		gameMenu.window.draw(gameMenu.textPlayExit);
		gameMenu.window.display();
	}

	void StartMenu()
	{
		bool isContinue = true;
		bool redrawWindow = false;
		GameMenu gameMenu;

		InitMenu(gameMenu);
		DrawWindow(gameMenu);

		while (isContinue)
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
						UpdateText(gameMenu, event.key.code);
						redrawWindow = true;
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					redrawWindow = true;
					gameMenu.window.setVisible(false);
					StartGame((int)time(nullptr), gameMenu.gameSettings);
					gameMenu.window.setVisible(true);
				} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					gameMenu.window.close();
					isContinue = false;
				}

				if (redrawWindow)
				{
					redrawWindow = false;
					DrawWindow(gameMenu);
				}
			}
		}
	}
}