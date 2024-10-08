#include <iostream>
#include <random>

using namespace std;

// Function to perform modular exponentiation
// It returns (base^exp) % mod
long long powerMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd, multiply base with result
            result = (result * base) % mod;
        }
        exp = exp >> 1;     // Divide exp by 2
        base = (base * base) % mod;  // Square base
    }
    return result;
}

// Function to perform the Miller-Rabin test
// It returns false if n is composite, true if n is probably prime
bool millerRabinTest(long long d, long long n) {
    // Generate a random number a in [2, n-2]
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(2, n - 2);
    long long a = dis(gen);

    // Compute a^d % n
    long long x = powerMod(a, d, n);

    if (x == 1 || x == n - 1) {
        return true;
    }

    // Keep squaring x while d != n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}

// Function to check if n is prime
// It returns false if n is composite, true if n is probably prime
bool isPrime(long long n, int k) {
    // Handle base cases
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Find d such that n-1 = d * 2^r for some r >= 1
    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    // Perform k iterations of Miller-Rabin test
    for (int i = 0; i < k; i++) {
        if (!millerRabinTest(d, n)) {
            return false;
        }
    }

    return true;
}

int main() {
    long long n;
    int k = 5;  // Number of iterations (higher value of k increases accuracy)

    cout << "Enter number to check: ";
    cin >> n;

    if (isPrime(n, k)) {
        cout << n << " is probably prime." << endl;
    } else {
        cout << n << " is composite." << endl;
    }

    return 0;
}
