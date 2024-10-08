#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate (base^exp) % mod efficiently
long long modExpo(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to calculate the modular inverse using the extended Euclidean algorithm
int modInverse(int e, int phi) {
    int t1 = 0, t2 = 1, r1 = phi, r2 = e;
    while (r2 != 0) {
        int quotient = r1 / r2;
        int temp = t1;
        t1 = t2;
        t2 = temp - quotient * t2;

        temp = r1;
        r1 = r2;
        r2 = temp - quotient * r2;
    }

    if (t1 < 0) {
        t1 += phi;
    }
    return t1;
}

int main() {
    // Step 1: Choose two prime numbers p and q
    int p = 61; // First prime number
    int q = 53; // Second prime number

    // Step 2: Calculate n = p * q
    int n = p * q;

    // Step 3: Calculate phi(n) = (p - 1) * (q - 1)
    int phi = (p - 1) * (q - 1);

    // Step 4: Choose public key e such that 1 < e < phi and gcd(e, phi) = 1
    int e = 17; // Public exponent
    if (gcd(e, phi) != 1) {
        cout << "e and phi are not coprime. Choose a different value for e." << endl;
        return -1;
    }

    // Step 5: Calculate private key d such that d * e ≡ 1 (mod phi)
    int d = modInverse(e, phi);

    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    // Step 6: Input message to encrypt
    int message;
    cout << "Enter the message to encrypt (as a number): ";
    cin >> message;

    // Step 7: Encrypt the message using the public key: c = (message^e) % n
    long long encryptedMessage = modExpo(message, e, n);
    cout << "Encrypted Message: " << encryptedMessage << endl;

    // Step 8: Decrypt the message using the private key: m = (c^d) % n
    long long decryptedMessage = modExpo(encryptedMessage, d, n);
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}
