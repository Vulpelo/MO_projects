#include <iostream>
#include <math.h>

const double stepH = 0.001;

double funAnalityczna(double t) {
	return 1 - exp(-10 * (t + atan(t)));
}

void metodaBezposredniaEulera(double h, double toNumber) {
	FILE *wyj = fopen("daneMBE", "w");

	double y = 0;
	double t = 0;

	for (t = 0; t < toNumber; t += h) {
			y = y + (10 * t*t + 20) / (t*t + 1)*(y - 1)*h;
	}


}

void metodaPosredniaEulera() {

}

void metodaTrapezow() {

}

int main()
{
	metodaBezposredniaEulera(stepH, 2.);


	return 0;
}

