#include <iostream>
#include <vector>

using namespace std;    

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    
    if (m == 1)
        return 0;
    
    
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    
    if (x1 < 0)
        x1 += m0;
    
    return x1;
}


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

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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
