#include <iostream>
#include <algorithm>
#include <chrono>

class FiboNvar {
private:
    unsigned long sum;

    long double binomialCoeff(int n, int r, int t) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;

        r = std::min(r, t);

        long double res = 1.0;
        for (int i = 0; i < r; ++i) {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    }

public:
    FiboNvar(int N) : sum(1) {
        if (N == 1) {
            sum = 0;
        } else if (N == 2 || N == 3) {
            sum = 1;
        } else {
            int s = N / 2;
            int K = 2;
            for (int i = 1; i < s; i++) {
                int n = N - K - 1;
                int r = K - 1;
                int t = N - 2 * K;
                long double coif = binomialCoeff(n, r, t);
                sum += static_cast<unsigned long>(coif);
                K++;
            }
        }
    }

    unsigned long getSum() const {
        return sum;
    }
};

int main() {
    int N;
    std::cout << "Enter n: ";
    std::cin >> N;

    auto start = std::chrono::high_resolution_clock::now();


    FiboNvar fiboObj(N);

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Result: " << fiboObj.getSum() << std::endl;

    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}
