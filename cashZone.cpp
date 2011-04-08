#include "cashZone.h"

CashZone::CashZone()
{

    verdana.loadFont("frabk.ttf",100);
    //std::cout<<"FONT CREADA!"<<std::endl

    radi=0.0395;
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
    ofSetColor(255,215,0);
    ofCircle(x,y,radi);
	ofPopMatrix();
    ofEnableAlphaBlending();
    ofSetColor(255,255,255);
    chipTexture.draw(x-0.04,y-0.04,0.08,0.08);
    ofDisableAlphaBlending();

    ofPushMatrix();
    ofTranslate(0.5,0.5,0);
    ofScale(0.0001f,0.0001f,1);
    verdana.drawString("hello, this is franklin book calling\nanyone home?", 0.5,0.5);
    ofPopMatrix();
    /*std::cout<<"FONT PINTADA!"<<std::endl;*/
}

void CashZone::update()
{
    radi+=increment;

    if(radi>0.05)
    {
        increment=-increment;
    }
    else if(radi<0.0395)
    {
        increment=-increment;
    }


}
