#pragma once
#include <list>

#include "TextItem.h"
#include "ButtonItem.h"

namespace ApplesGame
{
	enum class EHorizontalDirection
	{
		None = 0,
		Left,
		Right,
	};

	enum class ENavigationListElement
	{
		None = 0,
		Button,
		TextItem,
	};

	struct CustomElement
	{
		bool isSelected{ false };

		TextItem* textItem{ nullptr };
		ButtonItem* buttonItem{ nullptr };
	};

	void InsertButton(std::list<CustomElement>& list, ButtonItem& element);
	void InsertTextItem(std::list<CustomElement>& list, TextItem& element);
	void SelectElement(std::list<CustomElement>& list, EHorizontalDirection direction);
	ButtonItem* GetElementButton(const CustomElement& element);
	TextItem* GetElementText(const CustomElement& element);
	bool IsGotFocus(CustomElement& element, const Vector2D mousePos);

	ENavigationListElement WhichElementHas(const CustomElement& element);
}