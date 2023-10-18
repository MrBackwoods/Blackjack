#include "pch.h"
#include "player.h"
#include <iostream>

void Player::ClearHandAndStatus() 
{
	handValue = 0;
	hand.clear();
	stays = false;
}

int Player::HandCount()
{
	return hand.size();
}

void Player::AddCardToHand(std::pair<std::string, std::string> card)
{
	const std::map<std::string, int> cardValues = {
	{ "Demoted Ace", 1 }, { "Ace", 11 }, { "Two", 2 }, { "Three", 3 }, { "Four", 4 },
	{ "Five", 5 }, { "Six", 6 }, { "Seven", 7 }, { "Eight", 8 },
	{ "Nine", 9 }, { "Ten", 10 }, { "Jack", 10 }, { "Queen", 10 }, { "King", 10 }
	};

	hand.push_back(card);
	handValue += cardValues.at(card.first);
	std::cout << "Dealer dealed " << card.first << " of " << card.second + " to " << name << std::endl;

	// If player goes over but has an ace, it counts as 1 instead of 11
	if (handValue > 21)
	{
		for (auto& card : hand)
		{
			if (handValue > 21 && card.first == "Ace")
			{
				handValue -= 10;
				card.first = "Demoted Ace";
				std::cout << "Counting ace as 1 instead of 11" << std::endl;
			}
		}
	}
}