#ifndef _GAME
#define _GAME

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureMyDoubleTap.hpp"
#include "InputGestureMyTap.hpp"

#include "card.h"
#include "player.h"
#include <vector>

using namespace std;
using namespace tuio;

class Game : public OnTable < CanDirectObjects < Graphic > >
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
