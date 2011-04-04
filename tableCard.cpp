
#include "tableCard.h"

#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;
TableCard::TableCard()
{
    covered=true;
}

TableCard::~TableCard()
{
}

TableCard::TableCard(int id)
{
    idCard=id;
    covered=true;
}

TableCard::TableCard(const TableCard&)
{
    
}

void TableCard::draw()
{
    ofPushMatrix();
    ofTranslate(-0.0247487373+0.5-0.120208153,-0.0247487373+0.5-0.120208153,0);
    //ofTranslate(0,0.049,0);
    ofRotateZ(45);
    ofTranslate(0,-0.049,0);
    //ofTranslate((area.x+area.height/2),(area.y+area.width/2),0);
    //ofTranslate(-(area.x+area.height/2),-(area.y+area.width/2),0);
    texture.draw(area.x,area.y,area.height,area.width);
    ofPopMatrix();
}


