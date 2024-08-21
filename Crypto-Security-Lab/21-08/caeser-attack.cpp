#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    string cipher="OQZUDDM";
    int n=cipher.size();
    for(int i=1;i<=26;i++){
        string temp="";
        for(int j=0;j<n;j++){
            temp+=(((cipher[j]-'A'+26)-i)%26)+'A';
        }
        cout<<temp<<endl;
    }

}