#pragma once

namespace sf
{
	class Sprite;
}

namespace ApplesGame
{
	struct Vector2D
	{
		float x{ 0 };
		float y{ 0 };
	};

	typedef Vector2D Position2D;

	Position2D GetRandPosInScreen(float screenWidth, float screenHeight);
	bool IsRectanglesCollide(Position2D rect1Pos, Vector2D rect1Size, Position2D rect2Pos, Vector2D rect2Size);
	bool IsCirclesCollide(Position2D circle1Pos, float circle1Rad, Position2D circle2Pos, float circle2Rad);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}