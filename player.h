#ifndef _PLAYER
#define _PLAYER

#include "card.h"
#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureMyDoubleTap.hpp"
#include "InputGestureMyTap.hpp"



class Player : public OnTable < CanMyDoubleTap < Graphic > >{

	public:
	int idPlayer;
	int money;
    bool active;
    bool playing;
    Card Hand[2];
    ofRectangle reactZone;
    
    void Play();
	Player();
    
    virtual void MyDoubleTap(float a, float b)
    {
        if(a>reactZone.x&&a<reactZone.x+reactZone.width&&b>reactZone.y&&b<reactZone.y+reactZone.height)
            std::cout <<"DoubleTap! " << a << " " << b << std::endl;
    }
    

};


#endif
