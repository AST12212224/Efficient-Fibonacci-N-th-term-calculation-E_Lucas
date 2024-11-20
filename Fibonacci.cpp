#include <iostream>
#include <algorithm> 
class FiboNvar {
private:
    int sum; 
    double binomialCoeff(int n, int r, int t) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;
        r = std::min(r, t);
        double res = 1.0;
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
                double coif = binomialCoeff(n, r, t); 
                sum += static_cast<int>(coif);      
                K++;
            }
        }
    }
    int getSum() const {
        return sum;
    }
};

int main() {
    int N;
    std::cout << "Enter n: ";
    std::cin >> N;
    FiboNvar fiboObj(N);
    std::cout << "Result: " << fiboObj.getSum() << std::endl;

    return 0;
}
