#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "thomas.h"

/*
RR drugiego rzêdu:
	(d^2 * U(x)) / (dx^2) + 4*U(x) + tan(x) = 0
	z tego wychodzi ¿e:
	p(x) = 1
	q(x) = 0
	r(x) = 4
	s(x) = tan(x)


Obsar rozwiazania:
	0 <= x <= PI/4

warunki brzegowe:
	U(0) = 0;	U(PI/4) = 1/2
	z tego wychodzi ¿e:
	a-alpha,b-beta,.. znaki greckie
	a = 0;	b = 1;	r = 0
	Q = 0;	Y = 1;	0 = 1/2
*/

const int tries = 6;

double funcAnalityczna(double x) {
	double sin2x = sin(2 * x);
	return 1. / 4. * (2 * x*cos(2 * x) + 2 * sin2x - log(2)*sin2x - 2 * log(cos(x)) * sin2x);
}

double maxError(double *y, int len, double h) {
	double x = 0, d_max = 0, d = 0;

	d_max = fabs(y[0] - funcAnalityczna(x));
	for (int i = 1; i<len; i++){
		if (i == len - 1){
			x += h;
			d = fabs(y[i] - funcAnalityczna(x));
			if (d > d_max)
				d_max = d;
		}
		else{
			x += h;
			d = fabs(y[i] - funcAnalityczna(x));
			if (d > d_max)
				d_max = d;
		}
	}
	return d_max;
}

void konwencjonalna() {
	FILE *wyj = fopen("dane.dat", "w");
	FILE *wyj2 = fopen("danePrawdziwe.dat", "w"); 
	FILE *wyj3 = fopen("error.dat", "w");

	double *y;
	double h = 0.1; //krok
	double prevH = h;
	double prevError = 0;
	double a = 0, b = M_PI_4; // przedzia³; obszar rozwi¹zania; x nale¿y do [a,b]

	// ilosc wykonan
	for (int g = 0; g < tries; g++, h*=0.1) {

		int len = fabs((b - a) / h); // ilosc mo¿liwych kroków do wykonania z okreœlonym h
									 // wektory do alg. Thomas'a: Ay = b. Gdzie A to macierz trój-diagonalna (u,d,l)
		double *vB = new double[len]; //b
		double *u = new double[len - 1];
		double *d = new double[len];
		double *l = new double[len - 1];
		// ustawianie wartoœci wektorów zgodnie z wzorem postaci wektorowo-macierzowej
		//ustawienie macierzy
		u[0] = 0;
		d[0] = 1;
		double hh = 1.0 / (h*h);
		for (int i = 1; i < len - 1; i++) {
			u[i] = hh;
			d[i] = 4.0 - 2.0*hh;
			l[i - 1] = hh;
		}
		d[len - 1] = 1;
		l[len - 2] = 0;
		//ustawienie wektora
		vB[0] = 0;
		double x = a;
		for (int i = 1; i < len - 1; i++)
			vB[i] = -tan(i*h);
		vB[len - 1] = 0.5;

		Matrix thomas(u, d, l, vB, len);
		y = thomas.thomas3();

		double error = maxError(y, len, h);
		fprintf(wyj3, "%.5e %.5e\n", h, error);
		x = 0;
		if (g == 3) {
			for (int i = 0; i < len; i++) {
				fprintf(wyj, "%.5e %.5e\n", x, y[i]);
				fprintf(wyj2, "%.5e %.5e\n", x, funcAnalityczna(x));
				x += h;
			}
			std::cout << "h=" << h << "; prevh=" << prevH << "; Konwencjonalna dy/dx:" << (log10(prevError) - log10(error)) / (log10(prevH) - log10(h)) << std::endl;
			//printVector("Y", y, len, true);
		}
		// zapisywanie b³êdu bezwzglêdnego do pliku
		delete[] y;
		delete[] u;
		delete[] d;
		delete[] l;
		delete[] vB;
		prevH = h;
		prevError = error;
	}
	fclose(wyj);
	fclose(wyj2);
	fclose(wyj3);
}

void numerowa() {
	FILE *wyj = fopen("daneNumera.dat", "w");
	FILE *wyj2 = fopen("danePrawdziwe.dat", "w");
	FILE *wyj3 = fopen("errorNumera.dat", "w");

	double *y;
	double h = 0.1; //krok
	double prevH = h;
	double prevError = 0;
	double a = 0, b = M_PI_4; // przedzia³; obszar rozwi¹zania; x nale¿y do [a,b]

	// ilosc wykonan
	for (int g = 0; g < tries; g++, h *= 0.1) {

		int len = fabs((b - a) / h); // ilosc mo¿liwych kroków do wykonania z okreœlonym h
									 // wektory do alg. Thomas'a: Ay = b. Gdzie A to macierz trój-diagonalna (u,d,l)
		double *vB = new double[len]; //b
		double *u = new double[len - 1];
		double *d = new double[len];
		double *l = new double[len - 1];
		// ustawianie wartoœci wektorów zgodnie z wzorem postaci wektorowo-macierzowej
		//ustawienie macierzy
		u[0] = 0;
		d[0] = 1;
		for (int i = 1; i < len - 1; i++) {
			u[i] = 1. / (h*h) + 1./3.;
			d[i] = (10./3.) - 2. / (h*h);
			l[i - 1] = 1. / (h*h) + 1./3.;
		}
		d[len - 1] = 1;
		l[len - 2] = 0;
		
		//ustawienie wektora
		vB[0] = 0;
		double x = a;
		for (int i = 1; i < len - 1; i++) {
			x += h;
			vB[i] = -tan(x*h-1)/12. - (10*tan(x*h))/12. - tan(i*h+h)/12.;
		}
		vB[len - 1] = 0.5;

		Matrix thomas(u, d, l, vB, len);
		y = thomas.thomas3();

		double error = maxError(y, len, h);
		fprintf(wyj3, "%.5e %.5e\n", h, error);

		x = 0;
		if (g == 2) {
			for (int i = 0; i < len; i++) {
				fprintf(wyj, "%.5e %.5e\n", x, y[i]);
				fprintf(wyj2, "%.5e %.5e\n", x, funcAnalityczna(x));
				x += h;
			}
			std::cout << "h=" << h << "; prevh=" << prevH << "; Neuronowa dy/dx:" << (log10(prevError) - log10(error)) / (log10(prevH) - log10(h)) << std::endl;
			//printVector("Y", y, len, true);
		}
		// zapisywanie b³êdu bezwzglêdnego do pliku
		delete[] y;
		delete[] u;
		delete[] d;
		delete[] l;
		delete[] vB;
		prevH = h;
		prevError = error;
	}
	fclose(wyj);
	fclose(wyj2);
	fclose(wyj3);
}




int main() {
	konwencjonalna();
	numerowa();
	return 0;
}