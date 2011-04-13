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


class fons: public Graphic{

    public:
    fons():Graphic(110){board.loadImage("images/board.jpg");}
    ofImage board;
  void draw(){

        //ofSetColor(10,100,10);

      ofSetColor(255,255,255);
      board.draw(0,0,1,1);
        //ofCircle(0.5,0.5,0.5);
  }



};

//--------------------------------------------------------------
void testApp::Setup(){
    new CursorFeedback();
    //new FigureFeedback();
    //new TapFeedback();
    //new Ball();

    //new Ball(0.2,0.2);
    new fons();
    //new TestMyDoubleTap();

    new Game(1000,1000,1000,1000);
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


