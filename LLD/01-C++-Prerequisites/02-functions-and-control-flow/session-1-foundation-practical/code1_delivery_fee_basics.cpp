#include <iostream>



long long deliveryFee(int distanceKm){
    if(distanceKm < 0){
        return -1;
    }
    else if(distanceKm <= 3){
        return 2000;
    }
    else if(distanceKm <= 10){
        return 2000 + (distanceKm - 3) * 500;
    }
    else{
        return 2000 + 7 * 500 + (distanceKm - 10) * 800;
    }
}

bool qualifiesForFreeDelivery(long long orderPaisa){
    return orderPaisa >= 99900;
}

void printFee(int distanceKm){
    long long fee = deliveryFee(distanceKm);
    if(fee < 0){
        std::cout << distanceKm << " km: invalid" << std::endl;
        return;
    }
    std::cout << distanceKm << " Km: " << fee << std::endl;
}
void tryToRaiseFee(long long fee){
    fee++;
}


int main(){
    for(int km = 0; km <= 15; km+=5){
        printFee(km);
    }
    printFee(-2);

    int km = 0;
    while (deliveryFee(km + 1) <= 6000){
        km++;
    }

    std::cout << "The farthest distance within 6000 paise: "<< km <<" km\n";
    long long fee = 3000;
    tryToRaiseFee(fee);
    std::cout << "fee after tryToRaiseFee " << fee << "\n";
    std::cout << std::boolalpha << "free delivery for 1200 rupees? "<< qualifiesForFreeDelivery(120000) << "\n";

    return 0;
}


//To compile this file:
// g++ -std=c++20 -Wall -Wextra -g code1_delivery_fee_basics.cpp -o deliveryFees
//./deliveryFees