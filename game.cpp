#include "game.h"

#include <vector>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include<time.h>
#include<iostream>
using namespace std;

void Game::Restart(int m1, int m2, int m3, int m4)
{
    for(int i=0; i<4; i++)
    {
        if(Players[i].money==0)
        {
            Players[i].playing=false;
            Players[i].Hand[0].alpha=0;
            Players[i].Hand[1].alpha=0;
            Players[i].active=false;

        }
        else
        {
            Players[i].active=false;
            Players[i].playing=true;
            Players[i].Hand[0].alpha=255;
            Players[i].Hand[1].alpha=255;
        }
    }
    Players[0].money=m1;
    Players[1].money=m2;
    Players[2].money=m3;
    Players[3].money=m4;
    
    for(int i=0; i<52; i++)
    {
        Deck[i]=i;
    }
    DealCards();
    
    InitializePlayers();
    turn=smallBlind+1;
    if(turn==4)
    {
        turn=0;
    }
    while(!Players[turn].playing)
    {
        turn++;
        if(turn==numPlayers)
        {
            turn=0;
        }
    }

    smallBlind=turn;
    StartGame();
    
    updateGame=true;
    flop=false;
    preriver=false;
    river=false;
    talked=false;
    start=0;
    text.loadFont("frabk.ttf",100);

}


Game::Game(int m1, int m2, int m3, int m4)
{
    updateGame=false;
    numPlayers=4;
    srand((unsigned)time(0));
    
    Players[0].money=m1;
    Players[1].money=m2;
    Players[2].money=m3;
    Players[3].money=m4;

    //Inicialitzem les textures
    textureData[0]="images/cor-2.png";
    textureData[1]="images/cor-3.png";
    textureData[2]="images/cor-4.png";
    textureData[3]="images/cor-5.png";
    textureData[4]="images/cor-6.png";
    textureData[5]="images/cor-7.png";
    textureData[6]="images/cor-8.png";
    textureData[7]="images/cor-9.png";
    textureData[8]="images/cor-10.png";
    textureData[9]="images/cor-J.png";
    textureData[10]="images/cor-Q.png";
    textureData[11]="images/cor-K.png";
    textureData[12]="images/cor-A.png";
    textureData[13]="images/trebol-2.png";
    textureData[14]="images/trebol-3.png";
    textureData[15]="images/trebol-4.png";
    textureData[16]="images/trebol-5.png";
    textureData[17]="images/trebol-6.png";
    textureData[18]="images/trebol-7.png";
    textureData[19]="images/trebol-8.png";
    textureData[20]="images/trebol-9.png";
    textureData[21]="images/trebol-10.png";
    textureData[22]="images/trebol-J.png";
    textureData[23]="images/trebol-Q.png";
    textureData[24]="images/trebol-K.png";
    textureData[25]="images/trebol-A.png";
    textureData[26]="images/rombo-2.png";
    textureData[27]="images/rombo-3.png";
    textureData[28]="images/rombo-4.png";
    textureData[29]="images/rombo-5.png";
    textureData[30]="images/rombo-6.png";
    textureData[31]="images/rombo-7.png";
    textureData[32]="images/rombo-8.png";
    textureData[33]="images/rombo-9.png";
    textureData[34]="images/rombo-10.png";
    textureData[35]="images/rombo-J.png";
    textureData[36]="images/rombo-Q.png";
    textureData[37]="images/rombo-K.png";
    textureData[38]="images/rombo-A.png";
    textureData[39]="images/pica-2.png";
    textureData[40]="images/pica-3.png";
    textureData[41]="images/pica-4.png";
    textureData[42]="images/pica-5.png";
    textureData[43]="images/pica-6.png";
    textureData[44]="images/pica-7.png";
    textureData[45]="images/pica-8.png";
    textureData[46]="images/pica-9.png";
    textureData[47]="images/pica-10.png";
    textureData[48]="images/pica-J.png";
    textureData[49]="images/pica-Q.png";
    textureData[50]="images/pica-K.png";
    textureData[51]="images/pica-A.png";


    Deck.resize(52);
    for(int i=0; i<52; i++)
    {
         Deck[i]=i;
    }
    DealCards();

    InitializePlayers();
    turn=rand() % 4;
    smallBlind=turn;
    StartGame();
    knock.loadSound("sounds/knock.wav");
    
    updateGame=true;
    flop=false;
    preriver=false;
    river=false;
    talked=false;
    start=0;
    text.loadFont("frabk.ttf",100);

}

