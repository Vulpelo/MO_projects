#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;


template <typename T>
class Difference {
private:
	T h;

public:
	T function(T x) {
		return cos(x / 2.0);
	}
	T diff(T x) {
		return -(sin(x / 2.0) / 2.0);
	}


	Difference(T h) : h(h) {}
	~Difference() {}

	void setH(T h) {
		this->h = h;
	}
	T getH() {
		return h;
	}

	T forward(T x) {
		return (function(x+h) - function(x)) / h;
	}
	T forward3p(T x) {
		return (-3.0*function(x) + 4.0*function(x+h) - function(x+2.0*h)) / (2.0*h);
	}
	T backward(T x) {
		return (function(x) - function(x - h)) / h;
	}
	T backward3p(T x) {
		return (function(x-2.0*h) - 4.0*function(x-h) - 3.0*function(x)) / (2.0*h);
	}
	T central(T x) {
		return (function(x+h) - function(x-h)) / (2*h);
	}
};

char* toChar(string text) {
	char *nam = new char[text.length()];
	for (int i = 0; i <= text.length(); i++)
		nam[i] = text[i];
	return nam;
};

char* toChar(string text, string middle ,string end) {
	char *nam = new char[text.length() + middle.length() + end.length()];
	int i = 0;
	for (i = i; i < text.length(); i++)
		nam[i] = text[i];
	for (i = i; i < text.length() + middle.length(); i++)
		nam[i] = middle[i - text.length()];
	for (i = i; i <= text.length() + middle.length() + end.length(); i++)
		nam[i] = end[i - text.length() - middle.length()];
	return nam;
};

template <typename T>
void calculateError(Difference<T> &d, T *x, unsigned int len) {
	FILE *wyj = fopen(toChar("dane_", typeid(T).name(), ".txt"), "w");
	FILE *wyjRoz = fopen(toChar("roznice_", typeid(T).name(), ".txt"), "w");

	unsigned int n = 10;

	d.setH(T(0.1));
	cout << typeid(T).name() << endl;
	printf("%7s|%14s|%14s|%14s|%14s|%14s|%14s|%14s\n", "h", "PtP-F", "PtP - F3p", "PtS - F", "PtS - C", "PtS - B", "PtK - B", "PtK - B3p");
	fprintf(wyj,"%7s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\t%14s\n", "h", "PtP-F", "PtP - F3p", "PtS - F", "PtS - C", "PtS - B", "PtK - B", "PtK - B3p");

	T ptp_f = 0;
	T ptp_f3p = 0;
	T pts_f = 0;
	T pts_c = 0;
	T pts_b = 0;
	T ptk_b = 0;
	T ptk_b3p = 0;
	double h = 0;
	for (int i = 0; i < n; i++) 
	{
		if (i == 1) {
			h = d.getH();
			ptp_f = log10(fabs(d.diff(x[0]) - d.forward(x[0])));
			ptp_f3p = log10(fabs(d.diff(x[0]) - d.forward3p(x[0])));
			pts_f = log10(fabs(d.diff(x[1]) - d.forward(x[1])));
			pts_c = log10(fabs(d.diff(x[1]) - d.central(x[1])));
			pts_b = log10(fabs(d.diff(x[1]) - d.backward(x[1])));
			ptk_b = log10(fabs(d.diff(x[2]) - d.backward(x[2])));
			ptk_b3p = log10(fabs(d.diff(x[2]) - d.backward3p(x[2])));
		}
		else if (i == 2) {
			double xxxx = log10(h) - log10(d.getH());
			ptp_f = fabs( (ptp_f - log10(fabs(d.diff(x[0]) - d.forward(x[0])))) / xxxx);
			ptp_f3p = fabs((ptp_f3p - log10(fabs(d.diff(x[0]) - d.forward3p(x[0])))) / xxxx);
			pts_f = fabs((pts_f - log10(fabs(d.diff(x[1]) - d.forward(x[1])))) / xxxx);
			pts_c = fabs((pts_c - log10(fabs(d.diff(x[1]) - d.central(x[1])))) / xxxx);
			pts_b = fabs((pts_b - log10(fabs(d.diff(x[1]) - d.backward(x[1])))) / xxxx);
			ptk_b = fabs((ptk_b - log10(fabs(d.diff(x[2]) - d.backward(x[2])))) / xxxx);
			ptk_b3p = fabs((ptk_b3p - log10(fabs(d.diff(x[2]) - d.backward3p(x[2])))) / xxxx);

			fprintf(wyjRoz, "%+.0e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\n",
				d.getH(), ptp_f, ptp_f3p, pts_f, pts_c, pts_b, ptk_b, ptk_b3p);
		}
		printf("%+.0e | %+.5e | %+.5e | %+.5e | %+.5e | %+.5e | %+.5e | %+.5e\n",
			d.getH(),
			fabs(d.diff(x[0]) - d.forward(x[0])),
			fabs(d.diff(x[0]) - d.forward3p(x[0])),

			fabs(d.diff(x[1]) - d.forward(x[1])),
			fabs(d.diff(x[1]) - d.central(x[1])),
			fabs(d.diff(x[1]) - d.backward(x[1])),

			fabs(d.diff(x[2]) - d.backward(x[2])),
			fabs(d.diff(x[2]) - d.backward3p(x[2]))
		);

		fprintf(wyj, "%+.0e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\t%+.5e\n",
			d.getH(),
			fabs(d.diff(x[0]) - d.forward(x[0])),
			fabs(d.diff(x[0]) - d.forward3p(x[0])),

			fabs(d.diff(x[1]) - d.forward(x[1])),
			fabs(d.diff(x[1]) - d.central(x[1])),
			fabs(d.diff(x[1]) - d.backward(x[1])),

			fabs(d.diff(x[2]) - d.backward(x[2])),
			fabs(d.diff(x[2]) - d.backward3p(x[2]))
		);
		d.setH(d.getH() * T(0.1));
	}

	fclose(wyj);
	fclose(wyjRoz);
}

template <typename T>
void calculate(Difference<T> &d, T *x, unsigned int len) {
	unsigned int n = 10;

	d.setH(T(0.1));
	cout << endl << typeid(T).name(); 
	printf(": dokladny wynik: x0:%+.5e | x1:%+.5e | x2:%+.5e\n", d.diff(x[0]), d.diff(x[1]), d.diff(x[2]) );
	printf("%7s|%14s|%14s|%14s|%14s|%14s|%14s|%14s|\n", "h", "PtP-F", "PtP - F3p", "PtS - F", "PtS - C", "PtS - B", "PtK - B", "PtK - B3p");

	for (int i = 0; i < n; i++) {
		printf("%+.0e | %+.5e | %+.5e | %+.5e | %+.5e | %+.5e | %+.5e | %+.5e\n",
			d.getH(),
			d.forward(x[0]),
			d.forward3p(x[0]),

			d.forward(x[1]),
			d.central(x[1]),
			d.backward(x[1]),

			d.backward(x[2]),
			d.backward3p(x[2])
		);

		d.setH(d.getH() * T(0.1));
	}
}


int main() {
	double *D = new double[3];
	D[0] = 0; D[1] = M_PI_2; D[2] = M_PI;
	Difference<double> DD(1.0);
	calculate<double>(DD, D, 3);
	calculateError<double>(DD, D, 3);

	float *F = new float[3];
	F[0] = 0; F[1] = M_PI_2; F[2] = M_PI;
	Difference<float> FF(1.0);
	calculate<float>(FF, F, 3);
	calculateError<float>(FF, F, 3);

	return 0;
}