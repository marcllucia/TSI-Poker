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
#include "tableCard.h"
#include "player.h"
#include <vector>

using namespace std;
using namespace tuio;

class Game : public OnTable < CanMyTap < CanDirectObjects < Graphic > > >
{
	public:

	vector <int> Deck;
    std::string textureData[52];
    TableCard Cards[5];
	Player Players[4];
    ofSoundPlayer knock;
	int numPlayers;
	int smallBlind;
    int money;
    int bet;
    int lastBet;
    int turn;
    int firstPlayer;
    int start;
    bool updateGame;
    bool flop;
    bool river;
    std::map<int, tuio::DirectObject*> objects;


    Game();

    void DealCards();
    void InitializePlayers();
    int GetRandomCard();
    void StartGame();
    
    virtual void MyTap(float x, float y)
    {
        knock.play();
    }


    virtual void newObject(tuio::DirectObject * object)
    {
        objects[object->f_id]=object;
    }
    virtual void removeObject(tuio::DirectObject * object)
    {
        objects.erase(object->f_id);
    }
    virtual void updateObject(tuio::DirectObject * object)
    {
        objects[object->f_id]=object;
    }

    void draw();
    void update();
};




#endif
