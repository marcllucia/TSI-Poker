/*

    AIXÒ ÉS UNA PLANTILLA!!
    canvieu totes les X pel nom del vostre gest

    Poseu aquí el vostre nom, data, etc...

*/

//Recordeu de canviar les X
#ifndef INPUTGESTUREAposta_HPP_INCLUDED
#define INPUTGESTUREAposta_HPP_INCLUDED

//Afegiu els includes dels InputGestures que necessiteu
//#include "InputGestureDirectObjects.hpp"

namespace tuio
{

//******************************************************************
//                      DECLARACIÓ DELS EVENTS
//******************************************************************

// feu servir SimpleDeclareEvent
// 1r argument: Classe Capacitat (CanX)
// 2n argument: Mètode de la interfície que es cridarà
// 3r argument: Llista dels tipus dels arguments

SimpleDeclareEvent(CanAposta,Aposta,float,float,float);
//SimpleDeclareEvent(CanThrowChips,Event2,int,float);


//******************************************************************
//                 DECLARACIÓ DE L'INPUT GESTURE
//******************************************************************

// Aquí declarem la classe Input Gesture (InputGestureX)
// la farem derivar de CompositeGesture ja que es basa en altres gestos
// afegim capacitats com si es tractés de la classe Graphic
// ALERTA: noteu que no fem servir OnTable! No ens toca a nosaltres
// definir el tipus d'àrea, si n'hi ha.

class InputGestueAposta : public CanDirectObjects < CompositeGesture >
{
    public:
    int id_object;
    float x1_i,y1_i,x1_o,y1_o,t1,aux,aux2, v1;
    InputGestueAposta(){}

    //Interficie definida per la capacitat
    virtual void newObject(DirectObject * object)
    {
        // Llançem un event: Event1
        // fem servir SimpleCallEvent
        // 1r argument: Classe Capacitat (CanX)
        // 2n argument: Mètode de la interfície que es cridarà
        // 3r argument: Entre parèntesis, els arguments del mètode

        id_object = object->s_id;
        x1_i = object->getX();
        y1_i = object->getY();

    }
    virtual void removeObject(DirectObject * object)
    {
        if(id_object == object->s_id)
        {
            x1_o = object->getX();
            y1_o = object->getY();
            t1 = ofGetElapsedTimef();
            aux = x1_o - x1_i;
            aux2 = y1_o - y1_i;
            aux = sqrt(pow(aux,2) + pow(aux2,2));
            v1 = aux/t1;

            SimpleCallEvent(CanAposta,Aposta,(x1_i,y1_i,v1));
        }
    }

    virtual void updateObject(DirectObject * object){}
};


//******************************************************************
//                 DECLARACIÓ DE LA CAPACITAT
//******************************************************************
// Comentari friki:
// Fixeu-vos que és un template, al instanciar CanX<A> es crea una
// classe CanX<A>: public A de forma que podem definir els antecessors
//

template<class Base>
class CanAposta: public Base
{
    public:
    //Aquí poseu els mètodes dels events amb els seus arguments i tota la pesca
    //***HAN DE SER VIRTUALS***

    //Interface redefined
    virtual void Aposta(float a, float b,float c){}



    //Aquí sota hem de registrar els event i la capacitat
    void Register(Area * a)
    {
        // Aquesta línia sempre va aquí, bàsicament és per registrar
        // altres capacitats que pugui tenir la classe
        Base::Register(a);

        // Aquí registrem els events
        // fem servir SimpleRegisterEvent
        // 1r argument: Classe Capacitat (CanX)
        // 2n argument: Mètode de la interfície que es cridarà
        SimpleRegisterEvent(CanAposta, Aposta);
     //   SimpleRegisterEvent(CanThrowChips, Event2);

        // Això va també sempre aquí, simplement registra el Input Gesture (InputGestureX)
        Base::template registerIG<InputGestueAposta>();
    }
};

}

#endif

