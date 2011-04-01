#ifndef _PLAYER
#define _PLAYER

#include "card.h"


class Player{

	public:
	int idPlayer;
	int money;
    Card Hand[2];

	Player();
	//void draw();

};


#endif
