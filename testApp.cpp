#include "testApp.h"
#include "game.h"
#include "cashZone.h"

#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "Calibrator.hpp"
#include "InputGestureTap.hpp"
#include "InputGestureBasicObjects.hpp"
#include "InputGestureBasicFingers.hpp"
#include "InputGestureMyDoubleTap.hpp"
#include "InputGestureMyTap.hpp"

#include <list>

using namespace tuio;


class TestMyTap : public OnTable < CanMyTap < Graphic > >
{
    //Interface redefined
    virtual void MyTap(float a, float b){std::cout <<"Tap! " << a << " " << b << std::endl;}
};




class Ball : public OnTable < CanDirectObjects < CanBasicFingers < CanTap < Graphic > > > >
{
    std::list< DirectObject * > objectes;
    std::list< DirectObject * > Barrera;
    public:
    float x,y,vx,vy;
    Ball()
    {
            x=0.2;
            y=0.5;
            vx=0.01;
            vy=0.01;



    }
    Ball(float xx, float yy){
            x = xx;
            y = yy;
            vx = 0.01;
            vy = 0.01;
    }
    void draw(){

            ofCircle(x,y,0.01);
            ofImage();            //for per seguir la llista d'objectes
            for (std::list<DirectObject * >::iterator it = objectes.begin(); it != objectes.end(); ++it)
                {
                        DirectObject * obj = *it;
                        ofCircle(obj->getX(), obj->getY(),0.025);
                }
            //for llista barrera
            for (std::list<DirectObject * >::iterator it = Barrera.begin(); it != Barrera.end(); ++it)
                {
                        DirectObject * obj = *it;
                        ofSetColor(10,100,10);
                        ofCircle(obj->getX(), obj->getY(),0.01);
                }



    }
    void update(){
            x+=vx;
            y+=vy;

      if( x<0 or x>1)
            vx = -vx;
      if( y<0 or y>1)
            vy = -vy;
    if((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5)>0.24)
    {
        vy = -vy;
        vx = -vx;
    }

     //for per seguir la llista d'objectes
            for (std::list<DirectObject * >::iterator it = objectes.begin(); it != objectes.end(); ++it)
                {
                        DirectObject * obj = *it;
                        float distAobjecte = obj->getDistance(x,y);
                        if(distAobjecte < 0.05)
                        {
                            //XOQUEM
                            float m = sqrt (vx*vx+vy*vy);
                            float vangle = DirectPoint(0,0).getAngle(DirectPoint(vx,vy));
                            float angleAObjecte = DirectPoint(x,y).getAngle(obj);
                            float nouangle = 2*angleAObjecte + M_PI -vangle;
                            vx = cos(nouangle) * m;
                            vy = sin(nouangle) * m;
                        }
                }
                for (std::list<DirectObject * >::iterator it = Barrera.begin(); it != Barrera.end(); ++it)
                {
                        DirectObject * obj = *it;
                        float distAobjecte = obj->getDistance(x,y);
                        if(distAobjecte < 0.05)
                        {
                            //XOQUEM
                            float m = sqrt (vx*vx+vy*vy);
                            float vangle = DirectPoint(0,0).getAngle(DirectPoint(vx,vy));
                            float angleAObjecte = DirectPoint(x,y).getAngle(obj);
                            float nouangle = 2*angleAObjecte + M_PI -vangle;
                            vx = cos(nouangle) * m;
                            vy = sin(nouangle) * m;
                        }
                }



    }

   /*  virtual void Tap(float _x, float _y){
         x=_x;
         y=_y;
     }*/


    void setPosition(float xx, float yy){
            x = xx;
            y = yy;
    }

//interface redefined by ofApp


    //Area-aware interface optionally redefined by ofApp
    //Aixo serveix per saber si esta a dintre de la taula o no i fer-ho servir
   // virtual void enterObject(DirectObject * object)         {newObject(object);}
   // virtual void exitObject(DirectObject * object)          {removeObject(object);}

//CanBasicFinguers

    //Interface redefined by ofApp
    virtual void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
        DirectObject* e1 = new DirectObject();
        e1->setX(xpos);
        e1->setY(ypos);
        Barrera.push_back(e1);

        }
    virtual void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel){
        DirectObject* e1 = new DirectObject();
        e1->setX(xpos);
        e1->setY(ypos);
        Barrera.push_back(e1);
        }

        virtual void newObject(DirectObject * object){objectes.push_back(object);}
    virtual void removeObject(DirectObject * object){objectes.remove(object);}
    //virtual void removeTuioCursor(int32 id){}
};

class fons: public Graphic{

    public:
    fons():Graphic(110){}
  void draw(){

        //ofSetColor(10,100,10);
      ofImage board;
      board.loadImage("images/board.jpg");
      board.draw(0,0,1,1);
        //ofCircle(0.5,0.5,0.5);
  }



};

//--------------------------------------------------------------
void testApp::Setup(){
    //new CursorFeedback();
    //new FigureFeedback();
    //new TapFeedback();
    //new Ball();

    //new Ball(0.2,0.2);
    new fons();
    //new TestMyDoubleTap();

    new Game();
    //new TestMyTap();
}

//--------------------------------------------------------------
void testApp::Update(){


}

//--------------------------------------------------------------
void testApp::Draw(){


}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}


