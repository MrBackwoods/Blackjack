#include "pch.h"
#include "game.h"
#include <iostream>
#include <Windows.h>

// Constants for game parameters
const int shuffleThreshold = 20;
const int delayMilliseconds = 1000;

// Function for generating players
std::list<Player> Game::PreparePlayers()
{
	std::list<Player> allPlayers;

	Player dealer;
	dealer.name = "Dealer";
	dealer.dealer = true;
	allPlayers.push_front(dealer);

	Player gamer;
	gamer.name = "Player";
	allPlayers.push_front(gamer);

	return allPlayers;
}

// Function to checking for blackjack or if hand is over limit
bool Game::CheckLimits(Player& activePlayer, Player& otherPlayer)
{
	if (activePlayer.handValue > 21)
	{
		std::cout << activePlayer.name << " is over and loses!!!" << std::endl;
		otherPlayer.totalScore += 1;
		return true;
	}

	if (activePlayer.handValue == 21 && activePlayer.HandCount() == 2)
	{
		std::cout << "Blackjack! " << activePlayer.name << " wins!!!" << std::endl;
		activePlayer.totalScore += 1;
		return true;
	}

	return false;
}

// Function for resolving winner of the round
void Game::ResolveWinner(Player& dealer, Player& player)
{
	if (dealer.handValue > player.handValue)
	{
		std::cout << dealer.name << " wins!!!" << std::endl;
		dealer.totalScore += 1;
	}

	else if (dealer.handValue < player.handValue)
	{
		std::cout << player.name << " wins!!!" << std::endl;
		player.totalScore += 1;
	}

	else
	{
		std::cout << "It's a tie!" << std::endl;
	}
}

// A round of blackjack
void Game::PlayARound(std::list<Player>& players, Deck& deck)
{
	// Bool to checking if game is over
	bool gameOver = false;

	// Getting dealer and player references
	Player& player = *std::find_if(players.begin(), players.end(), [](const Player& player) { return !player.dealer; });
	Player& dealer = *std::find_if(players.begin(), players.end(), [](const Player& player) { return player.dealer; });

	// Dealing firt cards, player can instantly win with a blackjack
	deck.DealCard(player, delayMilliseconds);
	deck.DealCard(dealer, delayMilliseconds);
	deck.DealCard(player, delayMilliseconds);
	gameOver = CheckLimits(player, dealer);

	// Main gameplay loop after initial cards
	while (!gameOver)
	{
		// Player turn first
		while (!player.stays && !gameOver && player.handValue != 21)
		{
			std::cout << "Hit (H) or Stay (anything else)" << std::endl;
			char input;
			std::cin >> input;

			// Getting a new card
			if (std::toupper(input) == 'H')
			{
				std::cout << player.name << " hits" << std::endl;
				deck.DealCard(player, delayMilliseconds);
				gameOver = CheckLimits(player, dealer);
			}

			// Staying
			else
			{
				std::cout << player.name << " stays" << std::endl;
				player.stays = true;
			}
		}

		// Dealer turn 
		while (!dealer.stays && !gameOver)
		{
			// Staying
			if (dealer.handValue >= 17 && (player.stays && dealer.handValue >= player.handValue))
			{
				std::cout << dealer.name << " stays" << std::endl;
				dealer.stays = true;
				ResolveWinner(dealer, player);
				gameOver = true;
			}

			// Getting a new card
			else
			{
				std::cout << dealer.name << " hits" << std::endl;
				deck.DealCard(dealer, delayMilliseconds);
				gameOver = CheckLimits(dealer, player);
			}
		}
	}

	std::cout << std::endl;

	// Print score and clear hands
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 3);

	for (auto& p : players)
	{
		std::cout << ">>> " << p.name << " score " << p.totalScore << std::endl;
		p.ClearHandAndStatus();
	}

	SetConsoleTextAttribute(hConsole, 7);
	std::cout << std::endl;
}

// Running the game
void Game::Run()
{
	//Creating players
	std::list<Player> players = PreparePlayers();

	//Creating deck
	Deck deck;

	// Main gameplay loop
	while (true)
	{
		// Reset deck if needed
		if (deck.DeckCount() <= shuffleThreshold)
		{
			deck.ResetDeck();
		}

		// Play a round of blackjack
		PlayARound(players, deck);
	}
}