void Game::DealCards()
{
    for (int i=0;i<4;i++)
    {
        Players[i].lastBet=0;
        Players[i].Hand[0].updateAlpha=false;
        Players[i].Hand[1].updateAlpha=false;
        Players[i].increment=0;
        Players[i].Hand[0].covered=true;
        Players[i].Hand[1].covered=true;
        Players[i].Hand[0].idCard=GetRandomCard();
        Players[i].Hand[1].idCard=GetRandomCard();
        std::cout <<"Player " << i<<": "<< Players[i].Hand[0].idCard << " , "<<Players[i].Hand[1].idCard<<std::endl;
    }

    for (int i=0;i<5;i++)
    {
        Cards[i].covered=true;
        Cards[i].drawCard=false;
        Cards[i].idCard=GetRandomCard();
    }

}

void Game::InitializePlayers()
{
    Players[0].Hand[0].area.set(0.405,0.040,0.07,0.098);
    Players[0].Hand[0].texture.loadImage(textureData[Players[0].Hand[0].idCard]);
    Players[0].Hand[0].reactZone.set(Players[0].Hand[0].area.x,Players[0].Hand[0].area.y+Players[0].Hand[0].area.height/3*2,Players[0].Hand[0].area.width,Players[0].Hand[0].area.height/3);
    Players[0].Hand[0].tolerance=M_PI;

    Players[0].Hand[1].area.set(0.525,0.040,0.07,0.098);
    Players[0].Hand[1].texture.loadImage(textureData[Players[0].Hand[1].idCard]);
    Players[0].Hand[1].reactZone.set(Players[0].Hand[1].area.x,Players[0].Hand[1].area.y+Players[0].Hand[1].area.height/3*2,Players[0].Hand[1].area.width,Players[0].Hand[1].area.height/3);
    Players[0].Hand[1].tolerance=M_PI;


    Players[1].Hand[0].area.set(1-0.098-0.040,0.405,0.098,0.07);
    Players[1].Hand[0].texture.loadImage(textureData[Players[1].Hand[0].idCard]);
    Players[1].Hand[0].reactZone.set(Players[1].Hand[0].area.x,Players[1].Hand[0].area.y,Players[1].Hand[0].area.width/3,Players[1].Hand[0].area.height);
    Players[1].Hand[0].tolerance=3*M_PI/2;


    Players[1].Hand[1].area.set(1-0.098-0.040,0.525,0.098,0.07);
    Players[1].Hand[1].texture.loadImage(textureData[Players[1].Hand[1].idCard]);
    Players[1].Hand[1].reactZone.set(Players[1].Hand[1].area.x,Players[1].Hand[1].area.y,Players[1].Hand[1].area.width/3,Players[1].Hand[1].area.height);
    Players[1].Hand[1].tolerance=3*M_PI/2;


    Players[2].Hand[0].area.set(0.405,1-0.098-0.040,0.07,0.098);
    Players[2].Hand[0].texture.loadImage(textureData[Players[2].Hand[0].idCard]);
    Players[2].Hand[0].reactZone.set(Players[2].Hand[0].area.x,Players[2].Hand[0].area.y,Players[2].Hand[0].area.width,Players[2].Hand[0].area.height/3);
    Players[2].Hand[0].tolerance=0;


    Players[2].Hand[1].area.set(0.525,1-0.098-0.040,0.07,0.098);
    Players[2].Hand[1].texture.loadImage(textureData[Players[2].Hand[1].idCard]);
    Players[2].Hand[1].reactZone.set(Players[2].Hand[1].area.x,Players[2].Hand[1].area.y,Players[2].Hand[1].area.width,Players[2].Hand[1].area.height/3);
    Players[2].Hand[1].tolerance=0;


    Players[3].Hand[0].area.set(0.040,0.405,0.098,0.07);
    Players[3].Hand[0].texture.loadImage(textureData[Players[3].Hand[0].idCard]);
    Players[3].Hand[0].reactZone.set(Players[3].Hand[0].area.x+Players[3].Hand[0].area.width/4*3,Players[3].Hand[0].area.y,Players[3].Hand[0].area.width/4,Players[3].Hand[0].area.height);
    Players[3].Hand[0].tolerance=M_PI/2;


    Players[3].Hand[1].area.set(0.040,0.525,0.098,0.07);
    Players[3].Hand[1].texture.loadImage(textureData[Players[3].Hand[1].idCard]);
    Players[3].Hand[1].reactZone.set(Players[3].Hand[1].area.x+Players[3].Hand[1].area.width/4*3,Players[3].Hand[1].area.y,Players[3].Hand[1].area.width/4,Players[3].Hand[1].area.height);
    Players[3].Hand[1].tolerance=M_PI/2;



    Cards[0].texture.loadImage(textureData[Cards[0].idCard]);
    Cards[0].area.set(0,0,0.098,0.07);

    Cards[1].texture.loadImage(textureData[Cards[1].idCard]);
    Cards[1].area.set(0.085,0,0.098,0.07);

    Cards[2].texture.loadImage(textureData[Cards[2].idCard]);
    Cards[2].area.set(0.17,0,0.098,0.07);

    Cards[3].texture.loadImage(textureData[Cards[3].idCard]);
    Cards[3].area.set(0.255,0,0.098,0.07);

    Cards[4].texture.loadImage(textureData[Cards[4].idCard]);
    Cards[4].area.set(0.34,0,0.098,0.07);

    Players[0].reactZone.set(0.2,0,0.6,0.3);
    Players[1].reactZone.set(0.7,0.2,0.3,0.6);
    Players[2].reactZone.set(0.2,0.7,0.6,0.3);
    Players[3].reactZone.set(0,0.2,0.3,0.6);

    for (int i=0; i<4; i++)
    {
        //Players[i].playing=true;
    }
    
    Players[0].angle=180;
    Players[1].angle=270;
    Players[2].angle=0;
    Players[3].angle=90;
    
    Players[0].xPos=0.05;
    Players[0].yPos=0.06;
    Players[1].xPos=-0.06;
    Players[1].yPos=0.05;
    Players[2].xPos=-0.05;
    Players[2].yPos=-0.06;
    Players[3].xPos=0.06;
    Players[3].yPos=-0.05;

    Players[0].zone.setPoint(0.33,0.089);
    Players[0].zone.chipTexture.loadImage("images/pica-chip.png");
    Players[1].zone.setPoint(1-0.089,0.33);
    Players[1].zone.chipTexture.loadImage("images/cor-chip.png");
    Players[2].zone.setPoint(1-0.33,1-0.089);
    Players[2].zone.chipTexture.loadImage("images/trebol-chip.png");
    Players[3].zone.setPoint(0.089,1-0.33);
    Players[3].zone.chipTexture.loadImage("images/rombo-chip.png");
    
    Players[0].moneyX=0.25;
    Players[0].moneyY=0.13;

    Players[1].moneyX=-0.13;
    Players[1].moneyY=0.25;
    
    Players[2].moneyX=-0.25;
    Players[2].moneyY=-0.13;
    
    Players[3].moneyX=0.13;
    Players[3].moneyY=-0.25;
    
    angle=0;

}


