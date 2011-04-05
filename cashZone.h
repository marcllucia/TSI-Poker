#ifndef _CASHZONE
#define _CASHZONE

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureMyDoubleTap.hpp"
#include "InputGestureMyTap.hpp"

class CashZone  : public OnTable < Graphic >
{
    public:
    float x,y,radi,increment; 
    ofTrueTypeFont	verdana;
    
    CashZone();
    
    void setPoint(float xx, float yy);
    void draw();
    void update();
    //   void update();
};




#endif
