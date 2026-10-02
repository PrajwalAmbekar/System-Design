#include <iostream>

int applyDiscount(int paise, int percent) {
    return paise * (100 - percent) / 100; 
}

int main(){
    int total;
    total += 1000 * 2;
    total += 2500 * 1;

    int bulkOrder = 2000000 * 1500;

    double average = total / 3;

    std::cout<< "Discounted Amount: " << applyDiscount(total, 10) << std::endl;

    std::cout<<"Bulk Order Amount: " << bulkOrder << std::endl;

    std::cout<<"Average Amount: " << average << std::endl;

    return 0;
}