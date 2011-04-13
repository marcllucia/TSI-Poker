#include "card.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;
Card::Card()
{
    covered=true;
    back.loadImage("images/back.png");
    firstFinger=true;
    updateAlpha=false;

    alpha=255;
}

Card::~Card()
{
}

Card::Card(int id)
{
    idCard=id;
    covered=true;
    firstFinger=true;
    updateAlpha=false;

}

Card::Card(const Card&)
{
    firstFinger=true;
}

void Card::update()
{
    if(updateAlpha)
    {
        alpha-=2;
    }
}

void Card::draw()
{

    if(!objects.empty()or !covered)
    {
        if(area.width>area.height)
        {
            ofEnableAlphaBlending();
            ofPushMatrix();
            ofSetColor(255,255,255,alpha);
            ofTranslate(area.x+area.width/2,area.y+area.height/2,0);
            ofRotateZ(-90);
            ofTranslate(-(area.x+area.height/2),-(area.y+area.width/2),0);
            texture.draw(area.x,area.y,area.height,area.width);
            ofPopMatrix();
            ofDisableAlphaBlending();
        }
        else
        {
            ofEnableAlphaBlending();
            ofSetColor(255,255,255,alpha);
            texture.draw(area.x,area.y,area.width,area.height);
            ofDisableAlphaBlending();
        }
    }
    else
    {



        if(area.width>area.height)
        {
            ofEnableAlphaBlending();
            ofSetColor(255,255,255,alpha);
            ofPushMatrix();
            ofTranslate(area.x+area.width/2,area.y+area.height/2,0);
            ofRotateZ(-90);
            ofTranslate(-(area.x+area.height/2),-(area.y+area.width/2),0);
            back.draw(area.x,area.y,area.height,area.width);
            ofPopMatrix();
            ofDisableAlphaBlending();
        }
        else
        {
            ofEnableAlphaBlending();
            ofSetColor(255,255,255,alpha);
            back.draw(area.x,area.y,area.width,area.height);
            ofDisableAlphaBlending();
        }

    }

}


