#include <iostream>
#include <string>
#include <numeric> // for gcd
using namespace std;

const int ALPHABET_SIZE = 26;
const int a = 17; // Original multiplier
const int b = 20; // Original shift

string encryptMessage(string msg) {
    string cipher = ""; 
    for (int i = 0; i < msg.length(); i++) {
        if(msg[i] != ' ') 
            cipher += (char) ((((a * (msg[i] - 'A')) + b) % ALPHABET_SIZE) + 'A');
        else
            cipher += msg[i];	 
    }
    return cipher;
}

string decryptCipher(string cipher, int a, int b) {
    string msg = "";
    int a_inv = 0;
    int flag = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        flag = (a * i) % ALPHABET_SIZE;

        if (flag == 1) { 
            a_inv = i;
            break; // Break after finding the modular inverse
        }
    }
    for (int i = 0; i < cipher.length(); i++) {
        if(cipher[i] != ' ')
            msg += (char) (((a_inv * ((cipher[i] - 'A' - b + ALPHABET_SIZE) % ALPHABET_SIZE)) % ALPHABET_SIZE) + 'A');
        else
            msg += cipher[i]; 
    }

    return msg;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void bruteForceAttack(string cipherText) {
    for (int a = 1; a < ALPHABET_SIZE; a++) {
        if (gcd(a, ALPHABET_SIZE) == 1) { // a must be coprime with ALPHABET_SIZE
            for (int b = 0; b < ALPHABET_SIZE; b++) {
                string decryptedText = decryptCipher(cipherText, a, b);
                cout << "a = " << a << ", b = " << b << ": " << decryptedText << endl;
            }
        }
    }
}

int main() {
    string msg = "AFFINE CIPHER";
    string cipherText = encryptMessage(msg);
    cout << "Encrypted Message is: " << cipherText << endl;

    cout << "Brute Force Attack Results: " << endl;
    bruteForceAttack(cipherText);

    return 0;
}
