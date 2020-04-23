#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <cstring>

#include "nrutil.h"
#include "rk4.h"

using namespace std;
#define m3 3.0			// masa de las 3 particulas
#define m4 4.0
#define m5 5.0

string doubleToString(double a){
  ostringstream temp;
  temp<<a;
  return temp.str();
}

void derivs(double x, double* y, double* dy){
	double d34, d35, d45;						// distancia entre particulas
	d34 = sqrt(pow(y[5] - y[1], 2) + pow(y[6]  - y[2], 2));
	d35 = sqrt(pow(y[9] - y[1], 2) + pow(y[10] - y[2], 2));
	d45 = sqrt(pow(y[9] - y[5], 2) + pow(y[10] - y[6], 2));

	// Calcula aceleracion
	dy[3]  = m4 * (y[5] - y[1])  / pow(d34,3) + m5 * (y[9]  - y[1]) / pow(d35, 3);
	dy[4]  = m4 * (y[6] - y[2])  / pow(d34,3) + m5 * (y[10] - y[2]) / pow(d35, 3);
	dy[1]  = y[3];	
	dy[2]  = y[4];
	dy[7]  = m3 * (y[1] - y[5])  / pow(d34,3) + m5 * (y[9]  - y[5]) / pow(d45, 3);
	dy[8]  = m3 * (y[2] - y[6])  / pow(d34,3) + m5 * (y[10] - y[6]) / pow(d45, 3);
	dy[5]  = y[7];
	dy[6]  = y[8];
	dy[11] = m3 * (y[1] - y[9])  / pow(d35,3) + m4 * (y[5] - y[9])  / pow(d45, 3);
	dy[12] = m3 * (y[2] - y[10]) / pow(d35,3) + m4 * (y[6] - y[10]) / pow(d45, 3);
	dy[9]  = y[11];
	dy[10] = y[12];
}


#include "rk4.c"