void Game::draw()
{
    char pot[255]="Pot: ";
    char string[255];
    sprintf(string,"%i", (int)money);
    strcat(pot, string);

    ofRectangle rect = text.getStringBoundingBox(pot, 0,0);

    ofPushMatrix();
    ofTranslate(0.5,0.5,0);
    ofRotateZ(angle);
    ofTranslate(0,0.2,0);
    ofScale(0.00026f,0.00026f,1);
    ofTranslate(-rect.width/2,0,0);
    text.drawString(pot, 0,0);
    ofPopMatrix();

    /*for( map<int,tuio::DirectObject*>::iterator it=objects.begin(); it!=objects.end(); ++it)
    {
        DirectObject * obj = it->second;
        ofImage card;
        ofPushMatrix();
        ofSetColor(255,255,255);
        ofTranslate(obj->getX(),obj->getY(),0);
        ofRotateZ(obj->angle*180/3.1415);
        ofTranslate(-(obj->getX()),-(obj->getY()),0);
        card.draw(obj->getX()-(0.07/2),obj->getY()-(0.098/4),0.08,0.11);
        ofPopMatrix();
    }*/
}

void Game::update()
{  
    angle+=0.2;
    int numPlaying=0;
    int numAllIn=0;
    for(int i=0; i<4; i++)
    {
        if(Players[i].playing)
        {
            numPlaying++;
        }
        if(Players[i].allIn)
        {
            numAllIn++;
        }
    }
    if(numPlaying==numAllIn and numPlaying>0)
    {
        flop=false;
        preriver=false;
        river=false;
        preflop=false;
        for(int i=0; i<4; i++)
        {
            if(Players[i].playing)
            {
                Players[i].Hand[0].covered=false;
                Players[i].Hand[1].covered=false;
            }
            
        }
        for(int i=0; i<6; i++)
        {
            Cards[i].drawCard=true;
            Cards[i].covered=false;
        }
        
        if(Players[0].playing)
        {
            c0[0]=Players[0].Hand[0].idCard;
            c0[1]=Players[0].Hand[1].idCard;
            c0[2]=Cards[0].idCard;
            c0[3]=Cards[1].idCard;
            c0[4]=Cards[2].idCard;
            c0[5]=Cards[3].idCard;
            c0[6]=Cards[4].idCard;
        }
        else
        {
            c0[0]=-1;
        }
        
        if(Players[1].playing)
        {
            c1[0]=Players[1].Hand[0].idCard;
            c1[1]=Players[1].Hand[1].idCard;
            c1[2]=Cards[0].idCard;
            c1[3]=Cards[1].idCard;
            c1[4]=Cards[2].idCard;
            c1[5]=Cards[3].idCard;
            c1[6]=Cards[4].idCard;
        }
        else
        {
            c1[0]=-1;
        }
        
        if(Players[2].playing)
        {
            c2[0]=Players[2].Hand[0].idCard;
            c2[1]=Players[2].Hand[1].idCard;
            c2[2]=Cards[0].idCard;
            c2[3]=Cards[1].idCard;
            c2[4]=Cards[2].idCard;
            c2[5]=Cards[3].idCard;
            c2[6]=Cards[4].idCard;
        }
        else
        {
            c2[0]=-1;
        }
        
        if(Players[3].playing)
        {
            c3[0]=Players[3].Hand[0].idCard;
            c3[1]=Players[3].Hand[1].idCard;
            c3[2]=Cards[0].idCard;
            c3[3]=Cards[1].idCard;
            c3[4]=Cards[2].idCard;
            c3[5]=Cards[3].idCard;
            c3[6]=Cards[4].idCard;
        }
        else
        {
            c3[0]=-1;
        }
        int winner=calcularguanyador(c0,c1,c2,c3);
        
        Players[winner].money+=money;
        Players[turn].turnOff();
        Restart(Players[0].money,Players[1].money,Players[2].money,Players[3].money);
        std::cout<<"WINNER : "<<winner<<std::endl;
        
    }
    for(int i=0;i<4;i++)
    {
        Players[i].tableBet=bet;

        if(!Players[i].playing)
        {
            Players[i].lastBet=bet;
        }
        if(Players[i].lastBet==bet)
        {
            Players[i].canCheck=true;
        }
        else
        {
            Players[i].canCheck=false;
        }
    }
    
    if(preflop)
    {
        Cards[2].drawCard=true;
        Cards[3].drawCard=true;
        Cards[4].drawCard=true;

        if(!Players[turn].active or !Players[turn].playing)
        {
            int sB;
            if(smallBlind+1==4)
            {
                sB=0;
            }
            else
            {
                sB=smallBlind+1;
            }
            if(turn==sB)
            {
                talked=true;
            }
            if(Players[turn].confirmed)
            {
                bet=Players[turn].lastBet+Players[turn].bet;
                money+=bet;
                Players[turn].confirmed=false;
                Players[turn].lastBet+=Players[turn].bet;
            }

            Players[turn].turnOff();
            turn++;
            if(turn==4)
            {
                turn=0;
            }
            
            if(Players[turn].lastBet-bet==0 and talked)
            {
                talked=false;
                preflop=false;
                flop=true;
                Cards[1].drawCard=true;
                Cards[2].covered=false;
                Cards[3].covered=false;
                Cards[4].covered=false;
                turn=smallBlind;
                Players[turn].turnOn(bet);
            }
            else
            {
                Players[turn].turnOn(bet);

            }
        }
    }
    else if(flop)
    {
        if(!Players[turn].active or !Players[turn].playing)
        {
            if(Players[turn].confirmed)
            {
                bet=Players[turn].lastBet+Players[turn].bet;
                money+=bet;
                Players[turn].confirmed=false;
                Players[turn].lastBet+=Players[turn].bet;
            }
            Players[turn].turnOff();
            turn++;
            if(turn==4)
            {
                turn=0;
            }
            if(turn==smallBlind)
            {
                talked=true;
            }
            if(Players[turn].lastBet-bet==0 and talked)
            {
                talked=false;
                flop=false;
                preriver=true;
                Cards[1].covered=false;
                Cards[0].drawCard=true;
                turn=smallBlind;
                Players[turn].turnOn(bet);
            }
            else
            {
                Players[turn].turnOn(bet);
            }

        }
    }
    else if(preriver)
    {
        if(!Players[turn].active or !Players[turn].playing)
        {
            if(Players[turn].confirmed)
            {
                bet=Players[turn].lastBet+Players[turn].bet;
                money+=bet;
                Players[turn].confirmed=false;
                Players[turn].lastBet+=Players[turn].bet;
            }
            Players[turn].turnOff();
            turn++;
            if(turn==4)
            {
                turn=0;
            }
            if(turn==smallBlind)
            {
                talked=true;
            }
            if(Players[turn].lastBet-bet==0 and talked)
            {
                talked=false;
                preriver=false;
                river=true;
                Cards[0].covered=false;
                turn=smallBlind;
                Players[turn].turnOn(bet);
            }
            else
            {
                Players[turn].turnOn(bet);
            }
            
        }
    }
    else if(river)
    {
        if(!Players[turn].active or !Players[turn].playing)
        {
            if(Players[turn].confirmed)
            {
                bet=Players[turn].lastBet+Players[turn].bet;
                money+=bet;
                Players[turn].confirmed=false;
                Players[turn].lastBet+=Players[turn].bet;
            }
            Players[turn].turnOff();
            turn++;
            if(turn==4)
            {
                turn=0;
            }
            if(turn==smallBlind)
            {
                talked=true;
            }
            if(Players[turn].lastBet-bet==0 and talked)
            {
                talked=false;
                river=false;
                if(Players[0].playing)
                {
                    c0[0]=Players[0].Hand[0].idCard;
                    c0[1]=Players[0].Hand[1].idCard;
                    c0[2]=Cards[0].idCard;
                    c0[3]=Cards[1].idCard;
                    c0[4]=Cards[2].idCard;
                    c0[5]=Cards[3].idCard;
                    c0[6]=Cards[4].idCard;
                }
                else
                {
                    c0[0]=-1;
                }
                
                if(Players[1].playing)
                {
                    c1[0]=Players[1].Hand[0].idCard;
                    c1[1]=Players[1].Hand[1].idCard;
                    c1[2]=Cards[0].idCard;
                    c1[3]=Cards[1].idCard;
                    c1[4]=Cards[2].idCard;
                    c1[5]=Cards[3].idCard;
                    c1[6]=Cards[4].idCard;
                }
                else
                {
                    c1[0]=-1;
                }

                if(Players[2].playing)
                {
                    c2[0]=Players[2].Hand[0].idCard;
                    c2[1]=Players[2].Hand[1].idCard;
                    c2[2]=Cards[0].idCard;
                    c2[3]=Cards[1].idCard;
                    c2[4]=Cards[2].idCard;
                    c2[5]=Cards[3].idCard;
                    c2[6]=Cards[4].idCard;
                }
                else
                {
                    c2[0]=-1;
                }
                
                if(Players[3].playing)
                {
                    c3[0]=Players[3].Hand[0].idCard;
                    c3[1]=Players[3].Hand[1].idCard;
                    c3[2]=Cards[0].idCard;
                    c3[3]=Cards[1].idCard;
                    c3[4]=Cards[2].idCard;
                    c3[5]=Cards[3].idCard;
                    c3[6]=Cards[4].idCard;
                }
                else
                {
                    c3[0]=-1;
                }
                
                int winner=calcularguanyador(c0,c1,c2,c3);
                Players[winner].money+=money;
                Players[turn].turnOff();
                Restart(Players[0].money,Players[1].money,Players[2].money,Players[3].money);

                
                std::cout<<"WINNER : "<<winner<<std::endl;
                

                
            }
            else
            {
                Players[turn].turnOn(bet);
            }
            
        }
    }

    
}

int Game::GetRandomCard()
{
    int index = rand() % Deck.size();
    int id=Deck[index];
    Deck.erase(Deck.begin()+index);
    return id;
}

void Game::StartGame()
{
    Players[turn].money-=10;
    Players[turn].lastBet=10;
    Players[turn].position=0;
    
    
    turn++;
    if(turn==numPlayers)
    {
        turn=0;
    }
    while(!Players[turn].playing)
    {
        turn++;
        if(turn==numPlayers)
        {
            turn=0;
        }
    }
    
    Players[turn].position=1;
    Players[turn].money-=20;
    Players[turn].lastBet=20;
    
    turn++;

    if(turn==numPlayers)
    {
        turn=0;
    }
    while(!Players[turn].playing)
    {
        turn++;
        if(turn==numPlayers)
        {
            turn=0;
        }
    }
    bet=20;
    money=30;
    Players[turn].canCheck=false;
    Players[turn].turnOn(bet);
    lastBet=20;
    firstPlayer=turn;
    preflop=true;

    
}
