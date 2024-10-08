#include <iostream>
#include <string>
using namespace std;

// Function to remove spaces from the key
string prepareKey(string key, int msgLength) {
    string newKey = key;
    while (newKey.length() < msgLength) {
        newKey += key; // Repeat the key until it's the same length as the message
    }
    return newKey.substr(0, msgLength); // Trim the key to match the message length
}

// Function to encrypt the message
string encryptVigenere(string message, string key) {
    string cipherText = "";
    string preparedKey = prepareKey(key, message.length());
    
    for (int i = 0; i < message.length(); i++) {
        if (message[i] != ' ') {
            char encryptedChar = (message[i] + preparedKey[i] - 2 * 'A') % 26 + 'A'; // Encrypt
            cipherText += encryptedChar;
        } else {
            cipherText += message[i]; // Preserve spaces
        }
    }
    
    return cipherText;
}

// Function to decrypt the message
string decryptVigenere(string cipherText, string key) {
    string message = "";
    string preparedKey = prepareKey(key, cipherText.length());
    
    for (int i = 0; i < cipherText.length(); i++) {
        if (cipherText[i] != ' ') {
            char decryptedChar = (cipherText[i] - preparedKey[i] + 26) % 26 + 'A'; // Decrypt
            message += decryptedChar;
        } else {
            message += cipherText[i]; // Preserve spaces
        }
    }
    
    return message;
}

int main() {
    string message = "ATTACKATDAWN";
    string key = "LEMON";

    string cipherText = encryptVigenere(message, key);
    cout << "Encrypted Message: " << cipherText << endl;

    string decryptedText = decryptVigenere(cipherText, key);
    cout << "Decrypted Message: " << decryptedText << endl;

    return 0;
}
