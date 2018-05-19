#pragma once
#include <iostream>


class GMatrix {
private:
	unsigned int len;
	int *rowsSwitched;
	double **Matrix;

	double *lower(double *b) {
		double *y = new double[len];
		for (int i = 0; i < len; i++)
			y[i] = b[rowsSwitched[i]];

		for (int i = 0; i <len; i++) {
			double sum = 0;
			for (int j = 0; j < i; j++)
				sum += Matrix[i][j] * y[j];
			y[i] = y[i] - sum;
		}
		return y;
	}

	double *upper(double *y) {
		double *x = new double[len];
		for (int i = 0; i < len; i++)
			x[i] = y[i];

		for (int i = len - 1; i >= 0; i--) {
			double sum = 0;
			for (int j = i + 1; j < len; j++) {
				sum += Matrix[i][j] * x[j];
			}
			x[i] = (x[i] - sum) / Matrix[i][i];
		}
		return x;
	}

public:
	GMatrix(double **M, unsigned int len) {
		this->len = len;
		this->rowsSwitched = new int[len];
		Matrix = new double*[len];
		for (int i = 0; i < len; i++) {
			this->rowsSwitched[i] = i;
			Matrix[i] = new double[len];
			for (int j = 0; j < len; j++)
				Matrix[i][j] = M[i][j];
		}
	}

	void print(char *name) {
		printf("%s=[\n", name);
		for (int i = 0; i < len; i++) {
			printf("[ ");
			for (int j = 0; j < len - 1; j++) {
				printf("%+.5e; ", Matrix[i][j]);
			}
			printf("%+.5e]\n", Matrix[i][len - 1]);

		}
		printf("]\n");
	}
	
	unsigned int indexMaxColElemMatrix(unsigned int col, unsigned int fromRow) {
		double maxEl = -INFINITY;
		unsigned int index = NAN;
		for (int i = fromRow; i < len; i++)
			if (fabs(Matrix[i][col]) > fabs(maxEl)) {
				maxEl = Matrix[i][col];
				index = i;
			}
		return index;
	}

	void gaussMatrix() {
		//tworzenie zmiennych i przypisywanie wartoœci (prevM = M).
		for (int i = 0; i < len; i++)
			rowsSwitched[i] = i;
		double **prevM = new double*[len];
		for (int i = 0; i < len; i++)
			prevM[i] = new double[len];

		for (int n = 0; n < len - 1; n++) {
			//przepisywanie macierzy do innej zmiennej (prevM = nM)
			for (int i = 0; i < len; i++) {
				for (int j = 0; j < len; j++)
					prevM[i][j] = Matrix[i][j];
			}
			
			//Ewentualna zamiana wierszy w macierzy gdy (prevM[n][n] == 0 [lewy, górny róg liczonej macierzy])
			if (prevM[n][n] == 0) {
				unsigned int row = indexMaxColElemMatrix(n, n);
				double *tmp = prevM[row];
				prevM[row] = prevM[n];
				prevM[n] = tmp;

				rowsSwitched[n] = row;
				rowsSwitched[row] = n;
			}

			//wyliczanie nowych elementow macierzy
			for (int i = 1 + n; i < len; i++) {
				for (int j = n; j < len; j++)
					Matrix[i][j] = prevM[i][j] - prevM[n][j] * prevM[i][n] / prevM[n][n];
				Matrix[i][n] = prevM[i][n] / prevM[n][n];
			}
		}
	}

	//Ax = b; A = LO;  
	double *getvX_LO(double *b) {
		double *y = lower(b);
		y = upper(y);
		return y;
	}
};

void printVector(char *name, double *x, unsigned int len) {
	printf("%s=[ ", name);
	for (int i = 0; i < len - 1; i++)
		printf("%+.5e; ", x[i]);
	printf("%+.5e]", x[len - 1]);
}

double *gaussVectorFromMatrix(double *b, double **A, int *rowsSwitched, unsigned int len) {
	for (int i = 1; i < len; i++) {
		if (rowsSwitched[i - 1] != -1) {
			//wektor
			double tmp = b[i - 1];
			b[i - 1] = b[rowsSwitched[i - 1]];
			b[rowsSwitched[i - 1]] = tmp;
		}
		b[i] = b[i] - b[i - 1] * A[i][i - 1] / A[i - 1][i - 1];
	}
	return b;
}