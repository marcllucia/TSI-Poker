#ifndef _CARD
#define _CARD

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureMyDoubleTap.hpp"
#include "InputGestureMyTap.hpp"
#include "InputGestureSendCards.hpp"
#include "InputGestureTwoFingers.hpp"



#include <vector>
#include <cmath>

using namespace std;
using namespace tuio;


class Card : public OnTable < CanTwoFingers < CanDirectFingers < CanDirectObjects < Graphic > > > >
{
	public:
	int idCard;
    float angle,fingerX, fingerY, tolerance;
    float alpha;
	ofRectangle area;
    ofRectangle reactZone;
	ofImage texture;
	ofImage back;
	bool covered;
    bool first;
    bool firstFinger;
    bool updateAlpha;
    std::map<int, tuio::DirectObject*> objects;

    Card();
	Card(int id);
    Card(const Card&);

    ~Card();
    
    virtual void MoveCards(float x, float y)
    {
        std::cout<<"TWOFINGERS! x: "<<x<<" y:"<<y<<std::endl;
        if(x>area.x&&x<area.x+area.width&&y>area.y&&y<area.y+area.height)
        {

            if(firstFinger)
            {
                fingerX=x;
                fingerY=y;
                firstFinger=false;
            }
            area.x+=x-fingerX;
            area.y+=y-fingerY;
            reactZone.x+=x-fingerX;
            reactZone.y+=y-fingerY;
            fingerX=x;
            fingerY=y;
        }
    }
       
    /*virtual void newCursor(DirectFinger * f)
    {
        if(f->getX()>area.x&&f->getX()<area.x+area.width&&f->getY()>area.y&&f->getY()<area.y+area.height)
        {
            fingerX=f->getX();
            fingerY=f->getY();
            
        }
    }
    virtual void updateCursor(DirectFinger *f)
    {
        if(f->getX()>area.x&&f->getX()<area.x+area.width&&f->getY()>area.y&&f->getY()<area.y+area.height)
        {
            area.x+=f->getX()-fingerX;
            area.y+=f->getY()-fingerY;
            reactZone.x+=f->getX()-fingerX;
            reactZone.y+=f->getY()-fingerY;
            fingerX=f->getX();
            fingerY=f->getY();
        }
    }*/


    virtual void newObject(tuio::DirectObject * object)
    {

        if(object->getX()>reactZone.x&&object->getX()<reactZone.x+reactZone.width&&object->getY()>reactZone.y&&object->getY()<reactZone.y+reactZone.height&&(object->angle>=tolerance-0.01&&object->angle<tolerance+M_PI/6))
        {
            objects[object->f_id]=object;
        }
    }

    virtual void removeObject(tuio::DirectObject * object)
    {
        objects.erase(object->f_id);
    }

    virtual void updateObject(tuio::DirectObject * object)
    {
        if(object->getX()>reactZone.x&&object->getX()<reactZone.x+reactZone.width&&object->getY()>reactZone.y&&object->getY()<reactZone.y+reactZone.height&&(object->angle>=tolerance-0.01&&object->angle<tolerance+M_PI/6))
        {
            objects[object->f_id]=object;
        }
        else
        {
            objects.erase(object->f_id);
        }
    }



    void draw();
    void update();

};

#endif

