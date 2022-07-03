//	CHOINKA TOMASZA
//	1.0.0
//	by Tomasz Golaszewski 
//	2014

#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include <stdlib.h>
#include <time.h>

int **NowaMacierz(int n, int m) 
{
	int **M;
	M=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;++i)
	{
		M[i]=(int*)malloc(m*sizeof(int));
		for(int j=0;j<m;++j)
		{
			M[i][j]=0;
		}
	}
	return M;
}

double *NowyWektor(int n) 
{
	double *M;
	M=(double*)malloc(n*sizeof(double));
	for(int i=0;i<n;++i)
	{
		M[i]=0;
	}
	return M;
}

double Dlugosc1(int n, int **M)
{
	return(sqrt(1.*((M[n][0]-M[n][3])*(M[n][0]-M[n][3])+(M[n][1]-M[n][4])*(M[n][1]-M[n][4])+(M[n][2]-M[n][5])*(M[n][2]-M[n][5]))));
}

double Dlugosc2(int x, int y, int z)
{
	return(sqrt(1.*(x*x+y*y+z*z)));
}

void RysujChoinke(int opcja, int n, int **M,int transx, int transy, int transz, int skala)
{
	double a=0.7243116396;//=41'5'
	double b=0.1221730476;//=7'
	double c=0.7853981634;//=45'
	double d=0.5235987756;//=30'

//Rysowanie Choinki
	for (int i=0;i<n;++i)
	{
//Rzut na XY
		if(opcja==1)
		{
			line(transx+skala*M[i][0],transy-skala*M[i][1],transx+skala*M[i][3],transy-skala*M[i][4]);
		}
//Rzut na YZ
		if(opcja==2)
		{
			line(transx+skala*M[i][1],transz-skala*M[i][2],transx+skala*M[i][4],transz-skala*M[i][5]);
		}
//Rzut na XZ
		if(opcja==3)
		{
			line(transx+skala*M[i][0],transz-skala*M[i][2],transx+skala*M[i][3],transz-skala*M[i][5]);
		}
//Rzut dimetryczny prostokatny
		if(opcja==4)
		{
			line(transx+skala*(-M[i][0]*cos(a)/2.+M[i][1]*cos(b)),transz+skala*(M[i][0]*sin(a)/2.+M[i][1]*sin(b)-M[i][2]),transx+skala*(-M[i][3]*cos(a)/2.+M[i][4]*cos(b)),transz+skala*(M[i][3]*sin(a)/2.+M[i][4]*sin(b)-M[i][5]));
		}
//Rzut dimetryczny ukosny
		if(opcja==5)
		{
			line(transx+skala*(-M[i][0]*cos(c)/2.+M[i][1]),transz+skala*(M[i][0]*sin(c)/2.-M[i][2]),transx+skala*(-M[i][3]*cos(c)/2+M[i][4]),transz+skala*(M[i][3]*sin(c)/2.-M[i][5]));
		}
//Rzut izometryczny
		if(opcja==6)
		{
			line(transx+skala*(-M[i][0]*cos(d)+M[i][1]*cos(d)),transz+skala*(M[i][0]*sin(d)+M[i][1]*sin(d)-M[i][2]),transx+skala*(-M[i][3]*cos(d)+M[i][4]*cos(d)),transz+skala*(M[i][3]*sin(d)+M[i][4]*sin(d)-M[i][5]));
		}
	}
}

