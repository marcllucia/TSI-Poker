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
#include <cmath>

using namespace tuio;

class CashZone  : public OnTable < CanDirectObjects <  Graphic > >
{
    public:
    int G;
    float x,y,radi,increment,angle,sum;
    ofImage chipTexture;
    ofTrueTypeFont	moneyText;
    std::map<int, tuio::DirectObject*> objects;
    
    CashZone();
    
    void setPoint(float xx, float yy);
    void draw();
    void update();

    virtual void newObject(tuio::DirectObject * object)
    {
        float distance=sqrt(pow((object->getX()-x),2)+pow((object->getY()-y),2));
        
        if(distance<0.1)
        {
            G=0;
            angle=object->angle;
        }
    }
    
    virtual void removeObject(tuio::DirectObject * object)
    {
        sum=0;
        G=215;
    }
    
    virtual void updateObject(tuio::DirectObject * object)
    {
        float distance=sqrt(pow((object->getX()-x),2)+pow((object->getY()-y),2));
        
        if(distance<0.05)
        {
            if(object->angle-angle>-2&&object->angle-angle<2)
            {
                sum+=(object->angle-angle);
            }
           
            angle=object->angle;
        }
    }


};




#endif
