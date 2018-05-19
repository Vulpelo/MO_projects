#include <iostream>
#include "gaussLU.h"

using namespace std;



int main() {
	int len = 4;
	int *rowsSwitched = new int[len];
	double **A = new double*[len];
	for (int i = 0; i < len; i++)
		A[i] = new double[len];
	A[0][0] = 1; A[0][1] = 20; A[0][2] = -30; A[0][3] = -4;
	A[1][0] = 4; A[1][1] = 20; A[1][2] = -6; A[1][3] = 50;
	A[2][0] = 9; A[2][1] = -18; A[2][2] = 12; A[2][3] = -11;
	A[3][0] = 16; A[3][1] = -15; A[3][2] = 14; A[3][3] = 130;

	double *b = new double[len];
	b[0] = 0; b[1] = 114; b[2] = -5; b[3] = 177;

	//cout << "Macierz pocz¹tkowa:\n";
	//printMatrix("A", A, len);
	//printVector("b", b, len); cout << endl << endl;

	//gaussMatrix(A, rowsSwitched, len);
	////gaussVectorFromMatrix(b, A, rowsSwitched, len);
	//switchRows(b, rowsSwitched, len);
	//cout << "Po metodzie gauss'a:\n";
	//printMatrix("nA", A, len);
	//printVector("nb", b, len); cout << endl << endl;
	//
	//double *x = lower(A, b, len);
	//x = upper(A, x, len);
	//cout << "Wyznaczony wektor x po metodzie LU:\n";
	//printVector("x", x, len); cout << endl;


	GMatrix m(A, len);
	m.print("Macierz pocz¹tkowa:\nA"); cout<<endl;
	m.gaussMatrix();
	m.print("Po metodzie gauss'a\ngauss_A"); cout << endl;
	double *x = m.getvX_LO(b);
	printVector("Wyznaczony wektor x po metodzie LU:\nX", x, len); cout << endl;

	return 0;
}