#include <iostream>
#include <vector>
using namespace std;

void getKeyMatrix(const string& key, vector<vector<int>>& keyMatrix) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

void encrypt(vector<vector<int>>& cipherMatrix,
              const vector<vector<int>>& keyMatrix, 
              const vector<vector<int>>& messageVector) {
    int x, i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            cipherMatrix[i][j] = 0;
            for (x = 0; x < 3; x++) {
                cipherMatrix[i][j] += keyMatrix[i][x] * messageVector[x][j];
            }
            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}

void HillCipher(const string& message, const string& key) {
    vector<vector<int>> keyMatrix(3, vector<int>(3));
    getKeyMatrix(key, keyMatrix);
    
    vector<vector<int>> messageVector(3, vector<int>(1));
    for (int i = 0; i < 3; i++)
        messageVector[i][0] = (message[i]) % 65;

    vector<vector<int>> cipherMatrix(3, vector<int>(1));
    encrypt(cipherMatrix, keyMatrix, messageVector);

    string CipherText;
    for (int i = 0; i < 3; i++)
        CipherText += cipherMatrix[i][0] + 65;

    cout << "Ciphertext: " << CipherText << endl;
}

int main() {
    string message = "EAT";
    string key = "GYBNQKURP";

    HillCipher(message, key);
    return 0;
}
