#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

long long modularExponentiation(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1; 
        base = (base * base) % modulus; 
    }
    return result;
}

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
    return -1; 
}

int main() {
    srand(time(0)); 
    int p = 23;
    int g = findPrimitiveRoot(p);
    cout << "Prime (p): " << p << endl;
    cout << "Primitive Root (g): " << g << endl;
    
    int a = rand() % (p - 2) + 1;
    long long A = modularExponentiation(g, a, p);
    cout << "Alice's Private Key (a): " << a << endl;
    cout << "Alice's Public Key (A): " << A << endl;

    int b = rand() % (p - 2) + 1;
    long long B = modularExponentiation(g, b, p);
    cout << "Bob's Private Key (b): " << b << endl;
    cout << "Bob's Public Key (B): " << B << endl;

    long long sharedSecretAlice = modularExponentiation(B, a, p);
    cout << "Alice's Shared Secret: " << sharedSecretAlice << endl;

    long long sharedSecretBob = modularExponentiation(A, b, p);
    cout << "Bob's Shared Secret: " << sharedSecretBob << endl;

    if (sharedSecretAlice == sharedSecretBob) {
        cout << "Shared secret match!" << endl;
    } else {
        cout << "Shared secret mismatch!" << endl;
    }

    return 0;
}
