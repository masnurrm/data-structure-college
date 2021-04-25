#include <iostream>

using namespace std;

int main () {
    int n, m, num = 1;
    cout << "Masukkan ordo matriks: ";
    cin >> n >> m;
    int matriks[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n-i; j++) {
            matriks[i][j] = num++;
        }
        
        for (int j = i+1; j < n-i-1; j++) {
            matriks[j][n-i-1] = num++;
        }
        for (int j = n-i-2; j >= i; j--) {
            matriks[n-i-1][j] = num++;
        }
        for (int j = n-2-i; j > i; j--) {
            matriks[j][i] = num++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}