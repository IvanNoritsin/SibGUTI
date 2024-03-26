#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

int SimpleNumber(int N) {
	if (N == 0 || N == 1) {
		return 0;
	}
	for (int i = 2; i <= sqrt(N); i++)
		if (N % i == 0)
			return 0;
	return 1;
}

void DeleteSimple(int Arr[], int N) {
	int j = 0;
	for (int i = 0; i < N; i++) {
		if (SimpleNumber(Arr[i]) == 0) {
			Arr[j++] = Arr[i];
		}
	}
	N = j;
	for (int i = 0; i < N; i++) {
		cout << Arr[i] << " ";
	}

}

int main() {
	int N;
	cout << "Size of the Array: ";
	cin >> N;
	int *Arr = new int[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		Arr[i] = rand() % 100;
	}
	for (int i = 0; i < N; i++) {
		cout << Arr[i] << " ";
	}
	cout << "\n";
	DeleteSimple(Arr, N);
	
	delete[] Arr;

	return 0;
}