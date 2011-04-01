#include "player.h"
#include "game.h"
#include "card.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>

Game::Game()
{
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
   
    InitializePlayerCards();
    dealer=rand() % 4;

}

void Game::DealCards()
{
    for (int i=0;i<4;i++)
    {
        
        Players[i].Hand[0]=GetRandomCard();
        Players[i].Hand[1]=GetRandomCard();
        std::cout <<"Player " << i<<": "<< Players[i].Hand[0].idCard << " , "<<Players[i].Hand[1].idCard<<std::endl;
    }

}

void Game::InitializePlayerCards()
{
    Players[0].Hand[0].area.set(0.405,0.025,0.07,0.09777777777777777);
    Players[0].Hand[0].texture.loadImage(textureData[Players[0].Hand[0].idCard]);
    Players[0].Hand[1].area.set(0.525,0.025,0.07,0.09777777777777777);
    Players[0].Hand[1].texture.loadImage(textureData[Players[0].Hand[1].idCard]);

    Players[1].Hand[0].area.set(0.025,0.405,0.09777777777777777,0.07);
    Players[1].Hand[0].texture.loadImage(textureData[Players[1].Hand[0].idCard]);
    Players[1].Hand[1].area.set(0.025,0.525,0.09777777777777777,0.07);
    Players[1].Hand[1].texture.loadImage(textureData[Players[1].Hand[1].idCard]);

    Players[2].Hand[0].area.set(0.405,1-0.09777777777777777-0.025,0.07,0.09777777777777777);
    Players[2].Hand[0].texture.loadImage(textureData[Players[2].Hand[0].idCard]);
    Players[2].Hand[1].area.set(0.525,1-0.09777777777777777-0.025,0.07,0.09777777777777777);
    Players[2].Hand[1].texture.loadImage(textureData[Players[2].Hand[1].idCard]);

    Players[3].Hand[0].area.set(1-0.09777777777777777-0.025,0.405,0.09777777777777777,0.07);
    Players[3].Hand[0].texture.loadImage(textureData[Players[3].Hand[0].idCard]);
    Players[3].Hand[1].area.set(1-0.09777777777777777-0.025,0.525,0.09777777777777777,0.07);
    Players[3].Hand[1].texture.loadImage(textureData[Players[3].Hand[1].idCard]);
}

/*void Game::draw()
{
    if(objects.size()>0)
    {
            ofRectangle card1=Players[0].card1;

            ofSetColor(255,255,255);
            ofEnableAlphaBlending();
            Deck[0].texture.draw(card1.x,card1.y,card1.width,card1.height);
            ofDisableAlphaBlending();
    }
}*/

void Game::update()
{
    for(int i=0; i<4; i++)
    {
        for (int j=0; j<2; j++)
        {
            ofRectangle rect=Players[i].Hand[j].area;
            bool on=false;
            for( map<int,tuio::DirectObject*>::iterator it=objects.begin(); it!=objects.end(); ++it)
            {
                if(!on)
                {
                    DirectObject * obj = it->second;
                    if(obj->getX()>rect.x&&obj->getX()<rect.x+rect.width&&obj->getY()>rect.y&&obj->getY()<rect.y+rect.height)
                    {
                        Players[i].Hand[j].covered=false;
                        on=true;
                    }
                    else
                    {
                        Players[i].Hand[j].covered=true;
                    }
                }
            }
        }
    }
}

Card Game::GetRandomCard()
{
    int index = rand() % Deck.size();
    int id=Deck[index];
    Card c=* new Card();
    c.idCard=id;
    Deck.erase(Deck.begin()+index);
    return c;
}
