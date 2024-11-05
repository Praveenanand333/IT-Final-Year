#include <iostream>
#include <vector>

using namespace std;


int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


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


int chineseRemainder(const vector<int>& num, const vector<int>& rem, int n) {
    int product = 1;  
    for (int i = 0; i < n; i++)
        product *= num[i];
    
    int result = 0;
    
    
    for (int i = 0; i < n; i++) {
        int partialProduct = product / num[i];
        int inverse = modInverse(partialProduct, num[i]);
        result += rem[i] * inverse * partialProduct;
    }
    
    return result % product;
}

int main() {
    vector<int> num = {3, 5, 7};  
    vector<int> rem = {2, 3, 2};  
    
    int n = num.size();
    int x = chineseRemainder(num, rem, n);
    
    cout << "The solution is x = " << x << endl;
    
    return 0;
}
