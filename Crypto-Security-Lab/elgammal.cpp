#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to compute (base^exponent) mod modulus
long long modularExponentiation(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) { // If exponent is odd
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1; // Divide exponent by 2
        base = (base * base) % modulus; // Square the base
    }
    return result;
}

// Function to find a primitive root modulo p
int findPrimitiveRoot(int p) {
    for (int g = 2; g < p; g++) {
        bool isPrimitive = true;
        for (int k = 1; k < p - 1; k++) {
            if (modularExponentiation(g, k, p) == 1) {
                isPrimitive = false;
                break;
            }
        }
        if (isPrimitive) {
            return g;
        }
    }
    return -1; // Not found
}

int main() {
    srand(time(0)); // Seed for randomness

    // Step 1: Choose a large prime p and a primitive root g
    int p = 23; // A small prime for demonstration; in practice, use a larger prime
    int g = findPrimitiveRoot(p);
    cout << "Prime (p): " << p << endl;
    cout << "Primitive Root (g): " << g << endl;

    // Step 2: Alice chooses a private key (a) and computes A
    int a = rand() % (p - 2) + 1; // Alice's private key
    long long A = modularExponentiation(g, a, p);
    cout << "Alice's Private Key (a): " << a << endl;
    cout << "Alice's Public Key (A): " << A << endl;

    // Step 3: Bob chooses a private key (b) and computes B
    int b = rand() % (p - 2) + 1; // Bob's private key
    long long B = modularExponentiation(g, b, p);
    cout << "Bob's Private Key (b): " << b << endl;
    cout << "Bob's Public Key (B): " << B << endl;

    // Step 4: Alice computes the shared secret
    long long sharedSecretAlice = modularExponentiation(B, a, p);
    cout << "Alice's Shared Secret: " << sharedSecretAlice << endl;

    // Step 5: Bob computes the shared secret
    long long sharedSecretBob = modularExponentiation(A, b, p);
    cout << "Bob's Shared Secret: " << sharedSecretBob << endl;

    // Check if both secrets match
    if (sharedSecretAlice == sharedSecretBob) {
        cout << "Shared secret match!" << endl;
    } else {
        cout << "Shared secret mismatch!" << endl;
    }

    return 0;
}
