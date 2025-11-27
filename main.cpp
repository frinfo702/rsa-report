#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include <numeric>

using namespace std;

struct publicKey {
    long long n;
    long long e = 977; // p*qと互いに素になるようにある程度大きい素数
};

struct secretKey {
    long long p;
    long long q;
    long long d = 0;
};

long long modPow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

bool is_prime_number(long long number) {
    long long divider = 3;

    if (number % 2 == 0) {
        return false;
    }

    while (divider <= sqrt(number)) {
        if (number % divider == 0) {
            return false;
        }
        divider += 2;
    }

    return true;
}

long long find_next_prime(long long number) {
    long long initialNum = number;
    while (!is_prime_number(number) || initialNum == number) {
        number += 1;
    }
    long long next_prime_number = number;
    return next_prime_number;
}

secretKey generate_secret_key(long long seed) {
    long long num1 = seed + 20;
    long long num2 = seed + 30;
    long long nextPrimeNumber1 = find_next_prime(num1);
    long long nextPrimeNumber2 = find_next_prime(num2);
    secretKey secretKey = {nextPrimeNumber1, nextPrimeNumber2};
    return secretKey;
}

publicKey generate_public_key(secretKey secretKey) {
    long long n = secretKey.p * secretKey.q;
    return {n};
}

long long find_d(secretKey secretKey , publicKey publicKey) {
    long long d = secretKey.d;
    long long lambda = lcm(secretKey.p - 1, secretKey.q - 1);

    while ((publicKey.e * d) % lambda != 1) {
        d += 1;
    }

    return d;
}

long long encrypt(long long plainNum, publicKey publicKey) {
    long long encrypted = (long long)(modPow(plainNum, publicKey.e, publicKey.n)) % publicKey.n;

    return encrypted;
}

long long decrypt(long long encrypted, publicKey publicKey, secretKey secretKey) {
    return (long long)(modPow(encrypted, secretKey.d, publicKey.n)) % publicKey.n;
}


int main(int argc, char **argv) {
    if (argc < 2) return 1;

    long long plainNum =  stoll(argv[1]);
    secretKey secretKey = generate_secret_key(1);
    publicKey publicKey = generate_public_key(secretKey);
    secretKey.d = find_d(secretKey,  publicKey);

    long long encrypted = encrypt(plainNum, publicKey);
    long long decrypted = decrypt(encrypted, publicKey, secretKey);
    cout << decrypted << endl;

    return 0;
}
