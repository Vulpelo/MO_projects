#include <iostream>
#include "thomas.h"

using namespace std;


int main() {

	int len = 6;
	double *u = new double[len-1];
	u[0] = 2.0 / 3; u[1] = 5.0 / 6; u[2] = 9.0 / 10; u[3] = 13.0 / 14; u[4] = 17.0 / 18;
	double *d = new double[len];
	d[0] = 30; d[1] = 20; d[2] = 10; d[3] = 10; d[4] = 20; d[5] = 30;
	double *l = new double[len-1];
	l[0] = 3.0/4; l[1] = 7.0/8; l[2] = 11.0/12; l[3] = 15.0/16; l[4] = 19.0/20;


	double *b = new double[len];
	b[0] = 94.0 / 3; b[1] = 173.0 / 4; b[2] = 581.0 / 20; b[3] = -815.0 / 28; b[4] = -6301.0 / 144; b[5] = -319.0 / 10;

	Matrix matrix(l,u,d, b, len);
	matrix.print("Macierz poczatkowa A:\nA=");
	cout << matrix.get(2, 3);
	printVector("b", b, len);
	double *x = matrix.thomas3();
	matrix.print("\n\nMacierz A po obliczeniach thomasa:\nA=");
	printVector("X=", x, len);

	matrixMultiVector(matrix.getMatrix(), x, len);


	return 0;
}
