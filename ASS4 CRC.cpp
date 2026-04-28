#include <iostream>
using namespace std;

string xorOperation(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        if (a[i] == b[i])
            result += '0';
        else
            result += '1';
    }
    return result;
}

string divide(string dividend, string divisor) {
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);

    while (pick < dividend.length()) {

        if (temp[0] == '1')
            temp = xorOperation(divisor, temp) + dividend[pick];
        else
            temp = xorOperation(string(pick, '0'), temp) + dividend[pick];

        pick++;
    }

    if (temp[0] == '1')
        temp = xorOperation(divisor, temp);
    else
        temp = xorOperation(string(pick, '0'), temp);

    return temp;
}

int main() {
    string data, generator;

    cout << "Enter Data: ";
    cin >> data;

    cout << "Enter Generator: ";
    cin >> generator;

    int g = generator.length();

    // Sender Side
    string appended = data + string(g - 1, '0');
    string remainder = divide(appended, generator);

    string codeword = data + remainder;

    cout << "\nSender Side" << endl;
    cout << "CRC Remainder: " << remainder << endl;
    cout << "Transmitted Codeword: " << codeword << endl;

    // Ask user if Error should be introduced or not
    string choice;
    cout << "\nDo you want to introduce error? (yes/no): ";
    cin >> choice;

    string received;
    if (choice == "yes" || choice == "Yes") {
        cout << "Enter Received Codeword with Error: ";
        cin >> received;
    } else {
        received = codeword;
    }

    // Receiver Side
    string check = divide(received, generator);

    cout << "\nReceiver Side" << endl;

    if (check.find('1') != string::npos)
        cout << "Error detected in received data." << endl;
    else
        cout << "No error detected. Data received correctly." << endl;

    return 0;
}