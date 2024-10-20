#include <iostream>
#include <cmath>

using namespace std;


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


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
    
    int p = 61; 
    int q = 53; 

    
    int n = p * q;

    
    int phi = (p - 1) * (q - 1);

    
    int e = 17; 
    if (gcd(e, phi) != 1) {
        cout << "e and phi are not coprime. Choose a different value for e." << endl;
        return -1;
    }

    
    int d = modInverse(e, phi);

    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    
    int message;
    cout << "Enter the message to encrypt (as a number): ";
    cin >> message;

    
    long long encryptedMessage = modExpo(message, e, n);
    cout << "Encrypted Message: " << encryptedMessage << endl;

    
    long long decryptedMessage = modExpo(encryptedMessage, d, n);
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}
