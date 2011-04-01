/*

    AIDoubleTap� �S UNA PLANTILLA!!
    canvieu totes les DoubleTap pel nom del vostre gest

    Poseu aqu� el vostre nom, data, etc...

*/

//Recordeu de canviar les DoubleTap
#ifndef INPUTGESTUREDoubleTap_HPP_INCLUDED
#define INPUTGESTUREDoubleTap_HPP_INCLUDED

//Afegiu els includes dels InputGestures que necessiteu
#include "InputGestureDirectFingers.hpp"

namespace tuio
{

//******************************************************************
//                      DECLARACI� DELS EVENTS
//******************************************************************

// feu servir SimpleDeclareEvent
// 1r argument: Classe Capacitat (CanDoubleTap)
// 2n argument: M�tode de la interf�cie que es cridar�
// 3r argument: Llista dels tipus dels arguments

SimpleDeclareEvent(CanDoubleTap,Event1,float,float);
SimpleDeclareEvent(CanDoubleTap,Event2,int,float);


//******************************************************************
//                 DECLARACI� DE L'INPUT GESTURE
//******************************************************************

// Aqu� declarem la classe Input Gesture (InputGestureDoubleTap)
// la farem derivar de CompositeGesture ja que es basa en altres gestos
// afegim capacitats com si es tract�s de la classe Graphic
// ALERTA: noteu que no fem servir OnTable! No ens toca a nosaltres
// definir el tipus d'�rea, si n'hi ha.

class InputGestueDoubleTap : public CanDirectFingers < CompositeGesture >
{
    public:
    InputGestueDoubleTap(){}

    //Interficie definida per la capacitat
    virtual void newCursor(DirectFinger * f)
    {
        // Llan�em un event: Event1
        // fem servir SimpleCallEvent
        // 1r argument: Classe Capacitat (CanDoubleTap)
        // 2n argument: M�tode de la interf�cie que es cridar�
        // 3r argument: Entre par�ntesis, els arguments del m�tode
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
//                 DECLARACI� DE LA CAPACITAT
//******************************************************************
// Comentari friki:
// FiDoubleTapeu-vos que �s un template, al instanciar CanDoubleTap<A> es crea una
// classe CanDoubleTap<A>: public A de forma que podem definir els antecessors
//

template<class Base>
class CanDoubleTap: public Base
{
    public:
    //Aqu� poseu els m�todes dels events amb els seus arguments i tota la pesca
    //***HAN DE SER VIRTUALS***

    //Interface redefined
    virtual void Event1(float a, float b){}
    virtual void Event2(int c, float d){}



    //Aqu� sota hem de registrar els event i la capacitat
    void Register(Area * a)
    {
        // Aquesta l�nia sempre va aqu�, b�sicament �s per registrar
        // altres capacitats que pugui tenir la classe
        Base::Register(a);

        // Aqu� registrem els events
        // fem servir SimpleRegisterEvent
        // 1r argument: Classe Capacitat (CanDoubleTap)
        // 2n argument: M�tode de la interf�cie que es cridar�
        SimpleRegisterEvent(CanDoubleTap, Event1);
        SimpleRegisterEvent(CanDoubleTap, Event2);

        // AiDoubleTap� va tamb� sempre aqu�, simplement registra el Input Gesture (InputGestureDoubleTap)
        Base::template registerIG<InputGestueDoubleTap>();
    }
};

}

#endif

