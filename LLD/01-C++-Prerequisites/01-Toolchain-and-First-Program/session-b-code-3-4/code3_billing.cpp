#include <iostream>
#include <iomanip>


long long lineTotal(long long unitPaisa, int qty){
    return unitPaisa * qty; // qty is in int, but unitPaisa is in long long, so the result will be in long long if We reverse the order of multiplication, it will be in int and may cause overflow if qty is large. So, we should keep unitPaisa first. so the multiplication is left associative and will be evaluated from left to right. The result will be in long long.
}

long long applyDiscount(long long paisa, int discountPercent){
    return paisa * (100 - discountPercent) / 100; // paisa is in long long, but discountPercent is in int, so the result will be in long long if We reverse the order of multiplication, it will be in int and may cause overflow if paisa is large. So, we should keep paisa first. so the multiplication is left associative and will be evaluated from left to right. The result will be in long long.
}

void printBill(const char* label , long long paisa){
    std::cout << label << " Rs." << paisa / 100 << "." << std::setw(2) << std::setfill('0') << paisa % 100 << std::endl;// paisa is in long long, but we are dividing it by 100 and taking the remainder, so the result will be in long long. We are using std::setw(2) and std::setfill('0') to print the paisa part with 2 digits and leading zeros if necessary.
}

int main(){
    const int discountPercent = 10;
    const int TAX_PERCENT = 18;


    long long subtotal = 0;
    subtotal += lineTotal(1000, 2); // 2 keyboard of Rs.10.00 each
    subtotal += lineTotal(2500, 1); // 1 monitor of Rs.25.00 each
    subtotal += lineTotal(500, 5); // 5 mouse of Rs.5.00 each

    long long finalDiscountedAmount = applyDiscount(subtotal, discountPercent);
    long long taxAmount = finalDiscountedAmount * TAX_PERCENT / 100;
    long long totalAmount = finalDiscountedAmount + taxAmount;

    printBill("Subtotal", subtotal);
    printBill("DiscountedAmount", subtotal - finalDiscountedAmount);
    printBill("TaxAmount", taxAmount);
    printBill("Total", totalAmount);
}



//To compile and run the code, you can use the following commands in your terminal:
            // g++ -std=c++23 code3_billing.cpp -o billing
            // ./billing

 