#include "player.h"

#pragma once
class Deck
{
public:
    Deck();
    void ResetDeck();
    void DealCard(Player& player, int delay);
    int DeckCount();
private:
    std::vector<std::pair<std::string, std::string>> cards;
};
