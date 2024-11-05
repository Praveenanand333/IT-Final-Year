#include <iostream>
#include<bits/stdc++.h>
using namespace std;


vector<vector<char>> generateKeyMatrix(string key) {
    vector<vector<char>> keyMatrix(5, vector<char>(5, ' '));
    vector<bool> used(26, false);
    used['J' - 'A'] = true; 

    int row = 0, col = 0;
    for (char &c : key) {
        if (!isalpha(c)) continue;
        c = toupper(c);
        if (c == 'J') c = 'I'; 

        if (!used[c - 'A']) {
            keyMatrix[row][col] = c;
            used[c - 'A'] = true;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (!used[c - 'A']) {
            keyMatrix[row][col] = c;
            used[c - 'A'] = true;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
    return keyMatrix;
}


string formatText(string text) {
    string formattedText = "";
    text.erase(remove(text.begin(), text.end(), ' '), text.end());
    
    for (size_t i = 0; i < text.length(); i++) {
        char first = toupper(text[i]);
        if (first == 'J') first = 'I';

        formattedText += first;
        if (i + 1 < text.length()) {
            char second = toupper(text[i + 1]);
            if (second == 'J') second = 'I';

            if (first == second) {
                formattedText += 'X'; 
            } else {
                formattedText += second;
                i++;
            }
        }
    }

    if (formattedText.length() % 2 != 0) {
        formattedText += 'X'; 
    }
    return formattedText;
}


pair<int, int> findPosition(char c, const vector<vector<char>>& keyMatrix) {
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (keyMatrix[row][col] == c) {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}


string encrypt(string text, const vector<vector<char>>& keyMatrix) {
    string ciphertext = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        auto [row1, col1] = findPosition(text[i], keyMatrix);
        auto [row2, col2] = findPosition(text[i + 1], keyMatrix);

        if (row1 == row2) { 
            ciphertext += keyMatrix[row1][(col1 + 1) % 5];
            ciphertext += keyMatrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) { 
            ciphertext += keyMatrix[(row1 + 1) % 5][col1];
            ciphertext += keyMatrix[(row2 + 1) % 5][col2];
        } else { 
            ciphertext += keyMatrix[row1][col2];
            ciphertext += keyMatrix[row2][col1];
        }
    }
    return ciphertext;
}


string decrypt(string text, const vector<vector<char>>& keyMatrix) {
    string plaintext = "";
    for (size_t i = 0; i < text.length(); i += 2) {
        auto [row1, col1] = findPosition(text[i], keyMatrix);
        auto [row2, col2] = findPosition(text[i + 1], keyMatrix);

        if (row1 == row2) { 
            plaintext += keyMatrix[row1][(col1 + 4) % 5];
            plaintext += keyMatrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) { 
            plaintext += keyMatrix[(row1 + 4) % 5][col1];
            plaintext += keyMatrix[(row2 + 4) % 5][col2];
        } else { 
            plaintext += keyMatrix[row1][col2];
            plaintext += keyMatrix[row2][col1];
        }
    }
    return plaintext;
}

int main() {
    string key, plaintext;
    cout << "Enter key: ";
    getline(cin, key);
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    vector<vector<char>> keyMatrix = generateKeyMatrix(key);
    string formattedText = formatText(plaintext);
    string ciphertext = encrypt(formattedText, keyMatrix);
    string decryptedText = decrypt(ciphertext, keyMatrix);

    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
