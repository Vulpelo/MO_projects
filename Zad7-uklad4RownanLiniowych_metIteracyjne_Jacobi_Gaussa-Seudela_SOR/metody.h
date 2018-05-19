#pragma once

#include <iostream>
#include "matrix.h"

const unsigned int maxIter = 100;
const double TOLX = 0.000001;
const double TOLF = 0.000001;


class Metoda {
public:
	static void jacobiego(Matrix mat, double *b, double *startX) {
		std::cout << "\n####################################################\nJacobiego:\n";

		unsigned int len = mat.getLen();
		double *x = new double[len];
		double *xprev = new double[len];
		double *estx = new double[len];
		double *estf = new double[len];


		for (int i = 0; i < mat.getLen(); i++) {
			x[i] = startX[i];
			xprev[i] = startX[i];
		}

		unsigned int iteracje = 0;
		Matrix L(mat);
		L.lower();
		Matrix U(mat);
		U.upper();
		Matrix D(mat);
		D.diagonal();
		Matrix ID(D);
		ID.inverse();

		Matrix LU(L + U);
		Matrix IDLU(ID*LU);
		double *c = (ID * b);


		do {
			std::cout << "Iteracja nr. " << iteracje << std::endl;
			printVector("X", x, len);
			std::cout << " | estx: " << normMax(estx, len);
			std::cout << " | res: " << normMax(estf, len);
			std::cout << "\n\n";
		
			for (int i = 0; i < len; i++)
				xprev[i] = x[i];

			double *v2 = IDLU*xprev;
			x = vectorSubtract(c, v2, len);

			for (int i = 0; i < len; i++)
				estx[i] = fabs(x[i] - xprev[i]);

			estf = mat*x;
			for (int i = 0; i < len; i++)
				estf[i] -= b[i];


			iteracje++;
		} while (iteracje < maxIter &&  normMax(estx, len) > TOLX && normMax(estf, len) > TOLF);
		printVector("b na podstawie wyliczonego x. b", mat*x, len);
	}

	static void gaussaSeidela(Matrix mat, double *b, double *startX) {
		std::cout << "\n####################################################\nGaussa-Seidela:\n";

		unsigned int len = mat.getLen();
		double *x = new double[len];
		double *xprev = new double[len];
		double *estx = new double[len];
		double *estf = new double[len];


		for (int i = 0; i < mat.getLen(); i++) {
			x[i] = startX[i];
			xprev[i] = startX[i];
		}

		unsigned int iteracje = 0;
		Matrix L(mat);
		L.lower();
		Matrix U(mat);
		U.upper();
		Matrix D(mat);
		D.diagonal();
		
		Matrix I_LD(D);
		I_LD.inverse();

		Matrix M(I_LD*U);

		double *c = I_LD * b;


		do {
			std::cout << "Iteracja nr. " << iteracje << std::endl;
			printVector("X", x, len);
			std::cout << " | estx: " << normMax(estx, len);
			std::cout << " | res: " << normMax(estf, len);
			std::cout << "\n\n";

			for (int i = 0; i < len; i++)
				xprev[i] = x[i];

			double *v2 = M * xprev;
			x = vectorSubtract(c, v2, len);

			for (int i = 0; i < len; i++)
				estx[i] = fabs(x[i] - xprev[i]);

			estf = mat*x;
			for (int i = 0; i < len; i++)
				estf[i] -= b[i];

			iteracje++;
		} while (iteracje < maxIter &&  normMax(estx, len) > TOLX && normMax(estf, len) > TOLF);
		printVector("b na podstawie wyliczonego x. b", mat*x, len);
	}

	static void SOR(Matrix mat, double *b, double *startX, double w) {
		std::cout << "\n####################################################\nSOR z parametrem w:\n";

		unsigned int len = mat.getLen();
		double *x = new double[len];
		double *xprev = new double[len];
		double *estx = new double[len];
		double *estf = new double[len];


		for (int i = 0; i < mat.getLen(); i++) {
			x[i] = startX[i];
			xprev[i] = startX[i];
		}

		unsigned int iteracje = 0;
		Matrix L(mat);
		L.lower();
		Matrix U(mat);
		U.upper();
		Matrix D(mat);
		D.diagonal();

		Matrix iLDw( L + (D * (1.0/w)) );
		iLDw.inverse();
		double *c = iLDw*b;

		Matrix M(iLDw * (D * (1 - 1.0 / w) + U));


		do {
			std::cout << "Iteracja nr. " << iteracje << std::endl;
			printVector("X", x, len);
			std::cout << " | estx: " << normMax(estx, len);
			std::cout << " | res: " << normMax(estf, len);
			std::cout << "\n\n";

			for (int i = 0; i < len; i++)
				xprev[i] = x[i];

			double *v2 = M * xprev;
			x = vectorSubtract(c, v2, len);

			for (int i = 0; i < len; i++)
				estx[i] = fabs(x[i] - xprev[i]);

			estf = mat*x;
			for (int i = 0; i < len; i++)
				estf[i] -= b[i];

			iteracje++;
		} while (iteracje < maxIter &&  normMax(estx, len) > TOLX && normMax(estf, len) > TOLF);
		printVector("b na podstawie wyliczonego x. b", mat*x, len);
	}

};
