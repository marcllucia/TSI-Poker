/*
 
 Gest Per tirar les Cartes
 
 SendCards
 */

//Recordeu de canviar les MyDoubleTap
#ifndef INPUTGESTURETwoFingers_HPP_INCLUDED
#define INPUTGESTURETwoFingers_HPP_INCLUDED

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
    
    // SimpleDeclareEvent(CanSendCards,SendCards,float,float,float,float,float,float);
    SimpleDeclareEvent(CanTwoFingers,MoveCards,float,float);
    
    
    //******************************************************************
    //                 DECLARACI” DE L'INPUT GESTURE
    //******************************************************************
    
    // AquÌ declarem la classe Input Gesture (InputGestureMyDoubleTap)
    // la farem derivar de CompositeGesture ja que es basa en altres gestos
    // afegim capacitats com si es tractÈs de la classe Graphic
    // ALERTA: noteu que no fem servir OnTable! No ens toca a nosaltres
    // definir el t1pus d'‡rea, si n'hi ha.
    
    
    class METwoFingers
    {
    public:
        enum Estat {mort, onefinger, twofinger} estat;
        int id_cursor1;
        int id_cursor2;
        float x1_i, y1_i, x1_o, y1_o;
        float x2_i, y2_i, x2_o, y2_o;
        float aux, aux2;
        
        std::list<TEvent *> & events;
        
        METwoFingers(std::list<TEvent *> & _events):estat(mort),events(_events){}
        
        virtual void newCursor(DirectFinger * f)
        {
            
            if(estat == mort)
            {
                id_cursor1 = f->s_id;
                x1_i = f->getX();
                y1_i = f->getY();
                //canviem estat
                estat = onefinger;
            }
            else if(estat == onefinger)
            {
                id_cursor2 = f->s_id;
                x2_i = f->getX();
                y2_i = f->getY();
                //canviem estat*/
                aux = x1_i - x2_i;
                aux2 = y1_i - y2_i;
                aux = sqrt(pow(aux,2) + pow(aux2,2));
                if(aux<= 0.06)
                {
                    aux = (x1_i + x2_i)/2;
                    aux2 = (y1_i + y2_i)/2;
                    SimpleCallEvent(CanTwoFingers,MoveCards,(aux,aux2));
                    estat = twofinger;
                }
            }
            else if(estat == twofinger)
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
                estat = mort;
            }
        }
        
        virtual void updateCursor(DirectFinger * f)
        {
            if( estat == twofinger and (id_cursor1 == f->s_id or id_cursor2 == f->s_id)){
                aux = (aux + f->getX())/2;
                aux2 = (aux2 + f->getY())/2;
                //if( id_cursor1 == f->s_id )
                //{
                SimpleCallEvent(CanTwoFingers,MoveCards,(aux,aux2));
                //}
                //else if (id_cursor2 == f->s_id)
                //{
                //  SimpleCallEvent(CanTwoFingers,MoveCards,(aux,aux2));
            }
            //   }
        };
        
        
    };
    
    
    class InputGestueTwoFingers : public CanDirectFingers < CompositeGesture >
    {
    public:
        std::list < METwoFingers * > llista_me;
        
        InputGestueTwoFingers(){}
        
        //Interficie definida per la capacitat
        virtual void newCursor(DirectFinger * f)
        {
            //creem una maquina d'estats
            llista_me.push_back(new METwoFingers(events) );
            int cont=0;
            
            for (std::list < METwoFingers * >::iterator it= llista_me.begin();
                 it != llista_me.end(); ++it)
            {
                METwoFingers * me = *it;
                me->newCursor(f);
                //mirem si esta morta
                if(me->estat == METwoFingers::mort )
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
            llista_me.push_back(new METwoFingers(events) );
            int cont=0;
            
            for (std::list < METwoFingers * >::iterator it= llista_me.begin();
                 it != llista_me.end(); ++it, cont++)
            {
                
                METwoFingers * me = *it;
                me->removeCursor(f);
                //mirem si esta morta
                if(me->estat == METwoFingers::mort )
                {
                    delete me;
                    (*it) =NULL;
                }
            }
            llista_me.remove(NULL);
        }
        virtual void updateCursor(DirectFinger *f){
            
            //creem una maquina d'estats
            llista_me.push_back(new METwoFingers(events) );
            int cont=0;
            
            for (std::list < METwoFingers * >::iterator it= llista_me.begin();
                 it != llista_me.end(); ++it, cont++)
            {
                
                METwoFingers * me = *it;
                me->updateCursor(f);
                //mirem si esta morta
                if(me->estat == METwoFingers::mort )
                {
                    delete me;
                    (*it) =NULL;
                }
            }
            llista_me.remove(NULL);
            
        }
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
    class CanTwoFingers: public Base
    {
    public:
        //AquÌ poseu els mËtodes dels events amb els seus arguments i tota la pesca
        //***HAN DE SER VIRTUALS***
        
        //Interface redefined
        //virtual void SendCards(float x, float y, float z, float c, float g,float h){}
        virtual void MoveCards(float a, float b){}
        
        
        
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
            SimpleRegisterEvent(CanTwoFingers, MoveCards);
            //      SimpleRegisterEvent(CanSendCards, MoveCards);
            
            // AixÚ va tambÈ sempre aquÌ, simplement registra el Input Gesture (InputGestureMyDoubleTap)
            Base::template registerIG<InputGestueTwoFingers>();
        }
    };
    
}

#endif