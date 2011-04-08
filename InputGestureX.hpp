/*

    AIDoubleTapÒ ÉS UNA PLANTILLA!!
    canvieu totes les DoubleTap pel nom del vostre gest

    Poseu aquí el vostre nom, data, etc...

*/

//Recordeu de canviar les DoubleTap
#ifndef INPUTGESTUREDoubleTap_HPP_INCLUDED
#define INPUTGESTUREDoubleTap_HPP_INCLUDED

//Afegiu els includes dels InputGestures que necessiteu
#include "InputGestureDirectFingers.hpp"

namespace tuio
{

//******************************************************************
//                      DECLARACIÓ DELS EVENTS
//******************************************************************

// feu servir SimpleDeclareEvent
// 1r argument: Classe Capacitat (CanDoubleTap)
// 2n argument: Mètode de la interfície que es cridarà
// 3r argument: Llista dels tipus dels arguments

SimpleDeclareEvent(CanDoubleTap,Event1,float,float);
SimpleDeclareEvent(CanDoubleTap,Event2,int,float);


//******************************************************************
//                 DECLARACIÓ DE L'INPUT GESTURE
//******************************************************************

// Aquí declarem la classe Input Gesture (InputGestureDoubleTap)
// la farem derivar de CompositeGesture ja que es basa en altres gestos
// afegim capacitats com si es tractés de la classe Graphic
// ALERTA: noteu que no fem servir OnTable! No ens toca a nosaltres
// definir el tipus d'àrea, si n'hi ha.

class InputGestueDoubleTap : public CanDirectFingers < CompositeGesture >
{
    public:
    InputGestueDoubleTap(){}

    //Interficie definida per la capacitat
    virtual void newCursor(DirectFinger * f)
    {
        // Llançem un event: Event1
        // fem servir SimpleCallEvent
        // 1r argument: Classe Capacitat (CanDoubleTap)
        // 2n argument: Mètode de la interfície que es cridarà
        // 3r argument: Entre parèntesis, els arguments del mètode
        SimpleCallEvent(CanDoubleTap,Event1,(0.23,0.35));
    }
    virtual void removeCursor(DirectFinger *f)
    {
        SimpleCallEvent(CanDoubleTap,Event2,(66,0.35));
    }
    virtual void updateCursor(DirectFinger *){}
    virtual void enterCursor(DirectFinger *df){}
    virtual void eDoubleTapitCursor(DirectFinger *f){}
};


//******************************************************************
//                 DECLARACIÓ DE LA CAPACITAT
//******************************************************************
// Comentari friki:
// FiDoubleTapeu-vos que és un template, al instanciar CanDoubleTap<A> es crea una
// classe CanDoubleTap<A>: public A de forma que podem definir els antecessors
//

template<class Base>
class CanDoubleTap: public Base
{
    public:
    //Aquí poseu els mètodes dels events amb els seus arguments i tota la pesca
    //***HAN DE SER VIRTUALS***

    //Interface redefined
    virtual void Event1(float a, float b){}
    virtual void Event2(int c, float d){}



    //Aquí sota hem de registrar els event i la capacitat
    void Register(Area * a)
    {
        // Aquesta línia sempre va aquí, bàsicament és per registrar
        // altres capacitats que pugui tenir la classe
        Base::Register(a);

        // Aquí registrem els events
        // fem servir SimpleRegisterEvent
        // 1r argument: Classe Capacitat (CanDoubleTap)
        // 2n argument: Mètode de la interfície que es cridarà
        SimpleRegisterEvent(CanDoubleTap, Event1);
        SimpleRegisterEvent(CanDoubleTap, Event2);

        // AiDoubleTapò va també sempre aquí, simplement registra el Input Gesture (InputGestureDoubleTap)
        Base::template registerIG<InputGestueDoubleTap>();
    }
};

}

#endif

