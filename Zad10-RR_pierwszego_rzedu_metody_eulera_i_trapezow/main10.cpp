#include <iostream>
#include <math.h>

const double stepH = 0.001;

double funAnalityczna(double t) {
	return 1 - exp(-10 * (t + atan(t)));
}

void wykFuncAnalitycznej() {
	FILE *wyj = fopen("daneAalityczna.dat", "w");
	for (double i = 0; i < 2; i += stepH) {
		fprintf(wyj, "%.5e %.5e\n", i, funAnalityczna(i));
	}
	fclose(wyj);
}

// numeryczna stabilnoœæ
void metodaBezposredniaEulera(double h, double toNumber) {
	FILE *wyj = fopen("daneMBE", "w");

	double y = 0;
	double t = 0;

	for (t = 0; t < toNumber; t += h) {
			y = y - (10 * t*t + 20) / (t*t + 1)*(y - 1)*h;
			fprintf(wyj, "%.5e %.5e\n", t, y);
	}

	fclose(wyj);
}

void metodaPosredniaEulera(double h, double toNumber) {
	FILE *wyj = fopen("daneMPE", "w");

	double y = 0;
	double t = 0;
	double yk1;
	for (t = 0; t < toNumber; t += h) {
		yk1 = (10 * (t + h)*(t + h) + 20) / ((t + h)*(t + h) + 1) * h;
		y = (y - yk1) / (1 - yk1);
		fprintf(wyj, "%.5e %.5e\n", t, y);
	}

	fclose(wyj);
}

void metodaTrapezow(double h, double toNumber) {
	FILE *wyj = fopen("daneMT", "w");

	double y = 0;
	double t = 0;
	double yk1, yk;
	for (t = 0; t < toNumber; t += h) {
		yk = (10 * t*t + 20) / (t*t + 1);
		yk1 = (10 * (t + h)*(t + h) + 20) / ((t + h)*(t + h) + 1);
		y = (y*(yk+2) - yk - yk1) / (2 - yk1);
		fprintf(wyj, "%.5e %.5e\n", t, y);
	}

	fclose(wyj);
}

int main()
{
	wykFuncAnalitycznej();
	metodaBezposredniaEulera(stepH, 2.);

	metodaPosredniaEulera(stepH, 2.);
	metodaTrapezow(stepH, 2.);

	return 0;
}

