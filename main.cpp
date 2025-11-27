#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include <numeric>

using namespace std;

struct publicKey {
    int n;
    int e;
};

struct secretKey {
    int p;
    int q;
    int d = 0;
};


bool is_prime_number(int number) {
    int divider = 3;

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

int find_next_prime(int number) {
    int initialNum = number;
    while (!is_prime_number(number) || initialNum == number) {
        number += 1;
    }
    int next_prime_number = number;
    return next_prime_number;
}

secretKey generate_secret_key(string studentId) {
    int mln = atoi(&studentId.at(studentId.size() - 1));
    int num1 = mln + 20;
    int num2 = mln + 30;
    int nextPrimeNumber1 = find_next_prime(num1);
    int nextPrimeNumber2 = find_next_prime(num2);
    secretKey secretKey = {nextPrimeNumber1, nextPrimeNumber2};
    return secretKey;
}

publicKey generate_public_key(secretKey secretKey) {
    int n = secretKey.p * secretKey.q;
    int e = 5;
    return {n, e};
}

int find_d(secretKey secretKey , publicKey publicKey) {
    int d = secretKey.d;
    int lambda = lcm(secretKey.p - 1, secretKey.q - 1);

    while ((publicKey.e * d) % lambda != 1) {
        d += 1;
    }

    return d;
}

int encrypt(int plainNum, publicKey publicKey) {
    int encrypted = (int)(pow(plainNum, publicKey.e)) % publicKey.n;

    return encrypted;
}

int decrypt(int encrypted, publicKey publicKey, secretKey secretKey) {
    return (int)(pow(encrypted, secretKey.d)) % publicKey.n;
}


int main(int argc, char **argv) {
    if (argc < 2) return 1;

    int plainNum =  atoi(argv[1]);
    secretKey secretKey = {11, 13};
    publicKey publicKey = generate_public_key(secretKey);
    secretKey.d = find_d(secretKey,  publicKey);

    int encrypted = encrypt(plainNum, publicKey);
    int decrypted = decrypt(encrypted, publicKey, secretKey);
    cout << decrypted << endl;

    return 0;
}
