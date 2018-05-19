#include "Matrix.h"

using namespace std;


const double TOLX = 0.000001;
const double TOLF = 0.000001;
const double n_max = 1000;


double fun1(double *x) {
	return x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 2;
}
double fun2(double *x) {
	return x[0] * x[0] + x[1] * x[1] - 1;
}
double fun3(double *x) {
	return x[0] * x[0] - x[1];
}

double fun1diff(double *x, short nrVar) {
	switch (nrVar) {
	case 0:
		return 2 * x[0];
	case 1:
		return 2 * x[1];
	case 2:
		return 2 * x[2];
	}
}
double fun2diff(double *x, short nrVar) {
	switch (nrVar) {
	case 0:
		return 2 * x[0];
	case 1:
		return 2 * x[1];
	case 2:
		return 0;
	}
}
double fun3diff(double *x, short nrVar) {
	switch (nrVar) {
	case 0:
		return 2 * x[0];
	case 1:
		return -1;
	case 2:
		return 0;
	}
}

void myPrint(int n, double *x, double *F, unsigned int len, double *estx) {
	printf("n=%5d; ", n); printVector("Xn", x, len); printVector("; Fn", F, len);
	printf("; estMax=%.5e; resMax=%.5e\n", normMax(estx, len), normMax(F, len));
}

void newton(listFunction *funs, listDiffFunction *diffFuns, unsigned int len){
	int n = 0;

	double *estx = new double[len];
	double *F = new double[len];
	double *x = new double[len];
	for (int i = 0; i < len; i++)
		x[i] = 1;

	x[2] = -1;

	double *prevx = new double[len];

	listDiffFunction **J = makeMatrix(diffFuns, len);
	myPrint(n, x, F, len, estx);
	do {
		for (int i = 0; i < len; i++) {
			F[i] = funs[i](x);
			prevx[i] = x[i];
		}
		x = vectorSubtract(x, matrixMultiVector(inverseJacobian(J, x, len), F, len), len);
		for (int i = 0; i < len; i++)
			estx[i] = fabs(x[i] - prevx[i]);

		n++;
		myPrint(n, x, F, len, estx);
	} while (normMax(F, len) > TOLF && normMax(estx, len) > TOLX && n < n_max);
}



int main() {
	unsigned int len = 3;
	listFunction *fun  = new listFunction[len];
	fun[0] = fun1;
	fun[1] = fun2;
	fun[2] = fun3;
	listDiffFunction *difffun = new listDiffFunction[len];
	difffun[0] = fun1diff;
	difffun[1] = fun2diff;
	difffun[2] = fun3diff;

	newton(fun, difffun, len);

	delete fun;
	delete difffun;
	return 0;
}
