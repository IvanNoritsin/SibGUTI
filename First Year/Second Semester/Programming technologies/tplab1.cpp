#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    int N, K, j = 0, maxX = -1000, maxY = -1000, minX = 1000, minY = 1000;
    cout << "Size of the array X: ";
    cin >> N;
    K = N / 2;
    int* X = new int[N];
    int* Y = new int[K];

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        X[i] = rand() % 201 - 100;
    }

    cout << "Array X: ";
    for (int i = 0; i < N; i++) {
        cout << X[i] << " ";
    }

    cout << "\n";

    for (int i = 1; i < N; i = i + 2) {
        Y[j] = X[i];
        j++;
    }

    cout << "Array Y: ";
    for (int i = 0; i < K; i++) {
        cout << Y[i] << " ";
    }

    cout << "\n";

    for (int i = 0; i < N; i++) {
        if (X[i] > maxX) {
            maxX = X[i];
        }
    }

    for (int i = 0; i < K; i++) {
        if (Y[i] > maxY) {
            maxY = Y[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (X[i] < minX) {
            minX = X[i];
        }
    }

    for (int i = 0; i < K; i++) {
        if (Y[i] < minY) {
            minY = Y[i];
        }
    }


    int k = 0;
    for (int i = 0; i < N; i++) {
        if (X[i] != maxX && X[i] != minX) {
            X[k++] = X[i];
        }

    }

    N = k;


    cout << "Array X without MAX and MIN: ";
    for (int i = 0; i < N; i++) {
        cout << X[i] << " ";
    }

    cout << "\n";

    int m = 0;
    for (int i = 0; i < K; i++) {
        if (Y[i] != maxY && Y[i] != minY) {
            Y[m++] = Y[i];
        }
    }

    K = m;


    cout << "Array Y without MAX and MIN: ";
    for (int i = 0; i < K; i++) {
        cout << Y[i] << " ";
    }

    delete[] X;
    delete[] Y;

    return 0;
}