#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long returnE(long long phi) {
    for (long long e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            return e;
    }
    return -1; 
}

long long returnD(long long e, long long phi) {
    long long i = 1;
    while ((i * e) % phi != 1) {
        i++;
    } 
    return i;
}

void convertToAscii(vector<long long>& ascii, string s) {
    for(char curr : s) {
        ascii.push_back(int(curr));
    }
}

void convertBackToStringFromAscii(vector<long long>& ascii, string& s) {
    for(long long curr : ascii) {
        s += char(curr);
    }
}

long long modexp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

void encrypt(vector<long long>& ascii, vector<long long>& result, long long n, long long E) {
    for (long long i : ascii) {
        long long curr = modexp(i, E, n);
        result.push_back(curr);
    }
}

void decrypt(vector<long long>& result, long long d, long long n, vector<long long>& decryptedResult) {
    for(long long i: result) {
        long long curr = modexp(i, d, n);
        decryptedResult.push_back(curr);
    }
}

void RSA() {
    string message = "Hello there i am high like very very";
    long long p = 7919;
    long long q = 3253;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = returnE(phi);
    long long d = returnD(e, phi);

    cout << "Before encryption: " << message << endl;

    cout << "Public key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private key (d, n): (" << d << ", " << n << ")\n";

    vector<long long> ascii;
    convertToAscii(ascii, message);

    cout << "ASCII: ";
    for (long long r : ascii) {
        cout << r << " ";
    }
    cout << endl;

    vector<long long> result;
    encrypt(ascii, result, n, e);

    cout << "Encrypted message: ";
    for (long long r : result) {
        cout << r << " ";
    }
    cout << endl;

    vector<long long> decryptedResult;
    decrypt(result, d, n, decryptedResult);

    cout << "Decrypted message: ";
    for (long long r : decryptedResult) {
        cout << r << " ";
    }
    cout << endl;

    string dR;
    convertBackToStringFromAscii(decryptedResult, dR);

    cout << "After decryption: " << dR << endl;
}

int main() {
    RSA();
    return 0;
}