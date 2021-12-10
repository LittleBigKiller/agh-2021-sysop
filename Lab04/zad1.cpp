#include <iostream>
#include <new>

using namespace std;

void statyczna();

void dynamiczna();

// vvv WARTOŚCI RSS vvv
//
// htop:
//
// start 	=  1512
// stat		= 10604
// mid		= 10604
// dyn		= 18572
// end		= 10844
//
//
// /proc/[id]/smaps:
//
// start	=  3032
// stat 	= 10844
// mid		= 10844
// dyn		= 18660
// end		= 10844
//

int main() {

	// start
	cin.get();

	statyczna();	
	cout << "usunieta statyczna" << endl;

	// mid
	cin.get();

	dynamiczna();
	cout << "usunieta dynamiczna" << endl;

	// end
	cin.get();
}

void statyczna() {

	cout << "statyczna" << endl;
	// stack
	double tablica[1000000];
	for (int i = 0; i < 1000000; i++) {
		tablica[i] = 2.0;
	}

	// stat
	cin.get();
}

void dynamiczna() {

	cout << "dynamiczna" << endl;
	// heap
	double *tablica = new double[1000000];
	for (int i = 0; i < 1000000; i++) {
		tablica[i] = 3.0;
	}

	// dyna
	cin.get();

	delete[] tablica;
}

