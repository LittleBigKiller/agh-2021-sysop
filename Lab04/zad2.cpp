#include <iostream>
#include <new>
#include <stdlib.h>

using namespace std;

#define ROWS 256
#define COLS 1024

int main(int argc, char *argv[]) {

	if (argc != 2) {
		cout << "Poprawne wywołanie: ./zad2 <pamięć w M (około)>" << endl; 
	}

	int plen = atoi(argv[1]);

	plen = plen - 2 - 3*((int)(plen / 512));

	cout << "ENTER, aby zająć pamięć" << endl;

	cin.get();

	cout << "Zajmowanie pamięci..." << endl;
	
	int **arr[plen];
	
	for (int i = 0; i < plen; i++) {
		arr[i] = new int*[ROWS];
		for (int j = 0; j < ROWS; j++) {
			arr[i][j] = new int[COLS];
			for (int k = 0; k < COLS; k++) {
				arr[i][j][k] = ROWS*COLS;
			}
		}
	}

	cout << "Zakończono zajmowanie pamięci" << endl;
	cout << "ENTER, aby wyczyścić pamięć" << endl;

	cin.get();

	cout << "Czyszczenie pamięci..." << endl;

	for (int i = 0; i < plen; i++) {
		for (int j = 0; j < ROWS; j++) {
			delete[] arr[i][j];
		}
		delete[] arr[i];
	}

	cout << "Pamięć wyczyszczona" << endl;
	cout << "ENTER, aby zakończyć" << endl;

	cin.get();
}
