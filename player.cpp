#include "player.h"
#include "card.h"

Player::Player()
{

}

void Player::update()
{
    if(Hand[0].area.x<0.5&&Hand[0].area.y<0.51&&Hand[1].area.x>0.5&&Hand[1].area.y<0.51)
    {
        Hand[0].area.y+=increment;
        Hand[1].area.y+=increment;
        if(Hand[0].area.y>0.3-0.098)
        {
            increment=0;
        }
    }
    else if(Hand[0].area.x<0.51&&Hand[0].area.y<0.5&&Hand[1].area.x<0.51&&Hand[1].area.y>0.5)
    {
        Hand[0].area.x+=increment;
        Hand[1].area.x+=increment;
        if(Hand[0].area.x>0.3-0.098)
        {
            increment=0;
        }

    }
    else if(Hand[0].area.x>0.49&&Hand[0].area.y<0.5)
    {
        Hand[0].area.x-=increment;
        Hand[1].area.x-=increment;
        if(Hand[0].area.x<0.7)
        {
            increment=0;
        }
    }
    else if(Hand[0].area.x<0.5&&Hand[0].area.y>0.49)
    {
        Hand[0].area.y-=increment;
        Hand[1].area.y-=increment;
        if(Hand[0].area.y<0.7)
        {
            increment=0;
        }
    }

}