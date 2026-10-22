#include <iostream>

class FeeCalculator
{

private:
    long long basePricePaise_;
    int includedKm_;
    long long perKmPaise_;

public:
    FeeCalculator(long long basePricePaise = 2000, int includedKm = 3, long long perKmPaise = 500)
        : basePricePaise_(basePricePaise), includedKm_(includedKm), perKmPaise_(perKmPaise) {};

    long long feeFor(int distanceKm) const
    {
        if (distanceKm < 0)
        {
            return -1;
        }
        if (distanceKm <= includedKm_)
        {
            return basePricePaise_;
        }
        return basePricePaise_ + (distanceKm - includedKm_) * perKmPaise_;
    }

    long long feeFor(int distanceKm, int surgePercent) const
    {
        long long fee = feeFor(distanceKm);
        if (fee < 0 || surgePercent < 100)
            return -1;
        return fee * surgePercent / 100;
    }

    bool tryQuote(int distanceKm, long long &outfee, int surgePercent = 100) const
    {
        long long fee = feeFor(distanceKm, surgePercent);
        if (fee < 0)
            return false;
        outfee = fee;
        return true;
    }
};

int main(){
    FeeCalculator standard;
    FeeCalculator premium(3000,5,400);

    for(int km = 2 ; km <= 20 ; km += 6){
        std::cout << km << " km standard " << standard.feeFor(km) << " premium " << premium.feeFor(km) << "\n";
    };
    std::cout << "Surge 150% at 8 km: " << standard.feeFor(8,150) <<"\n";


    long long fee = 0;
    if(!standard.tryQuote(-5,fee)){
        std::cout << "quote rejected\n";
    }

    long long budget = 20000;
    int orders = 0;
    while(standard.tryQuote(1,fee)  && fee <= budget){
        budget -= fee;
        orders++;
    }

    std::cout << "Orders afforded: " << orders << ", budget left: " << budget << "\n";
    return 0;
}

//To compile this file 
//>> g++ -std=c++20 -Wall -Wextra -g code2_fee_calculator.cpp -o feeCalculator
//./feeCalculator