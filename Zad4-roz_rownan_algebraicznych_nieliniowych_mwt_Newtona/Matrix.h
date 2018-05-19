#pragma once

#include <iostream>
#include <cmath>

typedef double(*listFunction)(double*);
typedef double(*listDiffFunction)(double*, short);


double normVector(double *V, unsigned int len) {
	double s = 0;
	for (int i = 0; i < len; i++)
		s += V[i] * V[i];
	return sqrt(s);
}

double normMax(double *V, unsigned int len) {
	double biggest = fabs(V[0]);
	for (int i = 1; i < len; i++) {
		if (fabs(V[i]) > biggest)
			biggest = fabs(V[i]);
	}
	return biggest;
}

void printMatrix(char *name, double **M, unsigned int len) {
	printf("%s=[\n", name);
	for (int i = 0; i < len; i++) {
		printf("[ ");
		for (int j = 0; j < len - 1; j++) {
			printf("%+.5e; ", M[i][j]);
		}
		printf("%+.5e]\n", M[i][len - 1]);

	}
	printf("]\n");
}

void printVector(char *text, double *x, unsigned int len) {
	printf("%s=[ ", text);
	for (int i = 0; i < len - 1; i++)
		printf("%+.5e; ", x[i]);
	printf("%+.5e]", x[len - 1]);
}

listDiffFunction** makeMatrix(listDiffFunction *funs, unsigned int len) {
	listDiffFunction **mat = new listDiffFunction*[len];
	for (int i = 0; i < len; i++) {
		mat[i] = new listDiffFunction[len];
		for (int j = 0; j < len; j++) {
			mat[i][j] = funs[i];
		}
	}
	return mat;
};

double detMatrix(listDiffFunction **mat, double *x, unsigned int len) {
	double result = 0;

	for (int i = 0; i < len; i++)
	{
		double a = 1;
		for (int j = i; j < len + i; j++) {
			if (j >= len)
				a *= mat[j - i][j - len](x, j-len);
			else
				a *= mat[j - i][j](x, j);
		}
		result += a;

		a = 1;
		for (int j = len - 1 - i; j >= -(i); j--) {
			if (j < 0)
				a *= mat[len - j - 1 - i][j + len](x, j + len);
			else
				a *= mat[len - j - 1 - i][j](x, j);
		}
		result -= a;
	}

	return result;
};

double detMatrix(double **mat, unsigned int len) {
	if (len > 2) {
		double result = 0;
		for (int i = 0; i < len; i++)
		{
			double a = 1;
			for (int j = i; j < len + i; j++) {
				if (j >= len)
					a *= mat[j - i][j - len];
				else
					a *= mat[j - i][j];
			}
			result += a;

			a = 1;
			for (int j = len - 1 - i; j >= -(i); j--) {
				if (j < 0)
					a *= mat[len - j - 1 - i][j + len];
				else
					a *= mat[len - j - 1 - i][j];
			}
			result -= a;
		}

		return result;
	}
	else if (len == 2) {
		return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
	}
};

double *matrixMultiVector(double **A, double *V, unsigned int len) {
	double *vec = new double[len];

	for (int i = 0; i < len; i++) {
		vec[i] = 0;
		for (int j = 0; j < len; j++) {
			vec[i] += A[i][j] * V[j];
		}
	}
	return vec;
}

double *vectorSubtract(double *V1, double *V2, unsigned int len) {
	double *nV = new double[len];
	for (int i = 0; i < len; i++) {
		nV[i] = V1[i] - V2[i];
	}
	return nV;
}

double **matrixWithoutColumnRow(double **M, unsigned int col, unsigned int row, unsigned int len) {
	double **nM = new double*[len - 1];
	for (int i = 0; i < len - 1; i++) {
		nM[i] = new double[len - 1];
	}
	unsigned r = 0, c = 0;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (i != row && j != col) {
				nM[r][c] = M[i][j];
				c++;
				if (c >= len - 1) {
					c = 0; r++;
				}
			}
		}
	}
	return nM;
}

double **inverseJacobian(listDiffFunction **mat, double *x, unsigned int len)
{
	double **nMat = new double*[len];
	for (int i = 0; i < len; i++)
		nMat[i] = new double[len];

	double deta = detMatrix(mat, x, len);
	listDiffFunction **minM;

	double **calculatedMat = new double*[len];
	for (int i = 0; i < len; i++) {
		calculatedMat[i] = new double[len];
		for (int j = 0; j < len; j++)
			calculatedMat[i][j] = mat[i][j](x, j);
	}

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			double **mm = matrixWithoutColumnRow(calculatedMat, j, i, len);
			double d = detMatrix(mm, len - 1);
			nMat[i][j] = pow(-1, i + j)*d/ deta;
		}
	}

	return nMat;
};

double normMax(double *V, unsigned int len) {
	double biggest = fabs(V[0]);
	for (int i = 1; i < len; i++) {
		if (fabs(V[i]) > biggest)
			biggest = fabs(V[i]);
	}
	return biggest;
}


