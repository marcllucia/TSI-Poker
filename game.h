#ifndef _GAME
#define _GAME

#include "card.h"
#include "player.h"
#include <vector>

using namespace std;
using namespace tuio;

class Game
{
	public:

	vector <int> Deck;
    std::string textureData[52];
	Player Players[4];
	int numPlayers;
	int dealer;
    std::map<int, tuio::DirectObject*> objects;


    Game();

    void DealCards();
    void InitializePlayerCards();
    int GetRandomCard();
};




#endif
