#include "cashZone.h"

CashZone::CashZone()
{
    radi=0.0395;
    increment=0;
    sum=0;
    G=215;

}

void CashZone::setPoint(float xx, float yy)
{
    x=xx;
    y=yy;
}

void CashZone::draw()
{
    ofPushMatrix();
    ofSetColor(255,G,0);
    ofCircle(x,y,radi);
	ofPopMatrix();
    ofEnableAlphaBlending();
    ofSetColor(255,255,255);
    chipTexture.draw(x-0.04,y-0.04,0.08,0.08);
    ofDisableAlphaBlending();

    ofPushMatrix();
    ofTranslate(0.5,0.5,0);
    ofScale(0.0003f,0.0003f,1);
    ofPopMatrix();
}

void CashZone::update()
{
    radi+=increment;

    if(radi>0.05)
    {
        increment=-increment;
    }
    else if(radi<0.0385)
    {
        increment=-increment;
    }


}
