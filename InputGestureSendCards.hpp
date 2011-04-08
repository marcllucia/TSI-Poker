/*
 
 Gest Per tirar les Cartes
 
 SendCards
 */

//Recordeu de canviar les MyDoubleTap
#ifndef INPUTGESTURESendCards_HPP_INCLUDED
#define INPUTGESTURESendCards_HPP_INCLUDED

//Afegiu els includes dels InputGestures que necessiteu
#include "InputGestureDirectFingers.hpp"

namespace tuio
{
    
    //******************************************************************
    //                      DECLARACI” DELS EVENTS
    //******************************************************************
    
    // feu servir SimpleDeclareEvent
    // 1r argument: Classe Capacitat (CanMyDoubleTap)
    // 2n argument: MËtode de la interfÌcie que es cridar‡
    // 3r argument: Llista dels t1pus dels arguments
    
    SimpleDeclareEvent(CanSendCards,SendCards,float,float,float,float,float,float);
    
    
    //******************************************************************
    //                 DECLARACI” DE L'INPUT GESTURE
    //******************************************************************
    
    // AquÌ declarem la classe Input Gesture (InputGestureMyDoubleTap)
    // la farem derivar de CompositeGesture ja que es basa en altres gestos
    // afegim capacitats com si es tractÈs de la classe Graphic
    // ALERTA: noteu que no fem servir OnTable! No ens toca a nosaltres
    // definir el t1pus d'‡rea, si n'hi ha.
    
    
    class MESendCards
    {
    public:
        enum Estat {mort, onefinger, twofinger, oneleft, done} estat;
        int id_cursor1;
        int id_cursor2;
        float x1_i, y1_i, x1_o, y1_o;
        float x2_i, y2_i, x2_o, y2_o;
        float t1,t2;
        float v1, v2;
        float aux, aux2;
        
        std::list<TEvent *> & events;
        
        MESendCards(std::list<TEvent *> & _events):estat(mort),events(_events){}
        
        virtual void newCursor(DirectFinger * f)
        {
            
            if(estat == mort)
            {
                id_cursor1 = f->s_id;
                x1_i = f->getX();
                y1_i = f->getY();
                t1 = ofGetElapsedTimef();
                //canviem estat
                estat = onefinger;
            }
            else if(estat == onefinger)
            {
                id_cursor2 = f->s_id;
                x2_i = f->getX();
                y2_i = f->getY();
                t2 = ofGetElapsedTimef();
                //canviem estat*/
                estat = twofinger;
            }
            else if(estat == twofinger)
            {
                estat = mort;
            }
            else if(estat == oneleft)
            {
                estat = mort;
            }
            
        }
        virtual void removeCursor(DirectFinger *f)
        {
            
            if (estat == onefinger and id_cursor1 == f->s_id)
            {
                estat = mort;
            }
            else if (estat == twofinger and ((id_cursor2 == f->s_id) or (id_cursor1 == f->s_id)))
            {
                if(id_cursor1 == f->s_id)
                {
                    // si hem tret el primer dit, guardem la x1 i y1 finals
                    x1_o = f->getX();
                    y1_o = f->getY();
                    t1 = ofGetElapsedTimef();
                    aux = x1_o - x1_i;
                    aux2 = y1_o - y1_i;
                    aux = sqrt(pow(aux,2) + pow(aux2,2));
                    v1 = aux/t1;
                    estat = oneleft;
                }
                else if(id_cursor2 == f->s_id)
                {
                    // si hem tret el primer dit, guardem la x1 i y1 finals
                    x2_o = f->getX();
                    y2_o = f->getY();
                    t2 = ofGetElapsedTimef();
                    aux = x2_o - x2_i;
                    aux2 = y2_o - y2_i;
                    aux = sqrt(pow(aux,2) + pow(aux2,2));
                    v2 = aux/t2;
                    
                    estat = oneleft;
                }
            }
            else if(estat == oneleft and ((id_cursor2 == f->s_id) or (id_cursor1 == f->s_id)))
            {
                if(id_cursor1 == f->s_id)
                {
                    t1 = ofGetElapsedTimef();
                    if(f->getDistance(x2_o,y2_o)<0.2)
                    {
                        aux = x1_o - x1_i;
                        aux2 = y1_o - y1_i;
                        aux = sqrt(pow(aux,2) + pow(aux2,2));
                        v1 = aux/t1;
                        SimpleCallEvent(CanSendCards,SendCards,(v1,v2,x1_i,y1_i,x2_i,y2_i));
                    }
                }
                else if(id_cursor2 == f->s_id)
                {
                    t2 = ofGetElapsedTimef();
                    if(f->getDistance(x1_o,y1_o)<0.2/* and abs(t2-t1) < 0.2*/)
                    {
                        aux = x2_o - x2_i;
                        aux2 = y2_o - y2_i;
                        aux = sqrt(pow(aux,2) + pow(aux2,2));
                        v2 = aux/t2;
                        SimpleCallEvent(CanSendCards,SendCards,(v1,v2,x1_i,y1_i,x2_i,y2_i));
                    }
                }
                estat = mort;
            }
            
        }
    };
    
    
    class InputGestueSendCards : public CanDirectFingers < CompositeGesture >
    {
    public:
        std::list < MESendCards * > llista_me;
        
        InputGestueSendCards(){}
        
        //Interficie definida per la capacitat
        virtual void newCursor(DirectFinger * f)
        {
            //creem una maquina d'estats
            llista_me.push_back(new MESendCards(events) );
            int cont=0;
            
            for (std::list < MESendCards * >::iterator it= llista_me.begin();
                 it != llista_me.end(); ++it)
            {
                MESendCards * me = *it;
                me->newCursor(f);
                //mirem si esta morta
                if(me->estat == MESendCards::mort )
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
            llista_me.push_back(new MESendCards(events) );
            int cont=0;
            
            for (std::list < MESendCards * >::iterator it= llista_me.begin();
                 it != llista_me.end(); ++it, cont++)
            {
                
                MESendCards * me = *it;
                me->removeCursor(f);
                //mirem si esta morta
                if(me->estat == MESendCards::mort )
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
    //                 DECLARACI” DE LA CAPACITAT
    //******************************************************************
    // Comentari friki:
    // Fixeu-vos que Ès un template, al instanciar CanMyDoubleTap<A> es crea una
    // classe CanMyDoubleTap<A>: public A de forma que podem definir els antecessors
    //
    
    template<class Base>
    class CanSendCards: public Base
    {
    public:
        //AquÌ poseu els mËtodes dels events amb els seus arguments i tota la pesca
        //***HAN DE SER VIRTUALS***
        
        //Interface redefined
        virtual void SendCards(float v1, float v2,float x1, float y1, float x2, float y2){}
        
        
        
        //AquÌ sota hem de registrar els event i la capacitat
        void Register(Area * a)
        {
            // Aquesta lÌnia sempre va aquÌ, b‡sicament Ès per registrar
            // altres capacitats que pugui tenir la classe
            Base::Register(a);
            
            // AquÌ registrem els events
            // fem servir SimpleRegisterEvent
            // 1r argument: Classe Capacitat (CanMyDoubleTap)
            // 2n argument: MËtode de la interfÌcie que es cridar‡
            SimpleRegisterEvent(CanSendCards, SendCards);
            
            // AixÚ va tambÈ sempre aquÌ, simplement registra el Input Gesture (InputGestureMyDoubleTap)
            Base::template registerIG<InputGestueSendCards>();
        }
    };
    
}

#endif