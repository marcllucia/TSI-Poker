#include <iostream>
#include <vector>
#include "Poker.h"

int num(int id){
	return (id%13)+2;
}

int pal(int id){
	return id/13;
}

void evaluateHand(int cartes[7],int *hand,int *puntuacio)
{
	bool debug =false;
	bool debughard=debug;

	int aux;
	int maescales[5]= {-10,-10,-10,-10,-10};
	
	bool as=false;
	bool carta_alta = false;
	bool parella = false;
	bool dobleparella = false;
	bool trio = false;
	bool full = false;
	bool color = false;
	bool escala = false;
	bool escala_color = false;
	bool poker = false;
	

	int nrepetides[7] = {0,0,0,0,0,0,0};

	int a;
	int b;
		
	//int cartes[7] = {c1,c2,c3,c4,c5,c6,c7};
//	int hand[5] = {-10,-10,-10,-10,-10};

	if(debughard){
	std::cout<< cartes[0] << " es un " << (cartes[0]%13)+2 << " de " <<cartes[0]/13 <<std::endl;
	std::cout<< cartes[1] << " es un " << (cartes[1]%13)+2 << " de " <<cartes[1]/13 <<std::endl;
	std::cout<< cartes[2] << " es un " << (cartes[2]%13)+2 << " de " <<cartes[2]/13 <<std::endl;
	std::cout<< cartes[3] << " es un " << (cartes[3]%13)+2 << " de " <<cartes[3]/13 <<std::endl;
	std::cout<< cartes[4] << " es un " << (cartes[4]%13)+2 << " de " <<cartes[4]/13 <<std::endl;
	std::cout<< cartes[5] << " es un " << (cartes[5]%13)+2 << " de " <<cartes[5]/13 <<std::endl;
	std::cout<< cartes[6] << " es un " << (cartes[6]%13)+2 << " de " <<cartes[6]/13 <<std::endl;
	}
//ordenar el vector de numero mes petit a mes gran 
	for (int i=0;i<=6;i++)
	{
		for (int j=i+1;j<7;j++)
		{
			if (num(cartes[i])>num(cartes[j]))
			{
				aux=cartes[i];
				cartes[i]=cartes[j];
				cartes[j]=aux;
			}
		}
	}

	if(debug)for(int i=0;i<7;i++) std::cout << num(cartes[i])<< " de " << pal(cartes[i]) << std::endl;


	int mafinal = 0;
//quantes cartes repetides tenim de cada posició del vector 
	for(int i=0;i<7;i++)
	{	
		for(int j=0;j<7;j++)
		{
			if(num(cartes[i])==num(cartes[j])){
				nrepetides[i]++;
			}
		}
	}

	//if(debug)for(int i=0;i<7;i++) std::cout <<"Numero de repetides: "<< nrepetides[i]<<std::endl;
		//for(int i=0;i<5;i++) std::cout <<"ma: "<< num(hand[i])<<std::endl;

	
//agafar la primera posicio del vector on esta la carta mes alta q es repeteix 
	int majorcopsrepetits = nrepetides[0];	
	b = 0;
	int d = cartes[0];
	for (int i=0;i<7;i++)
	{
		
		
		if(nrepetides[i]>=majorcopsrepetits)
		{
			b=i;
			majorcopsrepetits = nrepetides[i];
			d = cartes[i];
		}
	}

	//std::cout << b <<std::endl;

//posem la carta amb numero mes alt i les seves repetides a la ma final
	int maxhand = 0;
	int maxrep = 0;
	for (int i=0;i<7;i++)
	{
		if(num(cartes[i])==num(cartes[b]) and maxhand<5 and maxrep<= nrepetides[b])
		{		
			hand[maxhand]=cartes[i];	
			maxhand++;
			maxrep++;
		}
	}
	
	
	
//mirem quantes posicions lliures hi ha a hand per saber que tenim com a mes alt 
	int nolligades = 0;	
	for(int i=0;i<5;i++)
	{
		if(hand[i]==-10)
		{
			nolligades++;
		}
	}
	if(debug)std::cout<<"No lligades: "<<nolligades<<std::endl;
//mirem si es nu poker, full, parella o doble parella 
	if(nolligades==1)
	{
		std::cout << "POKER!!!!" << std::endl;
		poker = true;
	}	
//mirem si potser un trio
	if(nolligades==2)
	{
		trio = true;

	}	
//mirem que passa quan hi ha nomes una parella ( la mes alta) a la hand // MIREM ESCALES ON TENS 5 CARTES Q FAN ESCALA I UNA PARELLA 

	if(nolligades ==3)
	{
		
		int cartaAltaEscala;
		int cartadescartada;
		int N;
		int numeroderepetides;
		//std::vector <int> cartesnopar;
		int  cartesnopar[6];
		int indexnopar=0;
        
		for(int i=0;i<7;i++)
		{
			if(nrepetides[i]==2)numeroderepetides++;
		}
		if(numeroderepetides==2)
		{
			N=6;
			indexnopar=0;
		}
		if(numeroderepetides==4)
		{
			N=5;
			indexnopar=1;
			
		}for(int i=0;i<N+1;i++)
		{
			if(i!=N)
			{
				if(num(cartes[i])!=num(cartes[i+1]))
				{
					cartesnopar[indexnopar]=cartes[i];
					indexnopar++;
				}
			}
			else	cartesnopar[indexnopar]=cartes[i];
		}

		if(debug)for(int i=0;i<7;i++) std::cout <<"cartesnopar: "<< num(cartesnopar[i])<<std::endl;
	  //. si ([i] + 4) % cantidad_cartas == [ (i+4) % tamaño_array ]
          //. devolver verdadero
		
		int ihandesc=0;
		int cartabaixaesc;
		int indexescalacartabaixa;
		int indexas;
		int palguardat;

		//busquem asos
		for(int i=0;i<7;i++)
		{
			if(num(cartes[i])==14)
			{
				as = true;
				indexas = i;
			}
		}
		if(debug)if(as==true)std::cout<<"as trobat!!!"<<std::endl;
		
		for(int i=0;i<N;i++)
		{
			if(num(cartesnopar[i])+4 == num(cartesnopar[(i+4)%N]))
			{
				escala=true;
				cartabaixaesc=cartesnopar[i];
				indexescalacartabaixa = i;
			} 
		}
		if(escala)as=false;

		if(!escala and as)
		{

			//substituim els asos per uns
			for(int i=0;i<N;i++)
			{
				if(num(cartesnopar[i])==14)
				{
					palguardat = pal(cartesnopar[i]);
					cartesnopar[i]=cartesnopar[i]-13*(palguardat+1);	
				}
			}

			//tornem a ordenar el vector
			for (int i=0;i<=N;i++)
			{
				for (int j=i+1;j<N;j++)
				{
					if (num(cartesnopar[i])>num(cartesnopar[j]))
					{
						aux=cartesnopar[i];
						cartesnopar[i]=cartesnopar[j];
						cartesnopar[j]=aux;
					}
				}
			}
			//tornem a mirar si hi ha escala

			for(int i=0;i<N;i++)
			{
				if(num(cartesnopar[i])+4 == num(cartesnopar[(i+4)%N]))
				{
					escala=true;
					cartabaixaesc=cartesnopar[i];
					indexescalacartabaixa = i;
				} 
			}
		}
		if(escala)hand[0]= cartabaixaesc;
		if(escala and !as)
		{
			hand[0]= cartabaixaesc;
			hand[1]= cartesnopar[indexescalacartabaixa+1];
			hand[2]= cartesnopar[indexescalacartabaixa+2];
			hand[3]= cartesnopar[indexescalacartabaixa+3];
			hand[4]= cartesnopar[indexescalacartabaixa+4];
		}
		//restaurem els asos		
		if(escala and as)
		{
			//if(num(hand[0])==14)
			hand[0]= cartabaixaesc+13*(palguardat+1);
			//else hand[0]= cartabaixaesc;	
			hand[1]= cartesnopar[indexescalacartabaixa+1];
			hand[2]= cartesnopar[indexescalacartabaixa+2];
			hand[3]= cartesnopar[indexescalacartabaixa+3];
			hand[4]= cartesnopar[indexescalacartabaixa+4];
		}
	


		
		if(!escala)parella = true;
		if(escala)std::cout<<"escala"<<std::endl;

		if(!escala and parella)
		{
			int indexcolor=0;
			int valorpal;
			for(int i=0;i<7;i++)
			{
				for(int j=0;j<7;j++)
				{
					if(pal(cartes[i])==pal(cartes[j]))
					{
						indexcolor++;
						if(indexcolor==5)
						{
							color=true;
							valorpal = pal(cartes[i]);
						}
					} 			
				}
			indexcolor=0;
			}
			if(color)
			{
				std::cout<<"color!"<<std::endl;
				indexcolor = 0;
				for(int i=0;i<7;i++)
				{
					if(pal(cartes[6-i])==valorpal and indexcolor <5)
					{
						hand[4-indexcolor]=cartes[6-i];
						indexcolor++;
					}
				}
			}	
			//for(int i=0;i<7;i++) std::cout <<"cartes: "<< num(cartes[i])<<std::endl;
			//std::cout <<"valor pal: "<< valorpal <<std::endl;
			if(color)
			{
				parella=false;
				
			}
		}
	}

//escala quan les 7 son diferents--------------------------------------------------
	
	if(nolligades==4)
	{
		as = false;
		int ihandesc=0;
		int cartabaixaesc;
		int indexescalacartabaixa;
		int palguardat;
		int indexas;
		//BUSQUEM ASOS	
		for(int i=0;i<7;i++)
		{
			//std::cout<<"numcarta "<<num(cartes[i])<<std::endl;
			if(num(cartes[i])==14)
			{
				as =  true;
				indexas = i;
				palguardat = pal(cartes[i]);
			}
		}

		//if(debug)if(as==true)std::cout<<"as trobat!!!aaaaaarg"<<std::endl;
		//std::cout<<"numcarta "<<num(cartes[i])<<std::endl;
		//std::cout<<"pos as: "<<indexas<<std::endl;
		//std::cout<<"pal: "<<palguardat<<std::endl;

		for(int i=0;i<7;i++)
		{
			if(num(cartes[i])+4 == num(cartes[(i+4)%7]))
			{
				escala=true;
				parella=false;
				cartabaixaesc=cartes[i];
				indexescalacartabaixa = i;
			} 
		}
		if(escala)as=false;
		if(!escala)
		{

			//substituim els asos per uns
			for(int i=0;i<7;i++)
			{
				if(num(cartes[i])==14)
				{
					palguardat = pal(cartes[i]);
					cartes[i]=cartes[i]-13*(palguardat+1);	
				}
			}

			//tornem a ordenar el vector
			for (int i=0;i<=7;i++)
			{
				for (int j=i+1;j<7;j++)
				{
					if (num(cartes[i])>num(cartes[j]))
					{
						aux=cartes[i];
						cartes[i]=cartes[j];
						cartes[j]=aux;
					}
				}
			}
			//if(debug)for(int i=0;i<7;i++)std::cout<< num(cartes[i]) <<std::endl;
			//tornem a mirar si hi ha escala

			for(int i=0;i<7;i++)
			{
				if(num(cartes[i])+4 == num(cartes[(i+4)%7]))
				{
					escala=true;
					parella=false;
					cartabaixaesc=cartes[i];
					indexescalacartabaixa = i;
				} 
			}
		}
		for(int i=0;i<7;i++)
		{
			if(num(cartes[i])==1)
			{
				cartes[i]=cartes[i]+(13*(palguardat+1));	
			}
		}
		if(escala)hand[0]= cartabaixaesc;
	
		if(escala and !as and !parella)
		{
			hand[0]= cartabaixaesc;
			hand[1]= cartes[indexescalacartabaixa+1];
			hand[2]= cartes[indexescalacartabaixa+2];
			hand[3]= cartes[indexescalacartabaixa+3];
			hand[4]= cartes[indexescalacartabaixa+4];
		}
		if(escala and as and !parella)
		{
			//std::cout<<hand[0]<<std::endl;
			//std::cout<<pal(hand[0])<<std::endl;
			//if(num(hand[0])==14)
			hand[0]= cartabaixaesc+13*(palguardat+1);
			//else hand[0]= cartabaixaesc;	
			hand[1]= cartes[indexescalacartabaixa+1];
			hand[2]= cartes[indexescalacartabaixa+2];
			hand[3]= cartes[indexescalacartabaixa+3];
			hand[4]= cartes[indexescalacartabaixa+4];
			//std::cout<<hand[0]<<std::endl;
		}
		if(escala)std::cout<<"escala"<<std::endl;	
		//if(debug)std::cout<<"pal de l'as trobat: "<<pal(hand[0])<<std::endl;	
		//if(debug)for(int i=0;i<7;i++)std::cout<< num(cartes[i]) <<std::endl;
		//reparem cartes

			

		//color
		int indexcolor=0;
		int valorpal;
		if(!escala)
		{
			for(int i=0;i<7;i++)
			{
				for(int j=0;j<7;j++)
				{
					if(pal(cartes[i])==pal(cartes[j]))
					{
						indexcolor++;
						valorpal = pal(cartes[i]);
						if(indexcolor==5)color=true;
					} 			
				}
			indexcolor=0;
			}
			if(color)
			{
				std::cout<<"color!"<<std::endl;
				indexcolor = 0;
				for(int i=0;i<7;i++)
				{
					if(pal(cartes[6-i])==valorpal and indexcolor <5)
					{
						hand[4-indexcolor]=cartes[6-i];
						indexcolor++;
					}
				}
			}	
		}	
	}


	
//PARELLA-DOBLEPARELLA---------------------------------------------------------------

	int numparellamesalta = 0;
	int ihand=2;
	int index1=0;
	int index2=0;
	int cartaAltaFinalDobleParella = 0;
	//mirem si hi ha alguna altre parella o nomes es una parella sola. 
	//for(int i=0;i<7;i++)std::cout<<num(cartes[i])<<std::endl;

	if(parella and !escala and !color and !escala_color)
	{
		for(int i=0;i<7;i++)
		{
			if(nrepetides[i]==2 and num(cartes[i])!=num(hand[0]) and num(cartes[i])>=numparellamesalta)
			{
				dobleparella = true;
				numparellamesalta = num(cartes[i]);
			}
		}
	}	

	if(dobleparella and parella  and !escala and !color and !escala_color)
	{
		std::cout <<"Doble Parella"<<std::endl;
		for(int i=0;i<7;i++)
		{
				if(num(cartes[i])==numparellamesalta )
				{
					hand[ihand] = cartes[i];
					ihand++;
				}
		}
		for(int i=0;i<7;i++)
		{
			if(num(cartes[i])>num(cartaAltaFinalDobleParella) and num(hand[0])!=num(cartes[i]) and num(hand[2])!=num(cartes[i]))
				cartaAltaFinalDobleParella = cartes[i];
		}
		hand[4]=cartaAltaFinalDobleParella;
	
	}
	if(!dobleparella and parella  and !escala and !color and !escala_color)
	{
		while(index2 !=6)
		{
			if(num(cartes[6-index2])!=num(hand[0]) and index1 < 3)
			{
				hand[4-index1]=cartes[6-index2];
				index1++;
			}
			index2++;
		}
		std::cout <<"Parella"<<std::endl;
	}

//end PARELLA-DOBLEPARELLA-----------------------------------------------------------
//TRIO-FULL--------------------------------------------------------------------------
	if(trio and !escala and !color and !escala_color)
	{
		for(int i=0;i<7;i++)
		{
			if(nrepetides[i]>=2 and num(hand[0])!= num(cartes[i]) or nrepetides[i]==3 and num(cartes[b])!=num(cartes[i]))
			{
				full = true;
			}
		}
		if(full)std::cout<<"FULLHOUSE!!"<<std::endl;
		if(!full)std::cout<<"TRIO"<<std::endl;
	}
	
	int hightfull_1 = 0; 
	int hightfull_2 = 0; 

	if(!full and trio and !escala and !color and !escala_color)
	{
		for(int i =0; i<7;i++)
		{
			if(num(cartes[i]) > num(hightfull_1) and  num(hand[0])!= num(cartes[i]))
			{
				hightfull_1=cartes[i];
			}
		}
		hand[3]=hightfull_1;
		for(int i =0; i<7;i++)
		{
			if(num(cartes[i]) > num(hightfull_2) and  nrepetides[i]!=nrepetides[b] and num(cartes[i]) != num(hightfull_1))
			{
				hightfull_2=cartes[i];
			}
		}
		hand[4]=hightfull_2;
	}
	int numero_parella_alta = 0;
	int parellafull1=0;
	int parellafull2=0;
	int indexHand=3;
	if(full)
	{
		//buscar parella mes gran entre les 4 cartes (7-3)
		for(int i =0;i<7;i++)
		{
			if(nrepetides[i]>1 and num(hand[0])!= num(cartes[i]) and num(cartes[i]) > num(numero_parella_alta))
			{
				numero_parella_alta=cartes[i];
			}
		}
		//posar tots els que siguin numero_parella_alta als llocs que falten de hand 
		for(int i =0;i<7;i++)
		{
			if(num(cartes[i])==num(numero_parella_alta))
			{
				hand[indexHand]=cartes[i];
				indexHand=4;
			}
		}

	}
	
//endTRIO-FULL-----------------------------------------------------------------------
//POKER------------------------------------------------------------------------------
	//mirem si hi ha poker i retornem el poker amb la carta mes alta 
	int hightpoker = 0; 
	if(poker and !escala and !color and !escala_color)
	{
		for(int i =0;i<7;i++)
		{	
			
			if(num(cartes[i]) > num(hightpoker) and  nrepetides[i]!=nrepetides[b])
			{
				hightpoker=cartes[i];
			}
		}
	hand[4]=hightpoker;
	}

//endPOKER----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////
	//std::cout<<hightpoker<<std::endl;
	
	//es un carta alta?
	

	//parella?

		//doble Parella??

	//trio?ad

		//full?

	//color?
	//escala?

		//escala color
//////////////////////////////////////////////////////////////////////////////////////////////
    
	if(!full and !escala and !poker and !parella and !dobleparella and !trio and !color and !escala_color)
	{
		int indexcartaalta=1;
		carta_alta= true;
		std::cout<<"Carta alta!"<<std::endl;
		for(int i=0;i<7;i++)
		{
			if(num(cartes[6-i])!=num(hand[0]) and indexcartaalta<5)
			{
				hand[indexcartaalta]=cartes[6-i];
				indexcartaalta++;
			}		
		}
	}




	if(pal(hand[0])==pal(hand[1]) and pal(hand[1])==pal(hand[2])and pal(hand[2])==pal(hand[3])and pal(hand[3])==pal(hand[4]))color=true;
	if(color and escala)
	{
		std::cout<<"escala de color!"<<std::endl;
		escala_color = true;
		color = false;
		escala = false;
	}
	//hand
//	if(debug)

	int final[6];

	if(carta_alta)*puntuacio=1;
	if(parella and !dobleparella and !trio and !full)*puntuacio=2;
	if(dobleparella)*puntuacio=3;
	if(trio and !full)*puntuacio=4;
	if(escala and !escala_color)*puntuacio=5;
	if(color)*puntuacio=6;
	if(full)*puntuacio=7;
	if(poker)*puntuacio=8;
	if(escala_color)*puntuacio=9;
/*
	for(int i=0;i<7;i++)
	{
		if(i!=6)final[i]=hand[i];
		else final[i]=pfinal;
		
	}*/

/*
	bool carta_alta = false;
	bool parella = false;
	bool dobleparella = false;
	bool trio = false;
	bool full = false;
	bool color = false;
	bool escala = false;
	bool escala_color = false;
	bool poker = false;
*/
}

