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



class Player : public OnTable < CanMyDoubleTap < CanSendCards < CanDirectObjects < Graphic > > > >{

	public:
	int idPlayer;
	int money;
    int bet;
    float sum;
    bool active;
    bool playing;
    Card Hand[2];
    ofRectangle reactZone;
    CashZone zone;


    
    void Play();
	Player();
    
    virtual void MyDoubleTap(float a, float b)
    {
        if(a>reactZone.x&&a<reactZone.x+reactZone.width&&b>reactZone.y&&b<reactZone.y+reactZone.height)
        {
            std::cout <<"DoubleTap! " << a << " " << b << std::endl;
            active=false;
            
            zone.radi=0.039;
            zone.increment=0;
            
        }
    }
    
    virtual void SendCards(float a, float b)
    {
        std::cout <<"SendCards! " << a << " " << b << std::endl;
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
