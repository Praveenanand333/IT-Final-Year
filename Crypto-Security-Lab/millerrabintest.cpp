#include <iostream>
#include <random>

using namespace std;



long long powerMod(long long base, long long exp, long long mod) {
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



bool millerRabinTest(long long d, long long n) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(2, n - 2);
    long long a = dis(gen);

    
    long long x = powerMod(a, d, n);

    if (x == 1 || x == n - 1) {
        return true;
    }

    
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}



bool isPrime(long long n, int k) {
    
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    
    for (int i = 0; i < k; i++) {
        if (!millerRabinTest(d, n)) {
            return false;
        }
    }

    return true;
}

int main() {
    long long n;
    int k = 5;  

    cout << "Enter number to check: ";
    cin >> n;

    if (isPrime(n, k)) {
        cout << n << " is probably prime." << endl;
    } else {
        cout << n << " is composite." << endl;
    }

    return 0;
}
