#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// Helper function to fill a grid with plaintext characters
void fillGrid(const string& text, vector<string>& grid, int numRows, int numCols) {
    int index = 0;
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            if (index < text.size()) {
                grid[r][c] = text[index++];
            }
        }
    }
}

// Helper function to extract text from a grid based on column order
string extractTextFromGrid(const vector<string>& grid, const vector<int>& order, int numRows) {
    string text;
    for (int c : order) {
        for (int r = 0; r < numRows; ++r) {
            if (grid[r][c] != ' ') {
                text += grid[r][c];
            }
        }
    }
    return text;
}

// Function to determine the column order based on the key
vector<int> getColumnOrder(const string& key) {
    vector<int> order(key.size());
    for (int i = 0; i < key.size(); ++i) {
        order[i] = i;
    }
    sort(order.begin(), order.end(), [&key](int a, int b) {
        return key[a] < key[b];
    });
    return order;
}

// Encryption function for Double Columnar Transposition Cipher
string encrypt(const string& plaintext, const string& key1, const string& key2) {
    // First columnar transposition
    int numCols1 = key1.size();
    int numRows1 = (plaintext.size() + numCols1 - 1) / numCols1;
    vector<string> grid1(numRows1, string(numCols1, ' '));

    fillGrid(plaintext, grid1, numRows1, numCols1);

    vector<int> order1 = getColumnOrder(key1);
    string intermediate = extractTextFromGrid(grid1, order1, numRows1);

    // Second columnar transposition
    int numCols2 = key2.size();
    int numRows2 = (intermediate.size() + numCols2 - 1) / numCols2;
    vector<string> grid2(numRows2, string(numCols2, ' '));

    fillGrid(intermediate, grid2, numRows2, numCols2);

    vector<int> order2 = getColumnOrder(key2);
    string ciphertext = extractTextFromGrid(grid2, order2, numRows2);

    return ciphertext;
}

// Decryption function for Double Columnar Transposition Cipher
string decrypt(const string& ciphertext, const string& key1, const string& key2) {
    // First columnar transposition decryption
    int numCols2 = key2.size();
    int numRows2 = (ciphertext.size() + numCols2 - 1) / numCols2;
    int numCols1 = key1.size();

    vector<string> grid2(numRows2, string(numCols2, ' '));

    vector<int> order2 = getColumnOrder(key2);
    string intermediate(numRows2 * numCols2, ' ');

    // Fill grid2 with ciphertext
    int index = 0;
    for (int c : order2) {
        for (int r = 0; r < numRows2; ++r) {
            if (index < ciphertext.size()) {
                grid2[r][c] = ciphertext[index++];
            }
        }
    }

    // Extract intermediate text
    intermediate = extractTextFromGrid(grid2, order2, numRows2);

    // Second columnar transposition decryption
    vector<string> grid1(numRows2, string(numCols1, ' '));

    vector<int> order1 = getColumnOrder(key1);
    string plaintext(numRows2 * numCols1, ' ');

    // Fill grid1 with intermediate text
    index = 0;
    for (int c : order1) {
        for (int r = 0; r < numRows2; ++r) {
            if (index < intermediate.size()) {
                grid1[r][c] = intermediate[index++];
            }
        }
    }

    // Extract plaintext
    plaintext = extractTextFromGrid(grid1, order1, numRows2);

    // Remove trailing spaces if any
    plaintext.erase(find_if(plaintext.rbegin(), plaintext.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), plaintext.end());

    return plaintext;
}

int main() {
    string plaintext = "Thisisasecretmessage";
    string key1 = "KEYONE";
    string key2 = "KEYTWO";

    string encrypted = encrypt(plaintext, key1, key2);
    string decrypted = decrypt(encrypted, key1, key2);
    decrypted=decrypt(decrypted,key1,key2);
    cout << "Plaintext: " << plaintext << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
