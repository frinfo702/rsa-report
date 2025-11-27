#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

const int PUBLIC_E = 5;

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

vector<int> generate_secret_key(string studentId) {
    int mln = atoi(&studentId.at(studentId.size() - 1));
    int num1 = mln + 20;
    int num2 = mln + 30;
    int nextPrimeNumber1 = find_next_prime(num1);
    int nextPrimeNumber2 = find_next_prime(num2);
    vector<int> primePair = {nextPrimeNumber1, nextPrimeNumber2};
    return primePair;
}

int encrypt(vector<int> secretKey, int plainNum) {
    int publicN = accumulate(secretKey.begin(), secretKey.end(), 1.0, std::multiplies<int>());
    int secretP = secretKey.at(0);
    int secretQ = secretKey.at(1);
    int lambda = lcm(secretP - 1, secretQ - 1);

    int d = 1;
    while (gcd(PUBLIC_E,  d) % lambda != 1) {
        d += 1;
    }

    int encrypted = int(pow(plainNum, PUBLIC_E)) % publicN;
    return encrypted;
}

int main(int argc, char **argv) {
    // string studentId = argv[1];

    int plainNum = 11;

    // vector<int> secretKey = generate_secret_key(studentId);
    vector<int> secretKey = {5, 7};
    int encrypted = encrypt(secretKey, plainNum);
    cout << encrypted << endl;
    cout << plainNum << endl;
    return 0;
}
