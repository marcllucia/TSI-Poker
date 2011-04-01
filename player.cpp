#include "player.h"
#include "card.h"

Player::Player()
{

}

/*void Player::draw()
{
    Card c1=Hand[0];
    if(!c1.covered)
    {
        if(c1.area.width>c1.area.height)
        {
            ofPushMatrix();
            ofTranslate((c1.area.x+c1.area.width/2),(c1.area.y+c1.area.height/2),0);
            ofRotateZ(-90);
            ofTranslate(-(c1.area.x+c1.area.height/2),-(c1.area.y+c1.area.width/2),0);
            c1.texture.draw(c1.area.x,c1.area.y,c1.area.height,c1.area.width);
            ofPopMatrix();
        }
        else
        {
            c1.texture.draw(c1.area.x,c1.area.y,c1.area.width,c1.area.height);
        }
    }
    else
    {
        ofImage texture;
        texture.loadImage("back.jpg");
        texture.draw(c1.area.x,c1.area.y,c1.area.width,c1.area.height);
    }


    Card c2=Hand[1];
    if(!c2.covered)
    {
         if(c2.area.width>c2.area.height)
        {
            ofPushMatrix();
            ofTranslate((c2.area.x+c2.area.width/2),(c2.area.y+c2.area.height/2),0);
            ofRotateZ(-90);
            ofTranslate(-(c2.area.x+c2.area.height/2),-(c2.area.y+c2.area.width/2),0);
            c2.texture.draw(c2.area.x,c2.area.y,c2.area.height,c2.area.width);
            ofPopMatrix();
        }
        else
        {
            c2.texture.draw(c2.area.x,c2.area.y,c2.area.width,c2.area.height);
        }
    }
    else
    {
        ofImage texture;
        texture.loadImage("back.jpg");
        texture.draw(c2.area.x,c2.area.y,c2.area.width,c2.area.height);
    }

}*/
