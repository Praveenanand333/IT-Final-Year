#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int modularExponentiation(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}

int fermatInverse(int a, int p) {
    return modularExponentiation(a, p - 2, p);
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

vector<int> primeFactors(int n) {
    vector<int> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2)
        factors.push_back(n);
    return factors;
}

int eulerTotientOptimized(int n) {
    if (isPrime(n)) {
        return n - 1;
    }

    vector<int> factors = primeFactors(n);
    if (factors.size() == 2 && factors[0] != factors[1]) {
        return (factors[0] - 1) * (factors[1] - 1);
    }

    int result = n;
    vector<int> uniqueFactors;
    
    for (int i = 0; i < factors.size(); i++) {
        if (i == 0 || factors[i] != factors[i - 1])
            uniqueFactors.push_back(factors[i]);
    }

    for (int p : uniqueFactors) {
        result *= (p - 1);
        result /= p;
    }

    return result;
}

int eulerTheorem(int a, int n) {
    if (gcd(a, n) != 1) {
        cout << "a and n are not coprime. No solution exists." << endl;
        return -1;
    }
    int phi_n = eulerTotientOptimized(n);
    return modularExponentiation(a, phi_n - 1, n);
}

int main() {
    int a = 3;
    int p = 7;
    int inverseFermat = fermatInverse(a, p);
    cout << "Using Fermat's Little Theorem, the modular inverse of " << a << " modulo " << p << " is: " << inverseFermat << endl;

    int n = 10;
    a = 3;
    int inverseEuler = eulerTheorem(a, n);
    if (inverseEuler != -1)
        cout << "Using Euler's Theorem, the modular inverse of " << a << " modulo " << n << " is: " << inverseEuler << endl;

    return 0;
}
