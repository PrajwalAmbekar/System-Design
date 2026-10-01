#include <iostream>

int applyDiscount(int paise, int percent) {
    return paise * (100 - percent) / 100; 
}

int main(){
    int total;
    total += 1000 * 2; // 2 keyboard of Rs.10.00 each
    total += 2500 * 1; // 1 monitor of Rs.25.00 each

    int bulkOrder = 2000000 * 1500; //2M units of Rs.15.00 each, this will cause overflow as the result will be 3B which is greater than the maximum value of int which is 2,147,483,647. So, we should use long long instead of int to store the total amount.

    double average = total / 3; // average is in double, but total is in int, so the result will be in int if we reverse the order of division, it will be in double and may cause loss of precision if total is large. So, we should keep total first. so the division is left associative and will be evaluated from left to right. The result will be in double.

    std::cout<< "Discounted Amount: " << applyDiscount(total, 10) << std::endl; // total is in int, but we are passing it to applyDiscount which takes int as parameter, so the result will be in int. We are using 10 as discount percent, so the result will be in int. We are using std::cout to print the discounted amount.

    std::cout<<"Bulk Order Amount: " << bulkOrder << std::endl; // bulkOrder is in int, but we are printing it using std::cout which takes int as parameter, so the result will be in int. We are using std::cout to print the bulk order amount.

    std::cout<<"Average Amount: " << average << std::endl; // average is in double, but we are printing it using std::cout which takes double as parameter, so the result will be in double. We are using std::cout to print the average amount.

    return 0;
}


//To compile with -Wall -Wextra -g to enable all warnings and debugging information, you can use the following command in your terminal:
            // g++ -std=c++23 -Wall -Wextra -g code3_billing_buggy.cpp -o billing_buggy
            // ./billing_buggy


// Learning from this Code:
// 1. Use long long instead of int to store large values(money/counts) to avoid overflow.
// 2. Use double instead of int to store average values to avoid loss of precision.
// 3.  Multiplication and division are left associative and will be evaluated from left to right, so we should keep the larger value first to avoid overflow or loss of precision. SO first multiply and then divide.