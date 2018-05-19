#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;

const double TOLX = 0.0001;
const double TOLF = 0.00001;
const double n_max = 1000;


double fun1(double arg) {
	//return arg;
	return (sin(arg / 4.0)*sin(arg / 4.0)) - arg;
}
double Ofun1(double arg) {
	//return arg;
	return (sin(arg / 4.0)*sin(arg / 4.0));
}
double differentiation1(double arg) {
	//return 1;
	return sin(arg / 2.0) * (1.0 / 4.0);				// (sin(arg / 4)*sin(arg / 4));
}

double fun2(double arg) {
	return (tan(2.0 * arg) - 1 - arg);
}
double Ofun2(double arg) {
	return (tan(2.0 * arg) - 1);
}
double differentiation2(double arg) {
	return 2.0 / (sin(2.0 * arg)*sin(2.0 * arg));	// (tan(2 * arg) - 1);
}





void picard(double (*fun)(double), double (*diff)(double), double startPoint){
	cout << "\nPicard:\n";
	int iteracje=0;
	double fx = startPoint;
	double x=fx;
	do{
		printf("n=%d : Fx: %.5e : En: %.5e || funkcja: %.5e\n", iteracje, fx, x - fx, fun(x));
		x = fx;
		fx = fun(x);
		iteracje++;
	} while (iteracje <= n_max && fabs(x - fx) > TOLX && fabs(fx) > TOLF && fabs(diff(fx)) < 1);
	if (fabs(diff(x)) > 1) {
		printf("CIAG JEST ROZBIERZNY :: Fx: %.5e || po %d iteracjach\n", fx, iteracje);
	}
	else
		printf("n=%d : Fx: %.5e : En: %.5e || funkcja: %.5e\n", iteracje, fx, x - fx, fun(x));
};


void bisekcja(double (*fun)(double), double odA, double doB) {
	cout << "\nBisekcja:\n";
	int iteracje = 0;
	double a, b; //przedzial
	double x;
	double prevX;
	x = INFINITY;
	a = odA;
	b = doB;
	do {
		printf("n=%d : Fx: %.5e : En: %.5e ||przedzial <%.5e ;; %.5e> || funkcja:: %.5e\n", iteracje, x, (b - a) / 2, a, b, fun(x));
		if ((fun(a) > 0 && fun((a + b) / 2.0) < 0) || (fun(a) < 0 && fun((a + b) / 2.0) > 0)) {
			b = (a+b)/2.0;
			x = b;
		}
		else if ((fun((a + b) / 2.0) > 0 && fun(b) < 0) || (fun((a + b) / 2.0) < 0 && fun(b) > 0)){
			a = (a+b)/2.0;
			x = a;
		}
		else {
			cout << "Brak odpowiedniego przedzia³u" << endl;
			break;
		}
			prevX = x;
			iteracje++;
	} while (iteracje <= n_max && fabs((b - a)/2) > TOLX && fabs(x) > TOLF);
	printf("n=%d : Fx: %.5e : En: %.5e ||przedzial <%.5e ;; %.5e> || funkcja:: %.5e\n", iteracje, x, (b - a) / 2, a, b, fun(x));
}


void newton(double(*fun)(double), double(*diff)(double), double startPoint) {
	cout << "\nMetoda Newtona:\n";
	int iteracje = 0;
	double fx = startPoint;
	double x=fx;
	do {
		printf("n=%d : Fx: %.5e : En: %.5e || funkcja: %.5e\n", iteracje, fx, x - fx, fun(x));
		x = fx;
		double d = diff(x);
		if (d == 0) { break; }
		fx = x - (fun(x)/diff(x)) ;
		iteracje++;
	} while (iteracje <= n_max && fabs(x - fx) > TOLX && fabs(fx) > TOLF);
	if (diff(x) == 0) {
		cout << "Dzielenie przez zero (f'(Xn) = 0)\n";
		printf("CIAG JEST ROZBIERZNY :: Fx: %.5e || po %d iteracjach\n", fx, iteracje);
	}
	else
		printf("n=%d : Fx: %.5e : En: %.5e || funkcja: %.5e\n", iteracje, fx, x - fx, fun(x));

};


void siecznych(double(*fun)(double), double(*diff)(double), double xA, double xB) {
	cout << "\nMetoda siecznych:\n";
	int iteracje = 0;
	double fx = xA;
	double x = xB;
	double xprev = x;
	do {
		printf("n=%d : Fx: %.5e : En: %.5e || funkcja: %.5e\n", iteracje, fx, x - fx, fun(x));
		xprev = x;
		x = fx;

		fx = x - (fun(x) /( (fun(x)-fun(xprev)) / (x - xprev) ) );
		iteracje++;
	} while (iteracje <= n_max && fabs(x - fx) > TOLX && fabs(fx) > TOLF);
	/*if (diff(x) == 0) {
		cout << "Dzielenie przez zero (f'(Xn) = 0)\n";
		printf("CIAG JEST ROZBIERZNY :: Fx: %e.5 || po %d iteracjach\n", fx, iteracje);
	}
	else*/
	printf("n=%d : Fx: %.5e : En: %.5e || funkcja: %.5e\n", iteracje, fx, x - fx, fun(x));
};


int main() {
	double (*funk)(double) = fun1;
	double(*diff)(double) = differentiation1;

	cout << "\n=======================================\nFUNKCJA:: sin^2(x/4)-x = 0\n";
	funk = Ofun1;
	picard(funk, diff, 2);

	funk = fun1;
	bisekcja(funk, -2, 4);
	newton(funk, diff, 0.5);
	siecznych(funk, diff, 1, 1.5);


	cout << "\n=======================================\nFUNKCJA:: tg(2x)-x-1 = 0\n";
	diff = differentiation2;
	funk = Ofun2;
	picard(funk, diff, 4);

	funk = fun2;
	bisekcja(funk, 0.25, 0.6);
	newton(funk, diff, 0.4);
	siecznych(funk, diff, 1, 1.5);

	return 0;
}