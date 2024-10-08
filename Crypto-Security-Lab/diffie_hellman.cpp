#include <iostream>
#include <cmath>

using namespace std;

// Function to compute (base^exp) % mod efficiently
long long modExpo(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }

    return result;
}

int main() {
    // Step 1: Both parties agree on a large prime number p and base g (public parameters)
    long long p = 23;  // Prime number
    long long g = 5;   // Primitive root modulo p

    cout << "Publicly Shared Prime (p): " << p << endl;
    cout << "Publicly Shared Base (g): " << g << endl;

    // Step 2: Alice and Bob select their private keys
    long long alicePrivateKey = 6;  // Alice's private key (secret)
    long long bobPrivateKey = 15;   // Bob's private key (secret)

    cout << "\nAlice's Private Key: " << alicePrivateKey << endl;
    cout << "Bob's Private Key: " << bobPrivateKey << endl;

    // Step 3: Alice and Bob compute their public keys
    long long alicePublicKey = modExpo(g, alicePrivateKey, p);
    long long bobPublicKey = modExpo(g, bobPrivateKey, p);

    cout << "\nAlice's Public Key: " << alicePublicKey << endl;
    cout << "Bob's Public Key: " << bobPublicKey << endl;

    // Step 4: Alice and Bob exchange their public keys (this is done over an insecure channel)

    // Step 5: Alice computes the shared secret using Bob's public key
    long long aliceSharedSecret = modExpo(bobPublicKey, alicePrivateKey, p);

    // Step 6: Bob computes the shared secret using Alice's public key
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
