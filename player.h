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


class Player : public OnTable < CanMyDoubleTap < CanSendCards < CanDirectObjects < Graphic > > > >{

	public:
	int idPlayer;
	int money;
    int bet;
    float sum;
    float increment;
    bool active;
    bool playing;
    Card Hand[2];
    ofRectangle reactZone;
    CashZone zone;



    void Play();
	Player();

    void update();

    virtual void MyDoubleTap(float a, float b)
    {
        if(active)
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
                    increment=0.02;
                    active=false;
                    playing=false;
                }
            }
            else if(x1>Hand[1].area.x&&x1<Hand[1].area.x+Hand[1].area.width&&y1>Hand[1].area.y&&y1<Hand[1].area.y+Hand[1].area.height)
            {
                if(x2>Hand[0].area.x&&x2<Hand[0].area.x+Hand[0].area.width&&y2>Hand[0].area.y&&y2<Hand[0].area.y+Hand[0].area.height)
                {
                    increment=0.02;
                    active=false;
                    playing=false;
                }

            }
        }
    }

    virtual void newObject(tuio::DirectObject * object)
    {
        bet=zone.sum*10;
        bet=bet*5;
    }
    virtual void removeObject(tuio::DirectObject * object)
    {
    }

    virtual void updateObject(tuio::DirectObject * object)
    {

        bet=zone.sum*10;
        bet=bet*5;

        if(bet>money)
        {
            bet=money;
            zone.sum=sum;
        }
        else if(bet<0)
        {
            bet=0;
            zone.sum=sum;
        }
        else
        {
            sum=zone.sum;
        }

        std::cout<<"APOSTA: "<<bet<<std::endl;


    }



};


#endif
