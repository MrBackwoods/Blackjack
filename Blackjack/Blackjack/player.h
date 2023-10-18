#pragma once
class Player
{
public:
	std::string name;
	int handValue = 0;
	bool stays = false;
	int totalScore = 0;
	bool dealer = false;
	void ClearHandAndStatus();
	void AddCardToHand(std::pair<std::string, std::string> card);
	int HandCount();
private:
	std::vector<std::pair<std::string, std::string>> hand;
};