int calcularguanyador(int cartes1[7],int cartes2[7],int cartes3[7], int cartes4[7], int *guanyadors)
{
	int empat=false;
	int jugadaempat;
	int iguany;
	
	bool noempat = true;
	int handcompare1[5];
	int handcompare2[5];
    
    
	int handres1[5];
	int handres2[5];
	int handres3[5];
	int handres4[5];
    
    
	int puntuacio1;
	int puntuacio2;
	int puntuacio3;
	int puntuacio4;
    
	int pguanyadora = 0;
    
	std::vector <int> puntuacions;
    
	int hand[5] = {-10,-10,-10,-10,-10};
	int puntuacio;
    
    //comencem a mirar les 4 mans.
    
    //ma1
    if(cartes1[0]!=-1){
        evaluateHand(cartes1,hand,&puntuacio);
        for(int i=0;i<5;i++)handres1[i]=hand[i];
        for(int i=0;i<5;i++) std::cout <<"Hand: "<< num(handres1[i])<< " de " << pal(handres1[i]) << std::endl;
        puntuacio1=puntuacio;
        puntuacions.push_back(puntuacio1);
        //std::cout << "Puntuacio de la hand final: "<<puntuacio1<<std::endl;
        for(int i=0;i<5;i++)hand[i]=-10;
    }
    if(cartes1[0]==-1)	puntuacions.push_back(0);
    
    //ma2
    if(cartes2[0]!=-1){
        evaluateHand(cartes2,hand,&puntuacio);
        for(int i=0;i<5;i++)handres2[i]=hand[i];
        for(int i=0;i<5;i++) std::cout <<"Hand: "<< num(handres2[i])<< " de " << pal(handres2[i]) << std::endl;
        puntuacio2=puntuacio;
        puntuacions.push_back(puntuacio2);
        //std::cout << "Puntuacio de la hand final: "<<puntuacio2<<std::endl;
        for(int i=0;i<5;i++)hand[i]=-10;
    }
    if(cartes2[0]==-1)	puntuacions.push_back(0);
    
    
    //ma3
    if(cartes3[0]!=-1){
        evaluateHand(cartes3,hand,&puntuacio);
        for(int i=0;i<5;i++)handres3[i]=hand[i];
        for(int i=0;i<5;i++) std::cout <<"Hand: "<< num(handres3[i])<< " de " << pal(handres3[i]) << std::endl;
        puntuacio3=puntuacio;
        puntuacions.push_back(puntuacio3);
        //std::cout << "Puntuacio de la hand final: "<<puntuacio3<<std::endl;
        for(int i=0;i<5;i++)hand[i]=-10;
    }
    if(cartes3[0]==-1)	puntuacions.push_back(0);
    
    
    //ma4
    if(cartes4[0]!=-1){
        evaluateHand(cartes4,hand,&puntuacio);
        for(int i=0;i<5;i++)handres4[i]=hand[i];
        for(int i=0;i<5;i++) std::cout <<"Hand: "<< num(handres4[i])<< " de " << pal(handres4[i]) << std::endl;
        puntuacio4=puntuacio;
        puntuacions.push_back(puntuacio4);
        //std::cout << "Puntuacio de la hand final: "<<puntuacio4<<std::endl;
        for(int i=0;i<5;i++)hand[i]=-10;
    }
    if(cartes4[0]==-1)	puntuacions.push_back(0);
    
    
	std::cout<<"size puntuacions: "<<puntuacions.size()<<std::endl;
    
	//for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
    
	for(int i =0;i <puntuacions.size();i++)
	{
		noempat = true;
        
		if(i==0)
		{
			for(int i =0;i<5;i++)handcompare1[i]=handres1[i];
		}
		if(i==1)
		{
			for(int j =0;j<5;j++)handcompare1[j]=handres2[j];
		}
		if(i==2)
		{
			for(int j =0;j<5;j++)handcompare1[j]=handres3[j];
		}
		if(i==3)
		{
			for(int j =0;j<5;j++)handcompare1[j]=handres4[j];
		}
        
        
		//std::cout<<"handcompare1[0]: "<< num(handcompare1[0]) <<std::endl;
		//std::cout<<"handcompare2[0]: "<< num(handcompare2[0]) <<std::endl;
		if(puntuacions[i]>pguanyadora)
		{
			pguanyadora = puntuacions[i];
			iguany = i;
            
			empat=false;
            
			if(i==0)
			{
				for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
			}			
			if(i==1)
			{
				for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
			}
			if(i==2)
			{
				for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
			}
			if(i==3)
			{
				for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
			}
			noempat =false;
            
		}
		
		else if(puntuacions[i]==pguanyadora and pguanyadora!=0)
		{
            
			if(pguanyadora==1)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
                    
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
					noempat =false;
				}
				if(num(handcompare1[0])==num(handcompare2[0]))
				{
					if(num(handcompare1[1])>num(handcompare2[1]))
					{
						pguanyadora = puntuacions[i];
						iguany = i;
                        
						empat=false;
						if(i==0)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
						}			
						if(i==1)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
						}
						if(i==2)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
						}
						if(i==3)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
						}
						noempat =false;
					}
					if(num(handcompare1[1])==num(handcompare2[1]))
					{
						if(num(handcompare1[2])>num(handcompare2[2]))
						{
							pguanyadora = puntuacions[i];
							iguany = i;
                            
							empat=false;
							if(i==0)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
							}			
							if(i==1)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
							}
							if(i==2)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
							}
							if(i==3)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
							}
						}
						if(num(handcompare1[2])==num(handcompare2[2]))
						{
							if(num(handcompare1[3])>num(handcompare2[3]))
							{
								pguanyadora = puntuacions[i];
								iguany = i;
                                
								empat=false;
								if(i==0)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
								}			
								if(i==1)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
								}
								if(i==2)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
								}
								if(i==3)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
								}
							}
							if(num(handcompare1[3])==num(handcompare2[3]))
							{
								if(num(handcompare1[4])>num(handcompare2[4]))
								{
									pguanyadora = puntuacions[i];
									iguany = i;
									std::cout<<"i guany : "<<iguany<<std::endl;
									empat=false;
									if(i==0)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
									}			
									if(i==1)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
									}
									if(i==2)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
									}
									if(i==3)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
									}
								}
								if(num(handcompare1[4])==num(handcompare2[4]))
								{
									empat = true;
									pguanyadora = puntuacions[i];
									jugadaempat = pguanyadora;
                                    
									guanyadors[i-1]=1;
									guanyadors[i]=1;
								}	
							}	
						}
					}
				}
			}
			if(pguanyadora==2)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
				}
				if(num(handcompare1[0])==num(handcompare2[0]))
				{
					if(num(handcompare1[4])>num(handcompare2[4]))
					{
						pguanyadora = puntuacions[i];
						iguany = i;
                        
						empat=false;
						if(i==0)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
						}			
						if(i==1)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
						}
						if(i==2)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
						}
						if(i==3)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
						}
					}
					if(num(handcompare1[4])==num(handcompare2[4]))
					{
						if(num(handcompare1[3])>num(handcompare2[3]))
						{
							pguanyadora = puntuacions[i];
							iguany = i;
                            
							empat=false;							
							if(i==0)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
							}			
							if(i==1)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
							}
							if(i==2)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
							}
							if(i==3)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
							}
						}
						if(num(handcompare1[3])==num(handcompare2[3]))
						{
							if(num(handcompare1[2])>num(handcompare2[2]))
							{
								pguanyadora = puntuacions[i];
								iguany = i;
                                
								empat=false;
								if(i==0)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
								}			
								if(i==1)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
								}
								if(i==2)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
								}
								if(i==3)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
								}
							}
							if(num(handcompare1[2])==num(handcompare2[2]))
							{
								empat = true;
								pguanyadora = puntuacions[i];
								jugadaempat = pguanyadora;
								guanyadors[i-1]=1;
								guanyadors[i]=1;
							}	
						}					
					}
				}
			}
			if(pguanyadora==3)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
				}
				if(num(handcompare1[0])==num(handcompare2[0]) and noempat)
				{
					if(num(handcompare1[2])>num(handcompare2[2]))
					{
						pguanyadora = puntuacions[i];
						iguany = i;
                        
						empat=false;
						if(i==0)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
						}			
						if(i==1)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
						}
						if(i==2)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
						}
						if(i==3)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
						}
					}
					if(num(handcompare1[2])==num(handcompare2[2]) and noempat)
					{
						if(num(handcompare1[4])>num(handcompare2[4]))
						{
							pguanyadora = puntuacions[i];
							iguany = i;
                            
							empat=false;							
							if(i==0)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
							}			
							if(i==1)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
							}
							if(i==2)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
							}
							if(i==3)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
							}
						}
						if(num(handcompare1[4])==num(handcompare2[4]))
						{
							empat = true;
							pguanyadora = puntuacions[i];
							jugadaempat = pguanyadora;
							guanyadors[i-1]=1;
							guanyadors[i]=1;
						}					
					}
				}
			}
			if(pguanyadora==4)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
                    
				}
				if(num(handcompare1[0])==num(handcompare2[0]))
				{
                    //std::cout<<"compare1: "<<num(handcompare1[0])<<num(handcompare2[0])<<" compare2"<<std::endl; 
					if(num(handcompare1[3])>num(handcompare2[3]))
					{
						pguanyadora = puntuacions[i];
						iguany = i;
                        
						empat=false;
						if(i==0)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
						}			
						if(i==1)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
						}
						if(i==2)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
						}
						if(i==3)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
						}
                        
					}
					if(num(handcompare1[3])==num(handcompare2[3]))
					{
						//std::cout<<"compare1: "<<num(handcompare1[3])<<num(handcompare2[3])<<" compare2"<<std::endl; 
						if(num(handcompare1[4])>num(handcompare2[4]))
						{
							pguanyadora = puntuacions[i];
							iguany = i;
                            
							empat=false;							
							if(i==0)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
							}			
							if(i==1)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
							}
							if(i==2)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
							}
							if(i==3)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
							}
                            
						}
                        
						if(num(handcompare1[4])==num(handcompare2[4]))
						{
							//std::cout<<"compare1: "<<num(handcompare1[4])<<num(handcompare2[4])<<" compare2"<<std::endl; 
							empat = true;
							pguanyadora = puntuacions[i];
							jugadaempat = pguanyadora;
							guanyadors[i-1]=1;
							guanyadors[i]=1;
						}		
					}
				}
			}
			if(pguanyadora==5)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
				}
				if(num(handcompare1[0])==num(handcompare2[0]))
				{
					empat = true;
					pguanyadora = puntuacions[i];
					jugadaempat = pguanyadora;
					guanyadors[i-1]=1;
					guanyadors[i]=1;
				}
			}
			if(pguanyadora==6)
			{
				if(num(handcompare1[4])>num(handcompare2[4]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
                    
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
				}
				if(num(handcompare1[4])==num(handcompare2[4]))
				{
					if(num(handcompare1[1])>num(handcompare2[1]))
					{
						pguanyadora = puntuacions[i];
						iguany = i;
                        
						empat=false;
						if(i==0)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
						}			
						if(i==1)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
						}
						if(i==2)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
						}
						if(i==3)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
						}
					}
					if(num(handcompare1[3])==num(handcompare2[3]))
					{
						if(num(handcompare1[2])>num(handcompare2[2]))
						{
							pguanyadora = puntuacions[i];
							iguany = i;
                            
							empat=false;
							if(i==0)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
							}			
							if(i==1)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
							}
							if(i==2)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
							}
							if(i==3)
							{
								for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
							}
						}
						if(num(handcompare1[2])==num(handcompare2[2]))
						{
							if(num(handcompare1[1])>num(handcompare2[1]))
							{
								pguanyadora = puntuacions[i];
								iguany = i;
                                
								empat=false;
								if(i==0)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
								}			
								if(i==1)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
								}
								if(i==2)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
								}
								if(i==3)
								{
									for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
								}
							}
							if(num(handcompare1[1])==num(handcompare2[1]))
							{
								if(num(handcompare1[0])>num(handcompare2[0]))
								{
									pguanyadora = puntuacions[i];
									iguany = i;
                                    
									empat=false;
									if(i==0)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
									}			
									if(i==1)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
									}
									if(i==2)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
									}
									if(i==3)
									{
										for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
									}
								}
								if(num(handcompare1[0])==num(handcompare2[0]))
								{
									empat = true;
									pguanyadora = puntuacions[i];
									jugadaempat = pguanyadora;
									guanyadors[i-1]=1;
									guanyadors[i]=1;
								}	
							}	
						}
					}
				}
			}
			if(pguanyadora==7)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
				}
				if(num(handcompare1[0])==num(handcompare2[0]))
				{
					if(num(handcompare1[3])>num(handcompare2[3]))
					{
						pguanyadora = puntuacions[i];
						iguany = i;
                        
						empat=false;
						if(i==0)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
						}			
						if(i==1)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
						}
						if(i==2)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
						}
						if(i==3)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
						}
					}
					if(num(handcompare1[3])==num(handcompare2[3]))
					{
						empat = true;
						pguanyadora = puntuacions[i];
						jugadaempat = pguanyadora;
						guanyadors[i-1]=1;
						guanyadors[i]=1;
					}
				}
			}
			if(pguanyadora==8)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
				}
				if(num(handcompare1[0])==num(handcompare2[0]))
				{
					if(num(handcompare1[4])>num(handcompare2[4]))
					{
						pguanyadora = puntuacions[i];
						iguany = i;
                        
						empat=false;
						if(i==0)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
						}			
						if(i==1)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
						}
						if(i==2)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
						}
						if(i==3)
						{
							for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
						}
					}
					if(num(handcompare1[4])==num(handcompare2[4]))
					{
						empat = true;
						pguanyadora = puntuacions[i];
						jugadaempat = pguanyadora;
						guanyadors[i-1]=1;
						guanyadors[i]=1;
					}
				}
			}
			if(pguanyadora==9)
			{
				if(num(handcompare1[0])>num(handcompare2[0]))
				{
					pguanyadora = puntuacions[i];
					iguany = i;
                    
					empat=false;
					if(i==0)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres1[j];
					}			
					if(i==1)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres2[j];
					}
					if(i==2)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres3[j];
					}
					if(i==3)
					{
						for(int j =0;j<5;j++)handcompare2[j]=handres4[j];
					}
				}
				if(num(handcompare1[0])==num(handcompare2[0]))
				{
					empat = true;
					pguanyadora = puntuacions[i];
					jugadaempat = pguanyadora;
					guanyadors[i-1]=1;
					guanyadors[i-1]=1;
					guanyadors[i]=1;
				}
			}
			
		}
        
	}
    
	if(empat)std::cout<<"jugada guanyadora : "<< pguanyadora<<std::endl;
	if(empat)std::cout<<"EMPAT: "<< pguanyadora<<std::endl;
	if(empat)return -1;
        return iguany;
}