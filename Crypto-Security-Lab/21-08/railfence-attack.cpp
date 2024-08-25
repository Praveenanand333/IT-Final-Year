#include <bits/stdc++.h>
using namespace std;

// Function to decrypt Rail Fence Cipher with a given key
string decryptRailFence(string cipher, int key)
{
    vector<vector<char>> rail(key, vector<char>(cipher.length(), '\n'));
    bool dir_down;
    int row = 0, col = 0;

    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        rail[row][col++] = '*';
        dir_down ? row++ : row--;
    }

    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*' && index < cipher.length())
                rail[i][j] = cipher[index++];

    string result;
    row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);

        dir_down ? row++ : row--;
    }
    return result;
}

// Function to perform Rail Fence cipher attack
void railFenceAttack(string cipher)
{
    int maxKey = cipher.length() / 2; // Maximum number of rails can be half the length of cipher
    for (int key = 2; key <= maxKey; key++) {
        string decryptedText = decryptRailFence(cipher, key);
        cout << "Key " << key << ": " << decryptedText << endl;
    }
}

int main()
{
    string cipherText = "dnhaaeedteeswlf  tl";
    railFenceAttack(cipherText);

    return 0;
}
