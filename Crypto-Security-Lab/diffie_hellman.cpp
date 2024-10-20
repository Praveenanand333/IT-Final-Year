#include <iostream>
#include <cmath>

using namespace std;
<<<<<<< HEAD

=======
>>>>>>> b6be3848ade85ef2470c301cf67d821e464e1ef3
long long modExpo(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1; 
        base = (base * base) % mod;
    }

    return result;
}

int main() {
<<<<<<< HEAD
    
    long long p = 23;  
    long long g = 5;   
=======
    long long p = 23; 
    long long g = 5;  
>>>>>>> b6be3848ade85ef2470c301cf67d821e464e1ef3

    cout << "Publicly Shared Prime (p): " << p << endl;
    cout << "Publicly Shared Base (g): " << g << endl;

<<<<<<< HEAD
    
    long long alicePrivateKey = 6;  
    long long bobPrivateKey = 15;   
=======
    long long alicePrivateKey = 6; 
    long long bobPrivateKey = 15;  
>>>>>>> b6be3848ade85ef2470c301cf67d821e464e1ef3

    cout << "\nAlice's Private Key: " << alicePrivateKey << endl;
    cout << "Bob's Private Key: " << bobPrivateKey << endl;

<<<<<<< HEAD
    
=======
>>>>>>> b6be3848ade85ef2470c301cf67d821e464e1ef3
    long long alicePublicKey = modExpo(g, alicePrivateKey, p);
    long long bobPublicKey = modExpo(g, bobPrivateKey, p);

    cout << "\nAlice's Public Key: " << alicePublicKey << endl;
    cout << "Bob's Public Key: " << bobPublicKey << endl;

<<<<<<< HEAD
    

    
    long long aliceSharedSecret = modExpo(bobPublicKey, alicePrivateKey, p);

    
=======
    long long aliceSharedSecret = modExpo(bobPublicKey, alicePrivateKey, p);
>>>>>>> b6be3848ade85ef2470c301cf67d821e464e1ef3
    long long bobSharedSecret = modExpo(alicePublicKey, bobPrivateKey, p);

    cout << "\nShared Secret Key (computed by Alice): " << aliceSharedSecret << endl;
    cout << "Shared Secret Key (computed by Bob): " << bobSharedSecret << endl;

    if (aliceSharedSecret == bobSharedSecret) {
        cout << "\nKey exchange successful! Both parties have the same shared secret." << endl;
    } else {
        cout << "\nKey exchange failed! The shared secrets do not match." << endl;
    }

    return 0;
}
