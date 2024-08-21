#include<iostream>
#include<bits/stdc++.h>
using namespace std;
bool custom(const pair<char, int>& a, const pair<char, int>& b) {
    return a.second > b.second;
}

int main() {
    string para = "to do several hands-on exercises to reinforce the students knowledge and understanding of the various security aspects "
                  "to explore the sequence of cryptographic algorithms by implementing using a programming language. "
                  "to understand vulnerabilities and security flaws in the various applications. "
                  "to develop simple and location specific applications in android environment. "
                  "to analyse the performance of mobile networks using network simulator.q";
    
    string cipherpara = "gl wl hvevizo szmwh-lm vcvixrhvh gl ivrmulixv gsv hgfwvmgh pmldovwtv zmw "
                        "fmwvihgzmwrmt lu gsv ezirlfh hvxfirgb zhkvxgh "
                        "gl vckoliv gsv hvjfvmxv lu xibkgltizksrx zotlirgsnh yb rnkovnvmgrmt fhrmt z "
                        "kiltiznnrmt ozmtfztv "
                        "gl fmwvihgzmw efomvizyrorgrvh zmw hvxfirgb uozdh rm gsv ezirlfh zkkorxzgrlmh "
                        "gl wvevolk hrnkov zmw olxzgrlm hkvxrurx zkkorxzgrlmh rm zmwilrw vmerilmnvmg "
                        "gl zmzobhv gsv kviulinzmxv lu nlyrov mvgdliph fhrmt Mvgdlip hrnfozgli j";
    
    unordered_map<char, int> mp;
    for (auto it : cipherpara) {
        if (isalpha(it)) {
            mp[it]++;
        }
    }
    std::vector<pair<char, int>> freqVec(mp.begin(), mp.end());
    sort(freqVec.begin(), freqVec.end(), custom);
    for(auto it:freqVec){
        cout<<it.first<<":"<<it.second<<endl;
    }
    string order1 = "eariotnslcudpmhgbfywkvxzjq";
    string order2 = "enoitasrlcdpugmhfvywkbqxnj";
    string order3 = "etainoshrdlucmfwygpbvkqjxz";
    int ind = 0;
    unordered_map<char, char> kvp;
    for (auto it : freqVec) {
        kvp[it.first] = order2[ind++];
    }
    string decoded = "";
    for (auto it : cipherpara) {
        if (isalpha(it)) {
            decoded += kvp[it];
        } else {
            decoded += it;
        }
    }

    cout << decoded;

    return 0;
}
