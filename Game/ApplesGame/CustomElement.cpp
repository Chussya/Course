#include "CustomElement.h"

namespace ApplesGame
{
	void InsertButton(std::list<CustomElement>& list, ButtonItem& element)
	{
		CustomElement ce = CustomElement();
		ce.buttonItem = &element;

		list.push_back(ce);
	}

	void InsertTextItem(std::list<CustomElement>& list, TextItem& element)
	{
		CustomElement ce = CustomElement();
		ce.textItem = &element;

		list.push_back(ce);
	}

	void SelectElement(std::list<CustomElement>& list, EHorizontalDirection direction)
	{
		CustomElement* ptrElement{ nullptr };
		std::list<CustomElement>::iterator oldElementIterator{ list.end() };

		for (auto iterator = list.begin(); iterator != list.end(); ++iterator)
		{
			if (iterator->isSelected)
			{
				iterator->isSelected = false;
				oldElementIterator = iterator;
				ptrElement = &*iterator;
				break;
			}
		}

		if (oldElementIterator == list.end())
		{
			ptrElement = &list.front();
		}
		else
		{
			switch (direction)
			{
			case ApplesGame::EHorizontalDirection::None:
				ptrElement = &list.front();
				break;
			case ApplesGame::EHorizontalDirection::Left:
			{
				if (ptrElement == &list.front())
				{
					ptrElement = &list.back();
				}
				else
				{
					ptrElement = &*std::prev(oldElementIterator);
				}
				break;
			}
			case ApplesGame::EHorizontalDirection::Right:
			{
				if (ptrElement == &list.back())
				{
					ptrElement = &list.front();
				}
				else
				{
					ptrElement = &*std::next(oldElementIterator);
				}
				break;
			}
			default:
				ptrElement = &list.front();
				break;
			}
		}
		ptrElement->isSelected = true;
	}

	ButtonItem* GetElementButton(const CustomElement& element)
	{
		return element.buttonItem;
	}

	TextItem* GetElementText(const CustomElement& element)
	{
		return element.textItem;
	}

	bool IsGotFocus(CustomElement& element, const Vector2D mousePos)
	{
		if (element.buttonItem != nullptr)
		{
			sf::FloatRect globalRect = element.buttonItem->text.getGlobalBounds();
			
			element.buttonItem->isFocused = globalRect.top <= mousePos.y && globalRect.top + globalRect.height >= mousePos.y
				&& globalRect.left <= mousePos.x && globalRect.left + globalRect.width >= mousePos.x;

			element.isSelected = element.buttonItem->isFocused;

			return element.isSelected;
		}
		else if (element.textItem != nullptr)
		{
			sf::FloatRect globalRect = element.textItem->text.getGlobalBounds();

			element.isSelected = IsGotFocus(*element.textItem, mousePos);

			return element.isSelected;
		}
		return false;
	}

	ENavigationListElement WhichElementHas(const CustomElement& element)
	{
		if (element.buttonItem != nullptr)
		{
			return ENavigationListElement::Button;
		} else if (element.textItem != nullptr)
		{
			return ENavigationListElement::TextItem;
		} else
		{
			return ENavigationListElement::None;
		}
	}
}