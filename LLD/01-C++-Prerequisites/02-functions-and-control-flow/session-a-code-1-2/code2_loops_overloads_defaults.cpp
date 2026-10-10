#include <iostream>
#include <string>


bool isEligibleForDiscount(int age){
    if(age < 12 || age > 72){
        return true;
    }
    return false;
}

long long ticketPricePaisa(int age){
    if(age < 0 ){
        return 1;        
    }
    else if(age < 5){
        return 0;
    }
    else if(isEligibleForDiscount(age)){
        return 15000;
    }

    return 30000;
};

long long ticketPricePaisa(int age, bool isMember){
    long long base = ticketPricePaisa(age);
    if(base < 0) {
        return -1;
    }

    return isMember ? base * 80 / 100 : base;
};

void printHeader(const std::string& title , char fill = '=', int width = 28){
    std::cout << std::string(width , fill ) << "\n" << title << "\n" << std::string(width ,fill) << "\n";
}


int main(){
    printHeader("Price Table");
    printHeader("Member view",'-');

    int paidCount = 0;
    for( int age = 0 ; age < 70 ; age+=10){
        long long regular =ticketPricePaisa(age);
        long long member = ticketPricePaisa(age,true);
        std::cout << "age " << age << ": " << regular << " / member " << member <<std::endl;

        if(regular == 0){
            continue;
        }
        ++paidCount;
    }

    std::cout<< "The paid categories "<< paidCount << std::endl;
    return 0;
}


//To compile this file:
//     g++ -std=c++20 -Wall -Wextra -g code2_loops_overloads_defaults.cpp -o loopsOverloads
//     ./loopsOverloads