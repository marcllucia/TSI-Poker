#include "cashZone.h"

CashZone::CashZone()
{

    //verdana.loadFont("frabk.ttf",30);
    //std::cout<<"FONT CREADA!"<<std::endl
    
    radi=0.04;
    increment=0;
    sum=0;
    
}

void CashZone::setPoint(float xx, float yy)
{
    x=xx;
    y=yy;
}

void CashZone::draw()
{
    ofPushMatrix();
    ofSetColor(51,153,204);
    ofCircle(x,y,radi);
	ofPopMatrix();

    /*
    ofTranslate(0.5,0.5,0);
    verdana.drawString("hello, this is franklin book calling\nanyone home?", 0.5,0.5);
    std::cout<<"FONT PINTADA!"<<std::endl;*/
}

void CashZone::update()
{
    radi+=increment;

    if(radi>0.05)
    {
        increment=-increment;
    }
    else if(radi<0.04)
    {
        increment=-increment;
    }
    
    
}