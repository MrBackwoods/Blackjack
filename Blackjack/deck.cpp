#include "pch.h"
#include "deck.h"
#include <iostream>
#include <random>
#include <windows.h>

// Resetting and shuffling deck at constructor
Deck::Deck()
{
    ResetDeck();
};

int Deck::DeckCount() 
{
	return cards.size();
}

// Resetting deck
void Deck::ResetDeck()
{
	const std::string faces[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	const std::string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };

	for (const std::string& suit : suits) {
		for (const std::string& face : faces) {
            cards.push_back(make_pair(face, suit));
        }
    }

	std::random_device rd;
	std::default_random_engine rng(rd());
	std::shuffle(cards.begin(), cards.end(), rng);
	std::cout << "Deck has been shuffled" << std::endl;
};

// Dealing a card
void Deck::DealCard(Player& player, int delay)
{
	if (cards.empty()) 
	{
		std::cerr << "Error: Deck is empty." << std::endl;
	}

	// Dealing card to player's hand and calculating hand value
	std::pair<std::string, std::string> firstCard = cards.back();
	cards.pop_back();
	player.AddCardToHand(firstCard);
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (player.dealer) 
	{
		SetConsoleTextAttribute(hConsole, 12);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 2);
	}

	std::cout << player.name << " hand value is " << std::to_string(player.handValue) << std::endl;

	SetConsoleTextAttribute(hConsole, 7); 
}

