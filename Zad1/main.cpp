#include <iostream>
#include <string>

using namespace std;

template <typename T>
void mantysa(string text, T number) {
	int rounds = -1;
	T prev = number;
	while (number + 1 > 1) {
		prev = number;
		number = number / 2;
		rounds++;
	};
	cout << text << endl;
	cout << "Obroty/il.znakow mantysy: " << rounds << endl;
	cout << "Wartosc minimalna: " << prev << endl;

	if(32 - rounds > 0)
		cout << "Ilosc bitow cechy: " << 32 - rounds - 1 << endl;
	else
		cout << "Ilosc bitow cechy: " << 64 - rounds - 1 << endl;
}



int main() {
	//float number = 1;
	//float prev = number;
	//int rounds = 0;

	//while (number + 1 > 1) {
	//	rounds++;
	//	prev = number;
	//	number = number / 2;
	//};
	//cout << "Float\n";
	//cout << "Obroty/il.znakow mantysy: " << rounds << endl;
	//cout << "Wartosc minimalna: " << prev * 2 << endl;
	//cout << "Ilosc bitow cechy: " << 32 - rounds - 1 << endl;

	//double number2 = 1;
	//prev = number2;

	//rounds = 0;
	//
	//while (number2 + 1 > 1) {
	//	rounds++;
	//	prev = number2;
	//	number2 = number2 / 2;
	//};
	//cout << "Double\n";
	//cout << "Obroty/il.znakow mantysy: " << rounds << endl;
	//cout << "Wartosc minimalna: " << prev * 2 << endl;
	//cout << "Ilosc bitow cechy: " << 64 - rounds - 1 << endl;
	float l1 = 1;
	mantysa<float>("Float", l1);

	double l2 = 1;
	mantysa<double>("Double", l2);


	return 0;
}