int main(int argc, char *argv[]){
  double h;					// intervalo
  if(argc==1){
    h = 0.01;
  } else if(argc ==2){
    h = atof(argv[1]);
  }
	int n = 12;							// Dimension de los vectores
	double t = 0;						// variable independiente (-> t)
	double Ekin, Epot;					// Energia
	double D34, D35, D45;				// distancia entre particulas
	double Dmin = 6;					// Variable de distancia mínima. 6 para la primera consulta (S.U.)
	double D, D1, D2;					// Recuerda las distancias minimas
	double *yvec, *dyvec;				// puntero de vectores 

	yvec = dvector(1, n);				// Vector y
	dyvec = dvector(1, n);				// Vector y'

										// Los valores iniciales para x_i y v_i
	yvec[1]  =  3, yvec[2]  = -1;		// particula m3
	yvec[3]  =  0, yvec[4]  =  0;
	yvec[5]  = -1, yvec[6]  =  2;		// particula m4
	yvec[7]  =  0, yvec[8]  =  0;
	yvec[9]  = -1, yvec[10] = -1;		// particula m5
	yvec[11] =  0, yvec[12] =  0.1;

											// Los valores iniciales para v_i y a_i
	dyvec[1]  =  0, dyvec[2]  = 0;			// particula m3
	dyvec[3]  =  m4 * (yvec[5] - yvec[1]) / 125 + m5 * (yvec[9] - yvec[1]) / 64;
	dyvec[4]  =  m4 * (yvec[6] - yvec[2]) / 125 + m5 * (yvec[10] - yvec[2]) / 64;
	dyvec[5]  =  0, dyvec[6]  = 0;			// particula m4
	dyvec[7]  =  m3 * (yvec[1] - yvec[5]) / 125 + m5 * (yvec[9] - yvec[5]) / 27;
	dyvec[8]  =  m3 * (yvec[2] - yvec[6]) / 125 + m5 * (yvec[10] - yvec[6]) / 27;
	dyvec[9]  =  0, dyvec[10] = 0;			// particula m5
	dyvec[11] =  m3 * (yvec[1] - yvec[9])  / 64 + m4 * (yvec[5] - yvec[9]) / 27;
	dyvec[12] =  m3 * (yvec[2] - yvec[10]) / 64 + m4 * (yvec[6] - yvec[10]) / 27;

  string p3 = "results/particula3_"+doubleToString(h)+".txt";
  string p4 = "results/particula4_"+doubleToString(h)+".txt";
  string p5 = "results/particula5_"+doubleToString(h)+".txt";
  string energia = "results/energia_"+doubleToString(h)+".txt";
  string dmin = "results/Dmin_"+doubleToString(h)+".txt";
  
	ofstream datei1(p3.c_str( ));
	ofstream datei2(p4.c_str( ));
	ofstream datei3(p5.c_str( ));
	ofstream energie(energia.c_str( ));
	ofstream minabstaende(dmin.c_str( ));


	for (int i = 0; i < 4000; i++)
	{
		t = i * h;

		// Calculo de la energia
		D34 = sqrt(pow(yvec[5] - yvec[1], 2) + pow(yvec[6]  - yvec[2], 2));
		D35 = sqrt(pow(yvec[9] - yvec[1], 2) + pow(yvec[10] - yvec[2], 2));
		D45 = sqrt(pow(yvec[9] - yvec[5], 2) + pow(yvec[10] - yvec[6], 2));
		Epot  = -m3 * m4 / D34;
		Epot -=  m3 * m5 / D35;
		Epot -=  m4 * m5 / D45;
		Ekin  = 0.5 * m3 * (yvec[3] * yvec[3] + yvec[4] * yvec[4]);
		Ekin += 0.5 * m4 * (yvec[7] * yvec[7] + yvec[8] * yvec[8]);
		Ekin += 0.5 * m5 * (yvec[11] * yvec[11] + yvec[12] * yvec[12]);

		// Determina la distancia minima
		if (D34 < D35 && D34 < Dmin) Dmin = D34;
		else if (D35 < Dmin) Dmin = D35;
		if (Dmin > D45 && D45 < Dmin) Dmin = D45;

		// Almacena distancias minimas
		if (D34 < D35) D = D34;
		else D = D35;
		if (D > D45) D = D45;
		//if (D > D1 && D1 < D2) minabstaende << i * h << "  " << D1 << endl;
		D2 = D1;
		D1 = D;
    minabstaende << i * h << "  " << D1 << endl;
		rk4(yvec, dyvec, n, t, h, (*derivs));


		// actualiza el vector dyvec
		// Velocidades y nuevas posiciones
		dyvec[1] = yvec[3],  dyvec[2]  = yvec[4];
		dyvec[5] = yvec[7],  dyvec[6]  = yvec[8];
		dyvec[9] = yvec[11], dyvec[10] = yvec[12];
		// Beschleunigungen an den neuen Positionen
		D34 = sqrt(pow(yvec[5] - yvec[1], 2) + pow(yvec[6]  - yvec[2], 2));
		D35 = sqrt(pow(yvec[9] - yvec[1], 2) + pow(yvec[10] - yvec[2], 2));
		D45 = sqrt(pow(yvec[9] - yvec[5], 2) + pow(yvec[10] - yvec[6], 2));
		dyvec[3]  =  m4 * (yvec[5] - yvec[1])  / pow(D34, 3) + m5 * (yvec[9]  - yvec[1]) / pow(D35, 3);
		dyvec[4]  =  m4 * (yvec[6] - yvec[2])  / pow(D34, 3) + m5 * (yvec[10] - yvec[2]) / pow(D35, 3);
		dyvec[7]  =  m3 * (yvec[1] - yvec[5])  / pow(D34, 3) + m5 * (yvec[9]  - yvec[5]) / pow(D45, 3);
		dyvec[8]  =  m3 * (yvec[2] - yvec[6])  / pow(D34, 3) + m5 * (yvec[10] - yvec[6]) / pow(D45, 3);
		dyvec[11] =  m3 * (yvec[1] - yvec[9])  / pow(D35, 3) + m4 * (yvec[5]  - yvec[9]) / pow(D45, 3);
		dyvec[12] =  m3 * (yvec[2] - yvec[10]) / pow(D35, 3) + m4 * (yvec[6] - yvec[10]) / pow(D45, 3);

		
		//if (i % 10 == 0){
			datei1 << t <<" "<< yvec[1] << "  " << yvec[2] << endl;		// actualiza las posiciones x y
			datei2 << t <<" "<< yvec[5] << "  " << yvec[6] << endl;
			datei3 << t <<" "<< yvec[9] << "  " << yvec[10] << endl;
			energie << t << "  " << Ekin << "  " << Epot << "  " << Ekin + Epot << endl;
		//}
	}

	cout << endl << "E Total: " << Ekin + Epot << endl;
	cout << endl << "Dmin: " << Dmin << endl << endl;


	datei1.close();
	datei2.close();
	datei3.close();
	energie.close();
	minabstaende.close();
}
