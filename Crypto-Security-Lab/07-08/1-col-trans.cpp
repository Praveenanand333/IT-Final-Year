 #include <iostream>
#include<bits/stdc++.h>
using namespace std;
string encrypt(const string &plaintext, const string &key) {
    int numRows = (plaintext.size() + key.size() - 1) / key.size();
    vector<string> grid(numRows, string(key.size(), ' '));
    int index = 0;
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < key.size(); ++c) {
            if (index < plaintext.size()) {
                grid[r][c] = plaintext[index++];
            }
        }
    }
    vector<int> order(key.size());
    for (int i = 0; i < key.size(); ++i) {
        order[i] = i;
    }
    sort(order.begin(), order.end(), [&key](int a, int b) {
        return key[a] < key[b];
    });
    string ciphertext;
    for (int c : order) {
        for (int r = 0; r < numRows; ++r) {
            if (grid[r][c] != ' ') {
                ciphertext += grid[r][c];
            }
        }
       
    }

    return ciphertext;
}
string decrypt(const string &ciphertext, const string &key) {
    int numRows = (ciphertext.size() + key.size() - 1) / key.size(); 
    int numCols = key.size();
    vector<int> order(numCols);
    for (int i = 0; i < numCols; ++i) {
        order[i] = i;
    }
    sort(order.begin(), order.end(), [&key](int a, int b) {
        return key[a] < key[b];
    });
    vector<string> grid(numRows, string(numCols, ' '));
    int index = 0;
    for (int c : order) {
        for (int r = 0; r < numRows; ++r) {
            if (index < ciphertext.size()) {
                grid[r][c] = ciphertext[index++];
            }
        }
    }
    string plaintext;
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            if (grid[r][c] != ' ') {
                plaintext += grid[r][c];
            }
        }
    }

    return plaintext;
}

int main() {
    string plaintext = "This-is-a-secretmessage";
    string key = "KEY";

    string encrypted = encrypt(plaintext, key);
    string decrypted = decrypt(encrypted, key);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
