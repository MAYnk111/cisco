#include <iostream>
using namespace std;

// Convert character to binary (8-bit)
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

// XOR operation
string xorOp(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        if (a[i] == b[i])
            result += '0';
        else
            result += '1';
    }
    return result;
}

// CRC Division
string crcDivide(string data, string key) {
    int k = key.length();
    string temp = data.substr(0, k);

    for (int i = k; i < data.length(); i++) {
        if (temp[0] == '1')
            temp = xorOp(key, temp) + data[i];
        else
            temp = xorOp(string(k, '0'), temp) + data[i];
    }

    if (temp[0] == '1')
        temp = xorOp(key, temp);
    else
        temp = xorOp(string(k, '0'), temp);

    return temp;
}

int main() {
    int choice;
    string data;

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

    string key;
    cout << "Enter generator polynomial (e.g. 1011 or 10011): ";
    cin >> key;

    int k = key.length();

    // Append zeros
    string appended = data + string(k - 1, '0');

    // Get remainder
    string remainder = crcDivide(appended, key);

    // Transmitted data
    string transmitted = data + remainder;

    cout << "\nTransmitted Data: " << transmitted << endl;

    // Introduce error
    int pos;
    cout << "Enter position to introduce error: ";
    cin >> pos;

    transmitted[pos - 1] = (transmitted[pos - 1] == '0') ? '1' : '0';

    cout << "Received Data: " << transmitted << endl;

    // Check error
    string check = crcDivide(transmitted, key);

    if (check.find('1') != string::npos)
        cout << "Error detected\n";
    else
        cout << "No error detected\n";

    return 0;
}
