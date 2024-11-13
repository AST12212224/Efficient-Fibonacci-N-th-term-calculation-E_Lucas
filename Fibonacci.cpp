#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate factorial
long long factorial(int num) {
    long long result = 1;
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    return result;
}

// Function to calculate F_n
long long F(int n) {
    if (n == 1) {
        return 0;
    }

    int s = (n % 2 == 0) ? n / 2 : (n - 1) / 2;  // Calculate s based on n being odd or even
    long long sum = 0;

    for (int k = 1; k <= s; k++) {
        sum += (factorial(n - k - 1) / (factorial(k - 1) * factorial(n - 2 * k)));
    }

    return sum;
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    cout << "F_" << n << " = " << F(n) << endl;
    return 0;
}