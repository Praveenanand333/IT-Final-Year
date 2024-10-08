#include <iostream>
#include <vector>
#include <string>

using namespace std;

class RC4 {
private:
    vector<int> S;
    int i, j;

public:
    RC4(const string& key) {
        S.resize(256);
        for (int k = 0; k < 256; k++) {
            S[k] = k;
        }

        j = 0;
        for (int k = 0; k < 256; k++) {
            j = (j + S[k] + key[k % key.length()]) % 256;
            swap(S[k], S[j]);
        }

        i = 0;
        j = 0;
    }

    string encrypt(const string& plaintext) {
        string ciphertext;
        for (char c : plaintext) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            swap(S[i], S[j]);
            int K = S[(S[i] + S[j]) % 256];
            ciphertext += c ^ K;
        }
        return ciphertext;
    }

    string decrypt(const string& ciphertext) {
        return encrypt(ciphertext); // RC4 is symmetric, so encryption and decryption are the same
    }
};

int main() {
    string key;
    cout << "Enter the key: ";
    cin >> key;

    string plaintext;
    cout << "Enter the plaintext: ";
    cin.ignore(); // To ignore the newline character left in the buffer
    getline(cin, plaintext);

    RC4 rc4(key);
    string ciphertext = rc4.encrypt(plaintext);

    cout << "Ciphertext (in hex): ";
    for (char c : ciphertext) {
        printf("%02x ", (unsigned char)c);
    }
    cout << endl;

    string decryptedText = rc4.decrypt(ciphertext);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
