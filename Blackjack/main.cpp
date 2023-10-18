#include "pch.h"
#include "game.h"
#include <iostream>

// Running the game
int main() 
{
    std::cout << "Welcome to Blackjack!" << std::endl << std::endl;

    try 
    {
        Game game;
        game.Run();
    }

    catch (const std::exception& e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

