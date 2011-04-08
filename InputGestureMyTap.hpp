
/*

    AIXÒ ÉS UNA PLANTILLA!!
    canvieu totes les X pel nom del vostre gest

    Poseu aquí el vostre nom, data, etc...

*/

//Recordeu de canviar les MyTap
#ifndef INPUTGESTUREMyTap_HPP_INCLUDED
#define INPUTGESTUREMyTap_HPP_INCLUDED

//Afegiu els includes dels InputGestures que necessiteu
#include "InputGestureDirectFingers.hpp"

namespace tuio
{

//******************************************************************
//                      DECLARACIÓ DELS EVENTS
//******************************************************************

// feu servir SimpleDeclareEvent
// 1r argument: Classe Capacitat (CanMyTap)
// 2n argument: Mètode de la interfície que es cridarà
// 3r argument: Llista dels tipus dels arguments

SimpleDeclareEvent(CanMyTap,MyTap,float,float);


//******************************************************************
//                 DECLARACIÓ DE L'INPUT GESTURE
//******************************************************************

// Aquí declarem la classe Input Gesture (InputGestureMyTap)
// la farem derivar de CompositeGesture ja que es basa en altres gestos
// afegim capacitats com si es tractés de la classe Graphic
// ALERTA: noteu que no fem servir OnTable! No ens toca a nosaltres
// definir el tipus d'àrea, si n'hi ha.


class MEMyTap
{
    public:
    enum Estat {mort, dins} estat;
    int id_cursor;
    float xi, yi;
    float ti;

    std::list<TEvent *> & events;

    MEMyTap(std::list<TEvent *> & _events):estat(mort),events(_events){}

    virtual void newCursor(DirectFinger * f)
    {
        if(estat == mort)
        {
            id_cursor = f->s_id;
            xi = f->getX();
            yi = f->getY();
            ti = ofGetElapsedTimef();
            //canviem estat
            estat = dins;

        }
    }
    virtual void removeCursor(DirectFinger *f)
    {
        if (estat == dins and id_cursor == f->s_id)
        {
            //comprovem que és Tap
            if( f->getDistance(xi,yi) < 0.01
                and (ofGetElapsedTimef() - ti) < 0.2)
            {
                SimpleCallEvent(CanMyTap,MyTap,(f->getX(),f->getY()));
            }
            estat = mort;
        }
    }
};


class InputGestueMyTap : public CanDirectFingers < CompositeGesture >
{
    public:
    std::list < MEMyTap * > llista_me;

    InputGestueMyTap(){}

    //Interficie definida per la capacitat
    virtual void newCursor(DirectFinger * f)
    {
        //creem una maquina d'estats
        llista_me.push_back(new MEMyTap(events) );

        for (std::list < MEMyTap * >::iterator it= llista_me.begin();
                it != llista_me.end(); ++it)
                {
                    MEMyTap * me = *it;
                    me->newCursor(f);
                    //mirem si esta morta
                    if(me->estat == MEMyTap::mort )
                    {
                        delete me;
                        (*it) =NULL;
                    }
                }
        llista_me.remove(NULL);

    }
    virtual void removeCursor(DirectFinger *f)
    {
        //creem una maquina d'estats
        llista_me.push_back(new MEMyTap(events) );

        for (std::list < MEMyTap * >::iterator it= llista_me.begin();
                it != llista_me.end(); ++it)
                {
                    MEMyTap * me = *it;
                    me->removeCursor(f);
                    //mirem si esta morta
                    if(me->estat == MEMyTap::mort )
                    {
                        delete me;
                        (*it) =NULL;
                    }
                }
        llista_me.remove(NULL);
    }
    virtual void updateCursor(DirectFinger *){}
    virtual void enterCursor(DirectFinger *df){}
    virtual void exitCursor(DirectFinger *f){}
};


//******************************************************************
//                 DECLARACIÓ DE LA CAPACITAT
//******************************************************************
// Comentari friki:
// Fixeu-vos que és un template, al instanciar CanMyTap<A> es crea una
// classe CanMyTap<A>: public A de forma que podem definir els antecessors
//

template<class Base>
class CanMyTap: public Base
{
    public:
    //Aquí poseu els mètodes dels events amb els seus arguments i tota la pesca
    //***HAN DE SER VIRTUALS***

    //Interface redefined
    virtual void MyTap(float x, float y){}



    //Aquí sota hem de registrar els event i la capacitat
    void Register(Area * a)
    {
        // Aquesta línia sempre va aquí, bàsicament és per registrar
        // altres capacitats que pugui tenir la classe
        Base::Register(a);

        // Aquí registrem els events
        // fem servir SimpleRegisterEvent
        // 1r argument: Classe Capacitat (CanMyTap)
        // 2n argument: Mètode de la interfície que es cridarà
        SimpleRegisterEvent(CanMyTap, MyTap);

        // Això va també sempre aquí, simplement registra el Input Gesture (InputGestureMyTap)
        Base::template registerIG<InputGestueMyTap>();
    }
};

}

#endif
