#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){
string plain;
cin>>plain;
int key;
cin>>key;
string cipher;
for (int i = 0; i < plain.length(); i++) {
        if (isupper(plain[i]))
            cipher += char(int(plain[i] + key - 65) % 26 + 65);
        else
            cipher += char(int(plain[i] + key - 97) % 26 + 97);
    }


cout<<"The encrypted text is:"<<cipher<<endl;


}
