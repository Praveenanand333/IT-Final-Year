#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
    string plain;
    cin >> plain;
    int key;
    cin >> key;
    
    key = (key % 26 + 26) % 26; // Normalize key to handle negative and large values
    string cipher;
    
    for (int i = 0; i < plain.length(); i++) {
        if (isalpha(plain[i])) {
            if (isupper(plain[i])) {
                cipher += char(int(plain[i] + key - 65) % 26 + 65);
            } else if (islower(plain[i])) {
                cipher += char(int(plain[i] + key - 97) % 26 + 97);
            }
        } else {
            cipher += plain[i]; // Directly add non-alphabet characters
        }
    }

    cout << "The encrypted text is: " << cipher << endl;
}
