#pragma once


class Matrix {
private:
	double *l;
	double *d;
	double *u;

	double *b;
	unsigned int len;

	void thomas3M() {
		for (unsigned int i = 1; i < len; i++)
			set(i,i, get(i, i) - get(i, i-1)*1.0 / get(i-1, i-1) * get(i-1, i) );
	}

	void thomas3B() {
		for (int i = 1; i < len; i++)
			b[i] = b[i] - get(i, i-1) * 1.0 / get(i-1, i-1) * b[i - 1];
	}

public:
	Matrix(double*l, double*u, double*d, double *b, unsigned int len) {
		this->b = new double[len];
		this->u = new double[len-1];
		this->d = new double[len];
		this->l = new double[len-1];
		for (int i = 0; i < len; i++) {
			this->d[i] = d[i];
			this->b[i] = b[i];
		}
		for (int i = 0; i < len - 1; i++) {
			this->u[i] = u[i];
			this->l[i] = l[i];
		}

		this->len = len;
	}

	double **getMatrix() {
		double **mat = new double*[len];
		for (int i = 0; i < len; i++) {
			mat[i] = new double[len];
			for (int j = 0; j < len; j++)
				mat[i][j] = 0;
		}
		for (int i = 0; i < len; i++) {
			mat[i][i] = d[i];
		}
		for (int i = 1; i < len; i++) {
			mat[i][i-1] = l[i-1];
		}
		for (int i = 0; i < len-1; i++) {
			mat[i][i+1] = u[i];
		}

		return mat;
	}

	double *getB() {
		return this->b;
	}

	void set(unsigned int row, unsigned int col, double var) {
		if (fabs(row - col) == 0)
			d[row] = var;
		if (row - col == 1)
			l[col] = var;
		if (row - col == -1)
			u[row] = var;
	}


	double get(unsigned int row, unsigned int col) {
		if (fabs(row - col) == 0)
			return d[row];
		if (row - col == 1)
			return l[col];
		if (row - col == -1)
			return u[row];
		return 0;
	}

	void print(char *name) {
		double **mat = this->getMatrix();
		printf("%s=[\n", name);
		for (int i = 0; i < len; i++) {
			printf("[ ");
			for (int j = 0; j < len - 1; j++) {
				printf("%+.5e; ", mat[i][j]);
			}
			printf("%+.5e]\n", mat[i][len - 1]);

		}
		printf("]\n");
	}

	double *thomas3() {
		thomas3B();
		thomas3M();
		
		double *x = new double[len];
		x[len - 1] = 1.0 / d[len - 1] * b[len - 1];
		for (int i = len-2; i >= 0; i--)
			x[i] = 1.0 / d[i] * (b[i] - u[i] * x[i + 1]);

		return x;
	}


	~Matrix() {
		delete u;
		delete l;
		delete d;
		delete b;
	}
};


void printVector(char *name, double *x, unsigned int len) {
	printf("%s=[ ", name);
	for (int i = 0; i < len - 1; i++)
		printf("%+.5e; ", x[i]);
	printf("%+.5e]", x[len - 1]);
}


void matrixMultiVector(double **A, double *x, unsigned int len) {
	double *b = new double[len];

	for (int i = 0; i < len; i++) {
		double sum = 0;
		for (int j = 0; j < len; j++) {
			sum += A[i][j] * x[j];
		}
		b[i] = sum;
	}

	printVector("\n\nTest po pomnozeniu A*x = B\nB", b, len);
}

