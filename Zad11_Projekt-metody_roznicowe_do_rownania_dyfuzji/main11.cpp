#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
/*
x jest [0,1]
t jest [0, t_max]

*/


double properFunc(double D, double t, double x) {
	return 1 + exp(-(M_PI*M_PI) * D * t) * cos(M_PI * x);
}

void dataForChart(double x_start, double x_end, double h, double t, double D) {
	FILE *wyj = fopen("dataProperFunc.dat", "w");
	for (double x = x_start; x <= x_end; x += h) {
		fprintf(wyj, "%.5e %.5e\n", x, properFunc(D, t, x));
	}
	fclose(wyj);
}


// Klasyczna metoda bezpoœrednia
void KMB(double h, double dt, double t_max, double D) {
	double lambda = D*dt / (h*h);
	if (lambda > 4.5) {
		printf("LAMBDA WIEKSZA OD 4.5 W METODZIE BEZPOSREDNIEJ %f \n", lambda);
		return;
	}
	printf("LAMBDA = %f\n", lambda);
	FILE *wyj = fopen("dataFuncKMB.dat", "w");
	FILE *wyj2 = fopen("dataFuncKMB_oneData.dat", "w");
	double x = 0.5;

	int nrOfT = int(t_max / dt); // liczba krokow czasowych
	// Uzupe³inanie tablicy warunkami poczatkowymi
	int nrOfH = int(1. / h) + 1;
	double *Uk = new double[nrOfH];
	fprintf(wyj, "%.5e", 0.0);
	for (int i = 0; i < nrOfH; i++) {
		Uk[i] = 1 + cos(M_PI*(h*i));
		fprintf(wyj, " %.5e", Uk[i]);
	}

	double *Ukp;
	
	for (int j = 0; j < nrOfT; j++) {
		Ukp = new double[nrOfH];
		Ukp[0] = 0; // warunek brzegowy
		fprintf(wyj, "\n%.5e %.5e", dt*j, Ukp[0]);
		for (int i = 1; i < nrOfH - 1; i++) { // wyliczanie nastepnego kroku czasu
			Ukp[i] = lambda*Uk[i - 1] + (1 - 2 * lambda)*Uk[i] + lambda*Uk[i + 1];
			fprintf(wyj, " %.5e", Ukp[i]);
		}
		Ukp[nrOfH - 1] = 0; // warunek brzegowy
		fprintf(wyj, " %.5e", Ukp[nrOfH - 1]);
		if (j == 10) {
			for(int l=0; l< nrOfH; l++)
				fprintf(wyj2, "%.5e %.5e\n", h*l, Ukp[l]);
		}
		delete[] Uk;
		Uk = Ukp; // przypisywanie do nastepnej petli
	}
	fclose(wyj);
	fclose(wyj2);
}


int main() {
	double x_start = 0, x_end = 1;
	double t_min = 0, t_max = 0.5;
	double D = 1;
	double h = 0.05; // Krok miêdzy kolejnymi wartoœciami x

	dataForChart(x_start, x_end, 0.01, 0.01, D);
	KMB(h, 0.001, t_max, D);

	return 0;
}