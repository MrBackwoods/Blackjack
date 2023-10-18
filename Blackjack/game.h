#include "player.h"
#include "deck.h"

#pragma once
class Game
{
public:
	void Run();
private:
	std::list<Player> PreparePlayers();
	bool CheckLimits(Player& activePlayer, Player& otherPlayer);
	void ResolveWinner(Player& dealer, Player& player);
	void PlayARound(std::list<Player>& players, Deck& deck);
};