void main()
{
	printf("\"CHOINKA TOMASZA\"\n1.0.0\nby Tomasz Golaszewski\n2014\n\n");

//Parametry drzewka
	int szerokosc=1000;
	int wysokosc=700;
	int liczbaplaszczyzn=11;
	int liczbapieter=7;
	int wysokoscpnia=300;
	int wysokoscchoinki=450;
	int promienpnia=20;
	int minzawieszenie=110;
	int maxpromien=200;
	int zwis=50;
	int roznicawysokosci=(wysokoscchoinki-minzawieszenie)/liczbapieter;
	int odlegloscigielek=7;
	int liczbaigielek=5;
	int dlugoscigielek=10;
	int zwisigielek=7;

	printf("\nWprowadz szerokosc okna (OPTYMALNIE 1000, MINIMALNIE 500):\t");
	scanf("%d",&szerokosc);
	while(szerokosc<500)
	{
		printf("=> MINIMALNIE 500 <= :\t");
		scanf("%d",&szerokosc);
	}
	printf("\nWprowadz wysokosc okna (OPTYMALNIE 700, MINIMALNIE 550):\t");
	scanf("%d",&wysokosc);
	while(wysokosc<550)
	{
		printf("=> MINIMALNIE 550 <= :\t");
		scanf("%d",&wysokosc);
	}

//Opcje wyswietlania
	int opcja=4;
	int skala=1;
	int transx=szerokosc/2;
	int transz=(wysokosc+wysokoscchoinki)/2-25;
	int transy=wysokosc/2;

	printf("\n1 - Rzut na XY\n2 - Rzut na YZ\n3 - Rzut na XZ\n4 - Rzut dimetryczny prostokatny <- TEN OSOBISCIE POLECAM\n5 - Rzut dimetryczny ukosny\n6 - Rzut izometryczny\nWprowadz nr rzutu choinki:\t");
	scanf("%d",&opcja);
	while((opcja<1)||(opcja>6))
	{
		printf("=> 1,2,3,4,5 lub 6, ale NAJLEPIEJ 4 <= :\t");
		scanf("%d",&opcja);
	}

//Pomocnicze zmienne
	double pi=4.*atan(1.);
	double fi;
	double psi;
	double alfa;
	double beta;
	int lastx;
	int lasty;
	int lastz;
	double *R=NowyWektor(3);//globalny wektor przesuniecia kepki
	double *MR=NowyWektor(3);//wektor przesuniecia kepki po galezi
	double *GR=NowyWektor(3);//wektor galezi
	int l;//dlugosc1
	int lmr;//dlugosc2
	int numerkepki=1;
	int aktualnypromien;
	int numergalazki=1;
	int numerigielki=0;

//Inicjalizacja liczb losowych - kazda choinka bedzie niepowtarzalna :)
    srand(time(NULL));

//Tworzenie Macierzy Skladowych Choinki
	int nc=liczbaplaszczyzn*liczbapieter+1;
	int mc=6;
	int **C=NowaMacierz(nc,mc);

//Tworzenie Macierzy Skladowych Pnia (Oczywiscie pien jest w warunkach normalnych skladowa choinki, nazwalem to tak tylko dla uproszczenia)
	int np=2*liczbaplaszczyzn;
	int mp=6;
	int **P=NowaMacierz(np,mp);

//Tworzwenie Macierzy Igielek
	int ni=7000;
	int mi=6;
	int **I=NowaMacierz(ni,mi);

//Tworzenie Pnia
	lastx=promienpnia;
	lasty=0;
	for(int i=0;i<liczbaplaszczyzn;i++)
	{
		P[i+liczbaplaszczyzn][0]=P[i][0]=lastx;
		P[i+liczbaplaszczyzn][1]=P[i][1]=lasty;
		lastx=P[i][3]=promienpnia*cos(2.*pi*(i+1)/liczbaplaszczyzn);
		lasty=P[i][4]=promienpnia*sin(2.*pi*(i+1)/liczbaplaszczyzn);
		P[i+liczbaplaszczyzn][5]=wysokoscpnia;
	}

//Tworzenie Czubka
	C[0][2]=wysokoscpnia;
	C[0][5]=wysokoscchoinki;

	l=C[0][5]-C[0][2];
	while(1)
	{
		lmr=numerkepki*odlegloscigielek;
		if(l<lmr) break;	
		lmr=lmr+wysokoscpnia;
		fi=2.*pi*rand()/(RAND_MAX*liczbaigielek);
		for(int k=0;k<liczbaigielek;k++)
		{
			I[numerigielki][2]=lmr;			
			I[numerigielki][3]=dlugoscigielek*cos(2.*pi*(k+1)/liczbaigielek+fi);
			I[numerigielki][4]=dlugoscigielek*sin(2.*pi*(k+1)/liczbaigielek+fi);
			I[numerigielki][5]=lmr+zwisigielek;
			numerigielki++;
		}
		numerkepki++;
	}
	numerkepki=1;

//Tworzenie Choinki
	for(int j=0;j<liczbapieter;j++)
	{
		aktualnypromien=maxpromien-maxpromien*j/liczbapieter;
		fi=2.*pi*rand()/(RAND_MAX*liczbaplaszczyzn);
		beta=atan(1.*zwis/aktualnypromien);

		for(int i=0;i<liczbaplaszczyzn;i++)
		{
			alfa=2.*pi*(i+1)/liczbaplaszczyzn+fi;
			C[numergalazki][2]=minzawieszenie+j*roznicawysokosci;
			C[numergalazki][3]=aktualnypromien*cos(alfa);
			C[numergalazki][4]=aktualnypromien*sin(alfa);
			C[numergalazki][5]=minzawieszenie-zwis+j*roznicawysokosci;

//Tworzenie Igielek
			l=Dlugosc1(numergalazki,C);
			for(int k=0;k<3;k++)
			{
				GR[k]=C[numergalazki][k+3]-C[numergalazki][k];
			}
			while(1)
			{
				psi=2.*pi*rand()/(RAND_MAX*liczbaigielek);

				for(int k=0;k<3;k++)
				{
					MR[k]=numerkepki*odlegloscigielek*GR[k]/l;
				}
				lmr=Dlugosc2(MR[0],MR[1],MR[2]);
				if(l<lmr) break;
				for(int k=0;k<3;k++)
				{	
					R[k]=MR[k]+C[numergalazki][k];
				}
				for(int k=0;k<liczbaigielek;k++)
				{
					lastx=zwisigielek;
					lasty=dlugoscigielek*cos(2.*pi*(k+1)/liczbaigielek+psi);
					lastz=dlugoscigielek*sin(2.*pi*(k+1)/liczbaigielek+psi);
					I[numerigielki][3]=(lastx*cos(beta)+lastz*sin(beta))*cos(alfa)-lasty*sin(alfa);
					I[numerigielki][4]=(lastx*cos(beta)+lastz*sin(beta))*sin(alfa)+lasty*cos(alfa);
					I[numerigielki][5]=lastz*cos(beta)-lastx*sin(beta);
					for(int p=0;p<3;p++)
					{
						I[numerigielki][p]=R[p];
						I[numerigielki][p+3]=I[numerigielki][p+3]+R[p];
					}
					numerigielki++;
				}
				numerkepki++;
			}
			numerkepki=1;
			numergalazki++;
		}
		liczbaplaszczyzn=liczbaplaszczyzn-1;
	}
	//printf("\n\n%d",numerigielki);

//Okno graficzne
	graphics(szerokosc,wysokosc);

//Rysowanie Pnia
	setcolor(0.97);
	RysujChoinke(opcja,np,P,transx,transy,transz,skala);

//Rysowanie Choinki i Igielek
	setcolor(0.5);
	RysujChoinke(opcja,nc,C,transx,transy,transz,skala);
	RysujChoinke(opcja,ni,I,transx,transy,transz,skala);

//Podpis
	setcolor(0);
	line(szerokosc-150,wysokosc-100,szerokosc-100,wysokosc-100);//		-T
	line(szerokosc-125,wysokosc-100,szerokosc-125,wysokosc-50);//		|T
	line(szerokosc-50,wysokosc-88,szerokosc-75,wysokosc-100);//		G\			//
	line(szerokosc-75,wysokosc-100,szerokosc-100,wysokosc-88);//		/G
	line(szerokosc-100,wysokosc-88,szerokosc-100,wysokosc-62);//		|G
	line(szerokosc-100,wysokosc-62,szerokosc-75,wysokosc-50);//		\G
	line(szerokosc-75,wysokosc-50,szerokosc-50,wysokosc-62);//		G/
	line(szerokosc-50,wysokosc-62,szerokosc-50,wysokosc-75);//		G|
	line(szerokosc-50,wysokosc-75,szerokosc-75,wysokosc-75);//		G-

//Czyszczenie
	for(int i=0;i<nc;++i) free(C[i]);
	free(C);
	for(int i=0;i<np;++i) free(P[i]);
	free(P);
	for(int i=0;i<ni;++i) free(I[i]);
	free(I);

//Czekanie
	wait();
}

