#include <iostream>
#include <cmath>
using namespace std;

int main() {
    string data;
    cout << "Enter data bits : ";
    cin >> data;

    int m = data.length();
    int r = 0;

    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    int total = m + r;
    int h[100];

    cout << "\nNumber of parity bits required: " << r << endl;

    int j = 0, k = 0;
    for (int i = 1; i <= total; i++) {
        if (pow(2, j) == i) {
            h[i] = 0; 
            j++;
        } else {
            h[i] = data[k++] - '0';
        }
    }

    cout << "\nPositions: ";
    for (int i = 1; i <= total; i++) cout << i << " ";
    
    cout << "\nInitial (with parity positions): ";
    for (int i = 1; i <= total; i++) cout << h[i] << " ";

    cout << "\n\nCalculating Parity Bits:\n";
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int sum = 0;

        for (int k = 1; k <= total; k++) {
            if ((k >> i) & 1) {
                sum += h[k];
            }
        }

        h[pos] = sum % 2;
        cout << "P" << pos << " = " << h[pos] << endl;
    }

    cout << "\nGenerated Hamming Code: ";
    for (int i = 1; i <= total; i++) cout << h[i];
    cout << endl;

    cout << "\n--- Receiver Side ---";
    cout << "\n1. Introduce Error\n2. No Error\nEnter choice: ";

    int choice;
    cin >> choice;

    int rcv[100];

    if (choice == 1) {
        string received;
        cout << "Enter received code: ";
        cin >> received;

        for (int i = 1; i <= total; i++) {
            rcv[i] = received[i - 1] - '0';
        }
    } else {
        for (int i = 1; i <= total; i++) {
            rcv[i] = h[i];
        }
    }

    int errorPos = 0;

    for (int i = 0; i < r; i++) {
        int sum = 0;

        for (int k = 1; k <= total; k++) {
            if ((k >> i) & 1) {
                sum += rcv[k];
            }
        }

        if (sum % 2 != 0) {
            errorPos += pow(2, i);
        }
    }

    if (errorPos == 0) {
        cout << "\nNo error detected in received code.\n";
    } else {
        cout << "\nError detected at position: " << errorPos << endl;

        rcv[errorPos] = (rcv[errorPos] == 0) ? 1 : 0;

        cout << "✔ Corrected Code: ";
        for (int i = 1; i <= total; i++) cout << rcv[i];
        cout << endl;
    }

    return 0;
}