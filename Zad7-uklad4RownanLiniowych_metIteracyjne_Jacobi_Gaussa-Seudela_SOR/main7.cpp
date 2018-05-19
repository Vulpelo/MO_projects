#include <iostream>
#include "matrix.h"
#include "metody.h"
#include <string>

using namespace std;
static int g;


int main() {
	int len = 4;
	double **A = new double*[len];
	for (int i = 0; i < len; i++)
		A[i] = new double[len];

	A[0][0] = 100;		 A[0][1] = 1;	A[0][2] = -2;		A[0][3] = 3;
	A[1][0] = 4;	 A[1][1] = 300;		A[1][2] = -5;	A[1][3] = 6;
	A[2][0] = 7;		 A[2][1] = -8;	A[2][2] = 400;		A[2][3] = 9;
	A[3][0] = -10;		 A[3][1] = 11;		A[3][2] = -12;	A[3][3] = 200;

	double *b = new double[len];
	b[0] = 395; b[1] = 603; b[2] = -415; b[3] = -606;

	double *x = new double[len];
	x[0] = 1; x[1] = 1; x[2] = 1; x[3] = 1;

	Metoda::jacobiego(Matrix(A, len), b, x);
	Metoda::gaussaSeidela(Matrix(A, len), b, x);
	Metoda::SOR(Matrix(A, len), b, x, 1.0 / 2.0);

	return 0;
}