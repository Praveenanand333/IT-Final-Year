#include <iostream>
#include <vector>
using namespace std;


void getKeyMatrix(const string& key, vector<vector<int>>& keyMatrix) {
    int k = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}


int modInverse(int num, int mod) {
    num = num % mod;
    for (int x = 1; x < mod; x++) {
        if ((num * x) % mod == 1)
            return x;
    }
    return -1; 
}


bool inverseKeyMatrix(vector<vector<int>>& keyMatrix, vector<vector<int>>& invKeyMatrix) {
    int det = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % 26;
    if (det < 0) det += 26;  

    int detInv = modInverse(det, 26);  
    if (detInv == -1) return false; 

    
    invKeyMatrix[0][0] = (keyMatrix[1][1] * detInv) % 26;
    invKeyMatrix[0][1] = (-keyMatrix[0][1] * detInv + 26) % 26;
    invKeyMatrix[1][0] = (-keyMatrix[1][0] * detInv + 26) % 26;
    invKeyMatrix[1][1] = (keyMatrix[0][0] * detInv) % 26;

    return true;
}


void encrypt(vector<vector<int>>& cipherMatrix, const vector<vector<int>>& keyMatrix, const vector<vector<int>>& messageVector) {
    for (int i = 0; i < 2; i++) {
        cipherMatrix[i][0] = 0;
        for (int j = 0; j < 2; j++) {
            cipherMatrix[i][0] += keyMatrix[i][j] * messageVector[j][0];
        }
        cipherMatrix[i][0] = cipherMatrix[i][0] % 26;
    }
}


void decrypt(vector<vector<int>>& decryptedMatrix, const vector<vector<int>>& invKeyMatrix, const vector<vector<int>>& cipherMatrix) {
    for (int i = 0; i < 2; i++) {
        decryptedMatrix[i][0] = 0;
        for (int j = 0; j < 2; j++) {
            decryptedMatrix[i][0] += invKeyMatrix[i][j] * cipherMatrix[j][0];
        }
        decryptedMatrix[i][0] = decryptedMatrix[i][0] % 26;
    }
}


void HillCipher(const string& message, const string& key) {
    vector<vector<int>> keyMatrix(2, vector<int>(2));
    getKeyMatrix(key, keyMatrix);

    
    vector<vector<int>> messageVector(2, vector<int>(1));
    messageVector[0][0] = (message[0]) % 65;
    messageVector[1][0] = (message[1]) % 65;

    
    vector<vector<int>> cipherMatrix(2, vector<int>(1));
    encrypt(cipherMatrix, keyMatrix, messageVector);

    string CipherText;
    for (int i = 0; i < 2; i++)
        CipherText += cipherMatrix[i][0] + 65;
    cout << "Ciphertext: " << CipherText << endl;

    
    vector<vector<int>> invKeyMatrix(2, vector<int>(2));
    if (!inverseKeyMatrix(keyMatrix, invKeyMatrix)) {
        cout << "Inverse key matrix does not exist. Decryption not possible." << endl;
        return;
    }

    
    vector<vector<int>> decryptedMatrix(2, vector<int>(1));
    decrypt(decryptedMatrix, invKeyMatrix, cipherMatrix);

    string PlainText;
    for (int i = 0; i < 2; i++)
        PlainText += decryptedMatrix[i][0] + 65;
    cout << "Decrypted Plaintext: " << PlainText << endl;
}

int main() {
    string message = "AI"; 
    string key = "BHAD";   

    cout << "Message: " << message << endl;
    cout << "Key: " << key << endl;

    HillCipher(message, key);
    return 0;
}
