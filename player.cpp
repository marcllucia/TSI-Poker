#include "player.h"
#include "card.h"

Player::Player()
{
    bet=0;
    increment=0;
    playing=true;
    active=false;
    lastBet=0;
    confirmed=false;
    allIn=false;
    moneyText.loadFont("Courier.dfont",100);
    moneyTable.loadFont("frabk.ttf",100);

    chips.loadSound("sounds/chips.mp3");
    fold.loadSound("sounds/fold.mp3");


}

void Player::turnOn(int bet)
{
    tableBet=bet;
    active=true;
    zone.increment=0.0002;
}

void Player::turnOff()
{
    active=false;
    zone.increment=0;
    zone.radi=0.039;
}

void Player::draw()
{
    
    char moneyValue[255]="Money: ";
    char moneyString[255];
    char tempString[255];
    char temp[255];
    if(playing)
    {
        sprintf(tempString,"%i", (int)bet);
    }
    else
    {
        sprintf(tempString,"%i", 0);
    }

    sprintf(moneyString,"%i", (int)money);
    
    
    strcat(moneyValue, moneyString);
	sprintf(temp,"%i", (int)bet);
    if(strlen(temp)==1)
    {
        sprintf(tempString,"%i", 0);
        strcat(tempString, temp);
        sprintf(temp,"%i", 0);
        strcat(temp, tempString);
        sprintf(tempString,"%i", 0);
        strcat(tempString, temp);
        
    }else if(strlen(temp)==2)
    {
        sprintf(tempString,"%i", 0);
        strcat(tempString, temp);
        sprintf(temp,"%i", 0);
        strcat(temp, tempString);
        strcpy(tempString,temp);
    }
    else if(strlen(temp)==3)
    {
        sprintf(tempString,"%i", 0);
        strcat(tempString, temp);
    }
    ofRectangle rect = moneyText.getStringBoundingBox(tempString, 0,30);
    ofRectangle rect2 = moneyText.getStringBoundingBox(tempString, 0,-30);


    ofPushMatrix();
    ofTranslate(zone.x+xPos,zone.y+yPos,0);
    ofRotateZ(angle);

    ofScale(0.0003f,0.0003f,1);
    ofSetColor(255,215,0);
    ofLine(rect.x,rect.y+rect.height,rect.x+rect.width,rect.y+rect.height) ;  
    ofLine(rect2.x,rect2.y,rect2.x+rect2.width,rect2.y) ;  
    ofSetColor(255,255,255);
    moneyText.drawString(tempString, 0,0);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(zone.x+moneyX,zone.y+moneyY,0);
    ofRotateZ(angle);
    ofScale(0.00026f,0.00026f,1);
    moneyTable.drawString(moneyValue, 0,0);
    ofPopMatrix();

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
    
          bet=zone.sum*10;
        //bet=bet*5;
        
        if(bet>money)
        {
            bet=money;
            zone.sum=sum;
        }
        else if(bet<tableBet-lastBet)
        {
            bet=tableBet-lastBet;
            zone.sum=(tableBet-lastBet)/10;
        }
        else
        {
            sum=zone.sum;
        }

}