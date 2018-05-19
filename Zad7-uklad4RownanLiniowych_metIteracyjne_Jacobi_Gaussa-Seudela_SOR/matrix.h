#pragma once


class Matrix {
private:
	unsigned int len;
	double **M;

public:
	Matrix() : M(NULL), len(0) {}
	Matrix(const Matrix &C) {
		this->len = C.len;
		M = new double*[len];
		for (int i = 0; i < len; i++) {
			this->M[i] = new double[len];
			for (int j = 0; j < len; j++)
				this->M[i][j] = C.M[i][j];
		}
	}
	Matrix(double **A, unsigned int len) {
		M = new double*[len];
		for (int i = 0; i < len; i++) {
			this->M[i] = new double[len];
			for (int j = 0; j < len; j++)
				this->M[i][j] = A[i][j];
		}
		this->len = len;
	}

	unsigned int getLen() {
		return this->len;
	}

	void upper(bool diagonalZero = true) {
		for (int i = len-1; i > 0; i--)
			for (int j = 0; j < i; j++)
				M[i][j] = 0;

		if (diagonalZero)
			for (int i = 0; i < len; i++)
				M[i][i] = 0;	
	}

	void lower(bool diagonalZero = true) {
		for (int i = 0; i < len; i++)
			for (int j = i+1; j < len; j++)
				M[i][j] = 0;

		if (diagonalZero)
			for (int i = 0; i < len; i++)
				M[i][i] = 0;
	}

	void diagonal() {
		lower(false);
		upper(false);
	}

	double det() {
		if (len > 2) {
			double result = 0;
			for (int i = 0; i < len; i++)
			{
				double a = 1;
				for (int j = i; j < len + i; j++) {
					if (j >= len)
						a *= M[j - i][j - len];
					else
						a *= M[j - i][j];
				}
				result += a;

				a = 1;
				for (int j = len - 1 - i; j >= -(i); j--) {
					if (j < 0)
						a *= M[len - j - 1 - i][j + len];
					else
						a *= M[len - j - 1 - i][j];
				}
				result -= a;
			}

			return result;
		}
		else if (len == 2) {
			return M[0][0] * M[1][1] - M[1][0] * M[0][1];
		}
	};

	Matrix deleteColumnRow(unsigned int col, unsigned int row) {
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
		return Matrix(nM, this->len - 1);
	};

	void inverse() {
		double **nMat = new double*[len];
		for (int i = 0; i < len; i++)
			nMat[i] = new double[len];

		double deta = this->det();

		double **calculatedMat = new double*[len];
		for (int i = 0; i < len; i++) {
			calculatedMat[i] = new double[len];
			for (int j = 0; j < len; j++)
				calculatedMat[i][j] = M[i][j];
		}

		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				Matrix mm = this->deleteColumnRow(j, i);
				double d = mm.det();
				nMat[i][j] = pow(-1, i + j)*d / deta;
			}
		}
		delete this->M;
		this->M = nMat;
	};

	const Matrix operator+(const Matrix &A) const {
		if (A.len == this->len) {
			double **nC = new double*[this->len];
			for (int i = 0; i < len; i++) {
				nC[i] = new double[len];
				for (int j = 0; j < len; j++)
					nC[i][j] = M[i][j] + A.M[i][j];
			}

			return Matrix(nC, this->len);
		}
	};

	const Matrix operator-(const Matrix &A) const {
		if (A.len == this->len) {
			double **nC = new double*[this->len];
			for (int i = 0; i < len; i++) {
				nC[i] = new double[len];
				for (int j = 0; j < len; j++)
					nC[i][j] = M[i][j] - A.M[i][j];
			}

			return Matrix(nC, this->len);
		}
	};

	const Matrix operator*(const Matrix &A) const {
		if (A.len == this->len) {

			double **nC = new double*[this->len];
			for (int i = 0; i < len; i++) {
				nC[i] = new double[len];
				for (int j = 0; j < len; j++) {

					nC[i][j] = 0;
					for (int g = 0; g < len; g++)
						nC[i][j] += M[i][g] * A.M[g][j];

				}
			}
			return Matrix(nC, this->len);
		}
	};

	double *operator*(const double *V) const {
		double *vec = new double[this->len];
		

		for (int i = 0; i < len; i++) {
			vec[i] = 0;
			for (int j = 0; j < len; j++) {
				vec[i] += M[i][j] * V[j];
			}
		}
		return vec;
	};

	const Matrix operator*(double L) const {
		double **nC = new double*[this->len];
		for (int i = 0; i < len; i++) {
			nC[i] = new double[len];
			for (int j = 0; j < len; j++) {
				nC[i][j] = this->M[i][j];
			}
		}

		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				nC[i][j] *= L;
			}
		}
		return Matrix(nC, this->len);
	};


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


double *vectorSubtract(double *V1, double *V2, unsigned int len) {
	double *nV = new double[len];
	for (int i = 0; i < len; i++) {
		nV[i] = V1[i] - V2[i];
	}
	return nV;
}


void printVector(char *name, double *x, unsigned int len) {
	printf("%s=[ ", name);
	for (int i = 0; i < len - 1; i++)
		printf("%+.5e; ", x[i]);
	printf("%+.5e]", x[len - 1]);
}

double normMax(double *V, unsigned int len) {
	double biggest = fabs(V[0]);
	for (int i = 1; i < len; i++) {
		if (fabs(V[i]) > biggest)
			biggest = fabs(V[i]);
	}
	return biggest;
}
