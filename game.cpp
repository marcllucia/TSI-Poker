#include "game.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>

Game::Game()
{
    numPlayers=4;
    srand((unsigned)time(0));

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
    
    StartGame();
}

void Game::DealCards()
{
    for (int i=0;i<4;i++)
    {
        Players[i].Hand[0].idCard=GetRandomCard();
        Players[i].Hand[1].idCard=GetRandomCard();
        std::cout <<"Player " << i<<": "<< Players[i].Hand[0].idCard << " , "<<Players[i].Hand[1].idCard<<std::endl;
    }
    
    for (int i=0;i<5;i++)
    {
        Cards[i].idCard=GetRandomCard();
    }

}

void Game::InitializePlayers()
{
    Players[0].Hand[0].area.set(0.405,0.040,0.07,0.098);
    Players[0].Hand[0].texture.loadImage(textureData[Players[0].Hand[0].idCard]);
    Players[0].Hand[0].reactZone.set(Players[0].Hand[0].area.x,Players[0].Hand[0].area.y+Players[0].Hand[0].area.height/4*3,Players[0].Hand[0].area.width,Players[0].Hand[0].area.height/4);
    
    Players[0].Hand[1].area.set(0.525,0.040,0.07,0.098);
    Players[0].Hand[1].texture.loadImage(textureData[Players[0].Hand[1].idCard]);
    Players[0].Hand[1].reactZone.set(Players[0].Hand[1].area.x,Players[0].Hand[1].area.y+Players[0].Hand[1].area.height/4*3,Players[0].Hand[1].area.width,Players[0].Hand[1].area.height/4);
    
    Players[1].Hand[0].area.set(1-0.098-0.040,0.405,0.098,0.07);
    Players[1].Hand[0].texture.loadImage(textureData[Players[3].Hand[0].idCard]);
    Players[1].Hand[0].reactZone.set(Players[1].Hand[0].area.x,Players[1].Hand[0].area.y,Players[1].Hand[0].area.width/4,Players[1].Hand[0].area.height);
    
    Players[1].Hand[1].area.set(1-0.098-0.040,0.525,0.098,0.07);
    Players[1].Hand[1].texture.loadImage(textureData[Players[3].Hand[1].idCard]);
    Players[1].Hand[1].reactZone.set(Players[1].Hand[1].area.x,Players[1].Hand[1].area.y,Players[1].Hand[1].area.width/4,Players[1].Hand[1].area.height);

    Players[2].Hand[0].area.set(0.405,1-0.098-0.040,0.07,0.098);
    Players[2].Hand[0].texture.loadImage(textureData[Players[2].Hand[0].idCard]);
    Players[2].Hand[0].reactZone.set(Players[2].Hand[0].area.x,Players[2].Hand[0].area.y,Players[2].Hand[0].area.width,Players[2].Hand[0].area.height/4);

    Players[2].Hand[1].area.set(0.525,1-0.098-0.040,0.07,0.098);
    Players[2].Hand[1].texture.loadImage(textureData[Players[2].Hand[1].idCard]);
    Players[2].Hand[1].reactZone.set(Players[2].Hand[1].area.x,Players[2].Hand[1].area.y,Players[2].Hand[1].area.width,Players[2].Hand[1].area.height/4);
    
    Players[3].Hand[0].area.set(0.040,0.405,0.098,0.07);
    Players[3].Hand[0].texture.loadImage(textureData[Players[1].Hand[0].idCard]);
    Players[3].Hand[0].reactZone.set(Players[3].Hand[0].area.x+Players[3].Hand[0].area.width/4*3,Players[3].Hand[0].area.y,Players[3].Hand[0].area.width/4,Players[3].Hand[0].area.height);
    
    Players[3].Hand[1].area.set(0.040,0.525,0.098,0.07);
    Players[3].Hand[1].texture.loadImage(textureData[Players[1].Hand[1].idCard]);
    Players[3].Hand[1].reactZone.set(Players[3].Hand[1].area.x+Players[3].Hand[1].area.width/4*3,Players[3].Hand[1].area.y,Players[3].Hand[1].area.width/4,Players[3].Hand[1].area.height);    

    
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
        Players[i].money=1000;
        Players[i].playing=true;
    }
    
    Players[0].zone.setPoint(0.33,0.089);
    Players[0].zone.chipTexture.loadImage("images/pica-chip.png");
    Players[1].zone.setPoint(1-0.089,0.33);
    Players[1].zone.chipTexture.loadImage("images/cor-chip.png");
    Players[2].zone.setPoint(1-0.33,1-0.089);
    Players[2].zone.chipTexture.loadImage("images/trebol-chip.png");
    Players[3].zone.setPoint(0.089,1-0.33);
    Players[3].zone.chipTexture.loadImage("images/rombo-chip.png");
    
}


void Game::draw()
{
    for( map<int,tuio::DirectObject*>::iterator it=objects.begin(); it!=objects.end(); ++it)
    {
        DirectObject * obj = it->second;
        ofImage card;
        ofPushMatrix();
        ofTranslate(obj->getX(),obj->getY(),0);
        ofRotateZ(obj->angle*180/3.1415);
        ofTranslate(-(obj->getX()),-(obj->getY()),0);
        card.draw(obj->getX()-(0.07/2),obj->getY()-(0.098/4),0.08,0.11);
        ofPopMatrix();
    }    
}

void Game::update()
{

    if(!Players[turn].playing or !Players[turn].active)
    {
        Players[turn].active=false;
        Players[turn].zone.increment=0;
        Players[turn].zone.radi=0.039;
        turn++;
        if(turn==numPlayers)
        {
            turn=0;
        }
        Players[turn].active=true;
        Players[turn].zone.increment=0.00075;
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
    turn++;
    if(turn==numPlayers)
    {
        turn=0;
    }
    else
    {
        Players[turn].money-=20;
    }
    turn++;
    
    if(turn==numPlayers)
    {
        turn=0;
    }
    else
    {
        Players[turn].active=true;
        Players[turn].zone.increment=0.0002;
    }
    
    money=10+20;
    bet=20;

}
