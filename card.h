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

#include <vector>

using namespace std;
using namespace tuio;


class Card : public OnTable < CanDirectObjects < Graphic > >
{
	public:
	int idCard;
	ofRectangle area;
	ofImage texture;
	bool covered;
    std::map<int, tuio::DirectObject*> objects;

    Card();
	Card(int id);
    Card(const Card&);

    ~Card();
    
    virtual void newObject(tuio::DirectObject * object)
    {

        if(object->getX()>area.x&&object->getX()<area.x+area.width/4&&object->getY()>area.y&&object->getY()<area.y+area.height)
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
        if(object->getX()>area.x&&object->getX()<area.x+area.width/4&&object->getY()>area.y&&object->getY()<area.y+area.height)
        {
            objects[object->f_id]=object;
        }
        else
        {
            objects.erase(object->f_id);
        }
    }
    

    
    void draw();

};

#endif

