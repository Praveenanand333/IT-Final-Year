#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include<bits/stdc++.h>
using namespace std;
string hex2bin(string s) {
    string mp[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                     "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    string bin = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
            bin += mp[s[i] - '0'];
        else
            bin += mp[s[i] - 'A' + 10];
    }
    return bin;
}
int bin2dec(string binary) {
    int decimal = 0, base = 1;
    int len = binary.length();
    for (int i = len - 1; i >= 0; i--) {
        if (binary[i] == '1')
            decimal += base;
        base = base * 2;
    }
    return decimal;
}
string bin2hex(string s) {
    string mp[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    string hex = "";
    for (int i = 0; i < s.size(); i += 4) {
        string ch = s.substr(i, 4);
        int num = stoi(ch, 0, 2);
        hex += mp[num];
    }
    return hex;
}



string dec2bin(int num) {
    string bin = bitset<4>(num).to_string();
    return bin;
}

string permute(string k, vector<int> arr, int n) {
    string per = "";
    for (int i = 0; i < n; i++) {
        per += k[arr[i] - 1];
    }
    return per;
}

string shift_left(string k, int shifts) {
    string s = "";
    for (int i = 0; i < shifts; i++) {
        s = k.substr(1, k.size() - 1) + k[0];
        k = s;
    }
    return k;
}
string xor_(string a, string b) {
    string ans = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }
    return ans;
}

vector<int> initial_perm = {58, 50, 42, 34, 26, 18, 10, 2,
                            60, 52, 44, 36, 28, 20, 12, 4,
                            62, 54, 46, 38, 30, 22, 14, 6,
                            64, 56, 48, 40, 32, 24, 16, 8,
                            57, 49, 41, 33, 25, 17, 9, 1,
                            59, 51, 43, 35, 27, 19, 11, 3,
                            61, 53, 45, 37, 29, 21, 13, 5,
                            63, 55, 47, 39, 31, 23, 15, 7};
vector<int> exp_d = {32, 1, 2, 3, 4, 5, 4, 5,
                     6, 7, 8, 9, 8, 9, 10, 11,
                     12, 13, 12, 13, 14, 15, 16, 17,
                     16, 17, 18, 19, 20, 21, 20, 21,
                     22, 23, 24, 25, 24, 25, 26, 27,
                     28, 29, 28, 29, 30, 31, 32, 1};
vector<int> per = {16, 7, 20, 21,
                   29, 12, 28, 17,
                   1, 15, 23, 26,
                   5, 18, 31, 10,
                   2, 8, 24, 14,
                   32, 27, 3, 9,
                   19, 13, 30, 6,
                   22, 11, 4, 25};
int sbox[8][4][16] = {{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                       {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                       {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                       {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
                      {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                       {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                       {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                       {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
                      {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                       {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                       {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                       {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
                      {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                       {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                       {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                       {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
                      {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                       {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                       {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                       {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
                      {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                       {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                       {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                       {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
                      {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                       {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                       {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                       {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
                      {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                       {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                       {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                       {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
vector<int> final_perm = {40, 8, 48, 16, 56, 24, 64, 32,
                          39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30,
                          37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28,
                          35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26,
                          33, 1, 41, 9, 49, 17, 57, 25};
void generate_keys(string key, vector<string> &rkb, vector<string> &rk) {
    vector<int> keyp = {57, 49, 41, 33, 25, 17, 9,
                        1, 58, 50, 42, 34, 26, 18,
                        10, 2, 59, 51, 43, 35, 27, 19,
                        11, 3, 60, 52, 44, 36, 63, 55,
                        47, 39, 31, 23, 15, 7, 62, 54,
                        46, 38, 30, 22, 14, 6, 61, 53,
                        45, 37, 29, 21, 13, 5, 28, 20,
                        12, 4};
    //discard 8 th bits and permute
    key = permute(key, keyp, 56);
    string left = key.substr(0, 28);
    string right = key.substr(28, 28);
    vector<int> shift_table = {1, 1, 2, 2, 2, 2, 2, 2,
                               1, 2, 2, 2, 2, 2, 2, 1};
    vector<int> key_comp = {14, 17, 11, 24, 1, 5, 3, 28,
                            15, 6, 21, 10, 23, 19, 12, 4,
                            26, 8, 16, 7, 27, 20, 13, 2,
                            41, 52, 31, 37, 47, 55, 30, 40,
                            51, 45, 33, 48, 44, 49, 39, 56,
                            34, 53, 46, 42, 50, 36, 29, 32};
                            //48
                            //discard 9 th bit

    for (int i = 0; i < 16; i++) {
        left = shift_left(left, shift_table[i]);
        right = shift_left(right, shift_table[i]);
        string combined_key = left + right;
        string round_key = permute(combined_key, key_comp, 48);
        rkb.push_back(round_key);
        rk.push_back(bin2hex(round_key));
    }
}
string feistel(string pt, vector<string> rkb) {
    pt = permute(pt, initial_perm, 64); 
    string left = pt.substr(0, 32);
    string right = pt.substr(32, 32);

    for (int i = 0; i < 16; i++) {
        string right_expanded = permute(right, exp_d, 48);  
        string x = xor_(rkb[i], right_expanded);            
        
        string op = "";
        //for 8 s-box
        for (int j = 0; j < 8; j++) {
            int row = bin2dec(x.substr(j * 6, 1) + x.substr(j * 6 + 5, 1));
            int col = bin2dec(x.substr(j * 6 + 1, 4));
            int val = sbox[j][row][col];
            op += dec2bin(val);
        }

        op = permute(op, per, 32);         
        x = xor_(op, left);             
        left = right;         
        right = x;
    }

    string combined = right + left;       
    return permute(combined, final_perm, 64); 
}
string decToHexa(int n)
{
    char hexaDeciNum[100];
    int i = 0;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;

        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        n = n / 16;
    }
 
    string ans = "";
    for (int j = i - 1; j >= 0; j--)
        ans += hexaDeciNum[j];
 
    return ans;
}
string ASCIItoHEX(string ascii)
{
    string hex = "";
    for (int i = 0; i < ascii.length(); i++) {
        char ch = ascii[i];
        int tmp = (int)ch;
        string part = decToHexa(tmp);
        hex += part;
    }

    return hex;
}
string hexToASCII(string hex)
{
    string ascii = "";
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        string part = hex.substr(i, 2);
        char ch = stoul(part, nullptr, 16);
        ascii += ch;
    }
    return ascii;
}
int main() {

    string key = "AABB09182736CCDD";
    key = hex2bin(key);
    //cout<<key.size();
    //string pt=hex2bin("123ABC567DEF8900");
    string pt=hex2bin(ASCIItoHEX("hellowor"));
    //cout<<":"<<pt.size()<<":";
    //cout<<pt<<":"<<key;
    //string temp="1110";
    //cout<<stoi(temp,0,2)<<":"<<bin2dec(temp);
    //cout<<hexToASCII(ASCIItoHEX("hello"));
    vector<string> rkb; 
    vector<string> rk;  
    generate_keys(key, rkb, rk);
    cout << "Encryption:\n";
    string cipher_text = feistel(pt, rkb);
    cout << "Cipher Text: " << hexToASCII(bin2hex(cipher_text)) << endl;

    reverse(rkb.begin(), rkb.end());
    cout << "Decryption:\n";
    string decrypted_text = feistel(cipher_text, rkb); 
    cout << "Decrypted Text: " << hexToASCII(bin2hex(decrypted_text)) << endl;


    return 0;
}
