#include <iostream>
#include <iomanip>

int main(){
    int quantity = 3;
    double price = 199.99;
    bool isPaid = true;
    char grade = 'A';

    std::cout << "sizeof(int) = " << sizeof(int) << " bytes" << std::endl;
    std::cout << "sizeof(double) = " << sizeof(double) << " bytes" << std::endl;
    std::cout << "sizeof(bool) = " << sizeof(bool) << " bytes" << std::endl;
    std::cout << "sizeof(char) = " << sizeof(char) << " bytes" << std::endl;

    auto total = quantity * price;
    auto count = 5;
    auto ratio = 7 / 2;
    auto exact = 7 / 2.0;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total: $" << total << std::endl;
    std::cout << "Exact: $" << exact << std::endl;
    std::cout << "Ratio: " << ratio << std::endl;

    double a = 0.1 + 0.2;
    std::cout << std::fixed << std::setprecision(20);
    std::cout << "0.1 + 0.2 = " << a << std::endl;

    std::cout << "isPaid: " << std::boolalpha << isPaid << std::endl;
    char nextGrade = grade + 1;
    std::cout << "Next grade: " << nextGrade << std::endl;
    std::cout << "Grade: " << nextGrade << "Code:" << static_cast<int>(nextGrade) << std::endl;

    int junk;
    int safe{};
    return 0;
}