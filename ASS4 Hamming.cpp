#include <iostream>
#include <cmath>
using namespace std;

// Convert character to binary string (8-bit)
string charToBinary(char ch) {
    string bin = "";
    int val = ch;

    for (int i = 7; i >= 0; i--) {
        if (val & (1 << i))
            bin += '1';
        else
            bin += '0';
    }
    return bin;
}

int main() {
    string data;
    int choice;

    cout << "1. Enter Binary Data\n2. Enter Character\nChoice: ";
    cin >> choice;

    if (choice == 2) {
        char ch;
        cout << "Enter character: ";
        cin >> ch;
        data = charToBinary(ch);
        cout << "Binary of " << ch << " = " << data << endl;
    } else {
        cout << "Enter binary data: ";
        cin >> data;
    }

    int m = data.length();
    int r = 0;

    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    int total = m + r;
    int h[100];

    cout << "\nParity bits required: " << r << endl;

    int j = 0, k = 0;
    for (int i = 1; i <= total; i++) {
        if (i == pow(2, j)) {
            h[i] = 0;
            j++;
        } else {
            h[i] = data[k++] - '0';
        }
    }

    cout << "\nInitial code: ";
    for (int i = 1; i <= total; i++) cout << h[i];

    cout << "\n\nCalculating Parity Bits:\n";

    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int sum = 0;

        for (int j = 1; j <= total; j++) {
            if (j & pos) {
                sum += h[j];
            }
        }

        h[pos] = sum % 2;
        cout << "P" << pos << " = " << h[pos] << endl;
    }

    cout << "\nGenerated Hamming Code: ";
    for (int i = 1; i <= total; i++) cout << h[i];
    cout << endl;

    // Receiver side
    cout << "\n--- Receiver Side ---";
    cout << "\nEnter received code: ";

    string received;
    cin >> received;

    int rcv[100];

    for (int i = 1; i <= total; i++) {
        rcv[i] = received[i - 1] - '0';
    }

    int errorPos = 0;

    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int sum = 0;

        for (int j = 1; j <= total; j++) {
            if (j & pos) {
                sum += rcv[j];
            }
        }

        if (sum % 2 != 0) {
            errorPos += pos;
        }
    }

    if (errorPos == 0) {
        cout << "\nNo error detected\n";
    } else {
        cout << "\nError at position: " << errorPos << endl;

        rcv[errorPos] ^= 1;

        cout << "Corrected Code: ";
        for (int i = 1; i <= total; i++) cout << rcv[i];
        cout << endl;
    }

    return 0;
}
