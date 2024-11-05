#include <iostream>
#include <vector>
using namespace std;

void KSA(vector<int> &S, const string &key) {
    int keyLength = key.size();
    int j = 0;
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keyLength]) % 256;
        swap(S[i], S[j]);
    }
}
string PRGA(vector<int> &S, const string &data) {
    int i = 0, j = 0;
    string output = data;
    for (int k = 0; k < data.size(); k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int keyStream = S[(S[i] + S[j]) % 256];
        output[k] = data[k] ^ keyStream;
    }
    return output;
}


string RC4(const string &key, const string &data) {
    vector<int> S(256);
    KSA(S, key);           
    return PRGA(S, data);   
}

int main() {
    string key = "secret_key";
    string plaintext = "Hello, World!";

    
    string ciphertext = RC4(key, plaintext);
    cout << "Ciphertext: ";
    for (unsigned char c : ciphertext) {
        cout<<c;
    }
    cout << endl;

    
    string decrypted = RC4(key, ciphertext);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
