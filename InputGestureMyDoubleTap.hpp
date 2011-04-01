/*

    AIXÒ ÉS UNA PLANt1LLA!!
    canvieu totes les X pel nom del vostre gest

    Poseu aquí el vostre nom, data, etc...

*/

//Recordeu de canviar les MyDoubleTap
#ifndef INPUTGESTUREMyDoubleTap_HPP_INCLUDED
#define INPUTGESTUREMyDoubleTap_HPP_INCLUDED

//Afegiu els includes dels InputGestures que necessiteu
#include "InputGestureDirectFingers.hpp"

namespace tuio
{

//******************************************************************
//                      DECLARACIÓ DELS EVENTS
//******************************************************************

// feu servir SimpleDeclareEvent
// 1r argument: Classe Capacitat (CanMyDoubleTap)
// 2n argument: Mètode de la interfície que es cridarà
// 3r argument: Llista dels t1pus dels arguments

SimpleDeclareEvent(CanMyDoubleTap,MyDoubleTap,float,float);


//******************************************************************
//                 DECLARACIÓ DE L'INPUT GESTURE
//******************************************************************

// Aquí declarem la classe Input Gesture (InputGestureMyDoubleTap)
// la farem derivar de CompositeGesture ja que es basa en altres gestos
// afegim capacitats com si es tractés de la classe Graphic
// ALERTA: noteu que no fem servir OnTable! No ens toca a nosaltres
// definir el t1pus d'àrea, si n'hi ha.


class MEMyDoubleTap
{
    public:
    enum Estat {mort, doubletap, singletap, removedtap} estat;
    int id_cursor;
    float x1, y1;
    float x2, y2;
    float t1,t2;

    std::list<TEvent *> & events;

    MEMyDoubleTap(std::list<TEvent *> & _events):estat(mort),events(_events){}

    virtual void newCursor(DirectFinger * f)
    {
        if(estat == removedtap)
        {
            id_cursor = f->s_id;
            x2 = f->getX();
            y2 = f->getY();
            t2 = ofGetElapsedTimef();
            //canviem estat
            estat = doubletap;
        }

        else if(estat == mort)
        {
            id_cursor = f->s_id;
            x1 = f->getX();
            y1 = f->getY();
            t1 = ofGetElapsedTimef();
            //canviem estat
            estat = singletap;
        }

    }
    virtual void removeCursor(DirectFinger *f)
    {

        if (estat == singletap and id_cursor == f->s_id)
        {
            //comprovem que és Tap
            if( f->getDistance(x1,y1) > 0.01
                or (ofGetElapsedTimef() - t1) > 0.2)
            {
                estat = mort;
            }else
            {

                estat=removedtap;
            }
        }

        if (estat == doubletap and id_cursor == f->s_id)
        {
            //comprovem que és DoubleTap

            if( f->getDistance(x2,y2) < 0.01
                and (ofGetElapsedTimef() - t2) < 0.2)
            {
                if(f->getDistance(x1,y1)<0.1 and abs(t1-t2) < 0.5)
                {
                    SimpleCallEvent(CanMyDoubleTap,MyDoubleTap,(f->getX(),f->getY()));
                }
            }
            estat = mort;
        }
    }
};


class InputGestueMyDoubleTap : public CanDirectFingers < CompositeGesture >
{
    public:
    std::list < MEMyDoubleTap * > llista_me;

    InputGestueMyDoubleTap(){}

    //Interficie definida per la capacitat
    virtual void newCursor(DirectFinger * f)
    {
        //creem una maquina d'estats
        llista_me.push_back(new MEMyDoubleTap(events) );
        int cont=0;

        for (std::list < MEMyDoubleTap * >::iterator it= llista_me.begin();
                it != llista_me.end(); ++it)
                {
                        MEMyDoubleTap * me = *it;
                        me->newCursor(f);
                        //mirem si esta morta
                        if(me->estat == MEMyDoubleTap::mort )
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
        llista_me.push_back(new MEMyDoubleTap(events) );
        int cont=0;

        for (std::list < MEMyDoubleTap * >::iterator it= llista_me.begin();
                it != llista_me.end(); ++it, cont++)
                {

                    MEMyDoubleTap * me = *it;
                    me->removeCursor(f);
                    //mirem si esta morta
                    if(me->estat == MEMyDoubleTap::mort )
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
// Fixeu-vos que és un template, al instanciar CanMyDoubleTap<A> es crea una
// classe CanMyDoubleTap<A>: public A de forma que podem definir els antecessors
//

template<class Base>
class CanMyDoubleTap: public Base
{
    public:
    //Aquí poseu els mètodes dels events amb els seus arguments i tota la pesca
    //***HAN DE SER VIRTUALS***

    //Interface redefined
    virtual void MyDoubleTap(float x, float y){}



    //Aquí sota hem de registrar els event i la capacitat
    void Register(Area * a)
    {
        // Aquesta línia sempre va aquí, bàsicament és per registrar
        // altres capacitats que pugui tenir la classe
        Base::Register(a);

        // Aquí registrem els events
        // fem servir SimpleRegisterEvent
        // 1r argument: Classe Capacitat (CanMyDoubleTap)
        // 2n argument: Mètode de la interfície que es cridarà
        SimpleRegisterEvent(CanMyDoubleTap, MyDoubleTap);

        // Això va també sempre aquí, simplement registra el Input Gesture (InputGestureMyDoubleTap)
        Base::template registerIG<InputGestueMyDoubleTap>();
    }
};

}

#endif
