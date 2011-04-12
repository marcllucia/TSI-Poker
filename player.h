#ifndef _PLAYER
#define _PLAYER

#include "ofMain.h"
#include "card.h"
#include "cashZone.h"
#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureMyDoubleTap.hpp"
#include "InputGestureSendCards.hpp"
#include "InputGestureAposta.hpp"


class Player : public OnTable < CanAposta < CanMyDoubleTap < CanSendCards < CanDirectObjects < Graphic > > > > >{

	public:
    float xPos, yPos;
	int idPlayer;
	int money;
    int bet;
    int lastBet;
    int tableBet;
    float sum;
    float increment;
    float angle;
    bool active;
    bool playing;
    bool confirmed;
    bool canCheck;
    ofSoundPlayer chips;
    Card Hand[2];
    ofRectangle reactZone;
    ofTrueTypeFont	moneyText;
    CashZone zone;



    void Play();
	Player();
    void draw();
    void update();
    
    virtual void Aposta(float x, float y,float v){
    
        if(active)
        {
            float distance=sqrt(pow((x-zone.x),2)+pow((y-zone.y),2));
            if(distance<0.05)
            {
                std::cout <<"Aposta! " << x << " " << y << std::endl;

                chips.play();
                money-=bet;
                active=false;
                confirmed=true;
            }

        }

    }

    virtual void MyDoubleTap(float a, float b)
    {
        if(active&&canCheck)
        {
            if(a>reactZone.x&&a<reactZone.x+reactZone.width&&b>reactZone.y&&b<reactZone.y+reactZone.height)
            {
                std::cout <<"DoubleTap! " << a << " " << b << std::endl;
                active=false;
            }
        }
    }

    virtual void SendCards(float v1, float v2,float x1, float y1, float x2, float y2)
    {
        if(active)
        {
            if(x1>Hand[0].area.x&&x1<Hand[0].area.x+Hand[0].area.width&&y1>Hand[0].area.y&&y1<Hand[0].area.y+Hand[0].area.height)
            {
                if(x2>Hand[1].area.x&&x2<Hand[1].area.x+Hand[1].area.width&&y2>Hand[1].area.y&&y2<Hand[1].area.y+Hand[1].area.height)
                {
                    increment=0.008;
                    active=false;
                    playing=false;
                }
            }
            else if(x1>Hand[1].area.x&&x1<Hand[1].area.x+Hand[1].area.width&&y1>Hand[1].area.y&&y1<Hand[1].area.y+Hand[1].area.height)
            {
                if(x2>Hand[0].area.x&&x2<Hand[0].area.x+Hand[0].area.width&&y2>Hand[0].area.y&&y2<Hand[0].area.y+Hand[0].area.height)
                {
                    increment=0.008;
                    active=false;
                    playing=false;
                }

            }
        }
    }

};


#endif
