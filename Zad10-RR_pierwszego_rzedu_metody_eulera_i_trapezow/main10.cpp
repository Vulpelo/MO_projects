#include <iostream>
#include <math.h>

const double stepH = 0.001;

double funAnalityczna(double t) {
	return 1 - exp(-10 * (t + atan(t)));
}

void wykFuncAnalitycznej(double toNumber) {
	FILE *wyj = fopen("daneAalityczna.dat", "w");
	for (double i = 0; i < toNumber; i += stepH) {
		fprintf(wyj, "%.5e %.5e\n", i, funAnalityczna(i));
	}
	fclose(wyj);
}

// numeryczna stabilnoœæ
void metodaBezposredniaEulera(double h, double toNumber) {
	FILE *wyj = fopen("daneMBE", "w");
	FILE *errorWyj = fopen("errorDaneMBE", "w");

	double y = 0;
	double t = 0;

	//double g = 1 + (-10 * (t*t + 2)) / ((t*t + 1)*(t*t + 1)) * h;
	for (t = 0; t < toNumber; t += h) {
			y = y - (10 * t*t + 20) / (t*t + 1)*(y - 1)*h;
			fprintf(wyj, "%.5e %.5e\n", t, y);
			//g = 1 + (-10 * (t*t + 2)) / ((t*t + 1)*(t*t + 1)) * h;
			//std::cout << g << std::endl;
	}

	double tmpError;
	double tmpH;
	double nH = 0.1;
	for (int i = 0; i < 7; i++, nH *= 0.1) {

		t = 0;
		y = 0;
		double maxError = 0;
		for (t = 0; t < toNumber; t += nH) {
			y = y - (10 * t*t + 20) / (t*t + 1)*(y - 1)*nH;

			if (maxError < fabs(y - funAnalityczna(t))) {
				maxError = fabs(y - funAnalityczna(t));
			}
		}
		if (i == 3) {
			tmpError = maxError;
			tmpH = nH;
		}
		else if (i == 4)
		{
			printf("MBE: %.5e", fabs((log10(maxError) - log10(tmpError)) / (log10(nH) - log10(tmpH))) );
		}
		fprintf(errorWyj, "%.5e %.5e\n", nH, maxError);
	}

	fclose(wyj);
	fclose(errorWyj);
}

void metodaBezposredniaEuleraNIESTABILNY(double h, double toNumber) {
	FILE *wyj = fopen("daneMBE-NS", "w");

	double y = 0;
	double t = 0;

	double g = 1 - (10 *(t*t + 2)) / (t*t + 1) * h;
	for (t = 0; t < toNumber; t += h) {
		y = y - (10 * t*t + 20) / (t*t + 1)*(y - 1)*h;
		fprintf(wyj, "%.5e %.5e\n", t, y);
		g = 1 - (10 * t*t + 20) / (t*t + 1) * h;
		std::cout << g << " " << y << std::endl;
	}

	fclose(wyj);
}

void metodaPosredniaEulera(double h, double toNumber) {
	FILE *wyj = fopen("daneMPE", "w");
	FILE *errorWyj = fopen("errorDaneMPE", "w");

	double y = 0;
	double t = 0;
	double yk1;
	for (t = 0; t < toNumber; t += h) {
		yk1 = (10 * (t + h)*(t + h) + 20) / ((t + h)*(t + h) + 1) * h;
		y = (y + yk1) / (1 + yk1);
		fprintf(wyj, "%.5e %.5e\n", t, y);
	}

	double tmpError;
	double tmpH;
	double nH = 0.1;
	for (int i = 0; i < 7; i++, nH *= 0.1) {

		t = 0;
		y = 0;
		double maxError = 0;
		for (t = 0; t < toNumber; t += nH) {
			yk1 = (10 * (t + nH)*(t + nH) + 20) / ((t + nH)*(t + nH) + 1) * nH;
			y = (y + yk1) / (1 + yk1);

			if (maxError < fabs(y - funAnalityczna(t) ) ) {
				maxError = fabs(y - funAnalityczna(t));
			}
		}
		fprintf(errorWyj, "%.5e %.5e\n", nH, maxError);
		if (i == 3) {
			tmpError = maxError;
			tmpH = nH;
		}
		else if (i == 4)
		{
			printf("\nMPE: %.5e\n", fabs((log10(maxError) - log10(tmpError)) / (log10(nH) - log10(tmpH))));
		}
	}



	fclose(wyj);
	fclose(errorWyj);
}

void metodaTrapezow(double h, double toNumber) {
	FILE *wyj = fopen("daneMT", "w");
	FILE *errorWyj = fopen("errorDaneMT", "w");

	double y = 0;
	double t1 = 0;
	double yk1, yk;
	for (t1 = 0; t1 < toNumber; t1 += h) {
		double t = (t1 + t1 + h) / 2.;
		yk = (10 * t*t + 20) / (t*t + 1) * h;
		yk1 = (10 * (t + h)*(t + h) + 20) / ((t + h)*(t + h) + 1) * h;
		y = (-y * yk + yk + yk1 + 2*y) / (2 + yk1);
		fprintf(wyj, "%.5e %.5e\n", t, y);
	}

	double tmpError;
	double tmpH;
	double nH = 0.1;
	for (int i = 0; i < 7; i++, nH *= 0.1) {

		t1 = 0;
		y = 0;
		double maxError = 0;
		for (t1 = 0; t1 < toNumber; t1 += nH) {
			double t = (t1 + t1 + nH) / 2.;
			yk = (10 * t*t + 20) / (t*t + 1) * nH;
			yk1 = (10 * (t + nH)*(t + nH) + 20) / ((t + nH)*(t + nH) + 1) * nH;
			y = (-y * yk + yk + yk1 + 2 * y) / (2 + yk1);

			if (maxError < fabs(funAnalityczna(t1) - y)) {
				maxError = fabs(funAnalityczna(t1) - y);
			}
		}
		fprintf(errorWyj, "%.5e %.5e\n", nH, maxError);
		if (i == 3) {
			tmpError = maxError;
			tmpH = nH;
		}
		else if (i == 4)
		{
			printf("MT: %.5e", fabs((log10(tmpError) - log10(maxError)) / (log10(tmpH) - log10(nH))));
		}
	}


	fclose(wyj);
	fclose(errorWyj);
}

int main()
{
	double to = 0.5;
	wykFuncAnalitycznej(to);
	metodaBezposredniaEulera(stepH, to);
	// metodaBezposredniaEuleraNIESTABILNY(0.1, 2.);

	metodaPosredniaEulera(stepH, to);
	metodaTrapezow(stepH, to);

	return 0;
}

