#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    Fraction(int n, int d) : numerator(n), denominator(d) {
        if (d == 0) {
            throw std::runtime_error("Denominator cannot be zero");
        }
    }
};

int main() {
    int n, d;

    try {
        if (!(std::cin >> n >> d)) {
            throw std::runtime_error("Invalid input");
        }

        Fraction f(n, d);
        std::cout << "Fraction created" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Incorrect data" << std::endl;
    }

    return 0;
}