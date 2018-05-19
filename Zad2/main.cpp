#include <iostream>
#include <fstream>

using namespace std;

double bWzgledny(double przyb, double wynikPrecyzyjny) {
	double d1 = (przyb - wynikPrecyzyjny);
	double w = (d1 / wynikPrecyzyjny);
	return abs(w);
}

double my_exp(double x, unsigned long int precyzja) {
	double potega = 1;
	double silnia = 1;
	double wynik = 0;
	for (long int i = 0; i < precyzja; i++) {
		wynik += potega * silnia;
		potega *= x;
		silnia = silnia * (1.0 / (i + 1));
	}
	return wynik;
}


double func(double x) {
	return (1 - exp(-x)) / x;
}

double funcTaylor(double x, double wynikPrecyzyjny, double maxWielkoscBledu) {
	double wynik = 0;
	long int precyzja = 3;
	do {
		precyzja++;
		double expon = my_exp(x, precyzja);
		wynik = (expon - 1) / (x * expon);
	} while (precyzja < 200);

	return wynik;
}



void print1(char* text, double wynik, double wynikPrecyzyjny) {
	printf("%s wynik:%.20e ; wynik precyzyjny:%.20e ; blad wzgledny:%.20e\n", text, wynik, wynikPrecyzyjny, bWzgledny(wynik, wynikPrecyzyjny));
}


void funcCount(double x, double wynikPrecyzyjny, double maxWielkoscBledu) {
	
	if (x > 5.6234132519034905e-17) {
		print1("Func:", func(x), wynikPrecyzyjny);
	}
	else
		print1("Taylor:", funcTaylor(x, wynikPrecyzyjny, maxWielkoscBledu), wynikPrecyzyjny);
}

int main() {
	fstream wej("dane.txt");
	double maxWielkoscBledu = 0.9;

	while(wej.good()){
		double logarytm;
		wej >> logarytm;
		double x;//zmienna
		wej >> x;
		double wynikPrecyzyjny;
		wej >> wynikPrecyzyjny;


		//printf("log:%.20e ; X:%.20e ; wynik precyzyjny:%.20e\n",logarytm, x, wynikPrecyzyjny);
		funcCount(x, wynikPrecyzyjny, maxWielkoscBledu);
	};
	return 0;
}