#include "card.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;
Card::Card()
{
    covered=true;
}

Card::~Card()
{
}

Card::Card(int id)
{
    idCard=id;
    covered=true;
}

Card::Card(const Card&)
{
    
}

void Card::draw()
{

    if(!objects.empty())
    {
        if(area.width>area.height)
        {
            ofEnableAlphaBlending();
            ofPushMatrix();
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
            texture.draw(area.x,area.y,area.width,area.height);
            ofDisableAlphaBlending();
        }    
    }
    else
    {
        ofImage back;
        back.loadImage("images/back.png");
        
        if(area.width>area.height)
        {
            ofEnableAlphaBlending();
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
            back.draw(area.x,area.y,area.width,area.height);
            ofDisableAlphaBlending();
        }    
        
    }

}


