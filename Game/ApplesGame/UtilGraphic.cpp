#include "UtilGraphic.h"

#include "Player.h"

namespace ApplesGame
{
	void InitText(sf::Text& text, std::string s, sf::Font& font, sf::Color colorText, unsigned int charSize)
	{
		text.setFont(font);
		text.setFillColor(colorText);
		text.setString(s);
		text.setCharacterSize(charSize);
	}

	void SetTextOrigin(sf::Text& text, TextOrigin textOrigin)
	{
		sf::FloatRect localRect = text.getLocalBounds();

		switch (textOrigin)
		{
		case ApplesGame::TextOrigin::LeftTop:
			text.setOrigin(0.f, 0.f);
			break;
		case ApplesGame::TextOrigin::MidTop:
			text.setOrigin(localRect.width / 2.f, 0.f);
			break;
		case ApplesGame::TextOrigin::RightTop:
			text.setOrigin(localRect.width, 0.f);
			break;
		case ApplesGame::TextOrigin::Center:
			text.setOrigin(localRect.width / 2.f, localRect.height / 2.f);
			break;
		case ApplesGame::TextOrigin::LeftBottom:
			text.setOrigin(0.f, localRect.height);
			break;
		case ApplesGame::TextOrigin::MidBottom:
			text.setOrigin(localRect.width / 2.f, localRect.height);
			break;
		case ApplesGame::TextOrigin::RightBottom:
			text.setOrigin(localRect.width, localRect.height);
			break;
		default:
			text.setOrigin(0.f, 0.f);
			break;
		}
	}

	void BalancedPlayerRotation(Player& player, PlayerDirection newDirection)
	{
		if (player.direction != newDirection)
		{
			player.sprite.setRotation((float)newDirection);

			// Flip player's sprite per siding (left <-> right)
			int width = (int)player.sprite.getTexture()->getSize().x;
			int height = (int)player.sprite.getTexture()->getSize().y;

			if (newDirection == PlayerDirection::Left)
			{
				player.sprite.setTextureRect(sf::IntRect(0, height, width, -height));
			}
			if (newDirection == PlayerDirection::Right)
			{
				player.sprite.setTextureRect(sf::IntRect(0, 0, width, height));
			}
		}
	}

	bool IsObjectColdidedBorders(Position2D pos)
	{
		return pos.y - PLAYER_SIZE / 2.f <= 0 || pos.y + PLAYER_SIZE / 2.f >= SCREEN_HEIGHT_GAME
			|| pos.x - PLAYER_SIZE / 2.f <= 0 || pos.x + PLAYER_SIZE / 2.f >= SCREEN_WIDTH_GAME;
	}
}