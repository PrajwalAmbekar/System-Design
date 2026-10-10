#include <iostream>

int square(int n){
    return n * n;
};

bool isEligibleForDiscount(int age){
    if(age < 12 || age > 72){
        return true;
    }
    return false;
};

long long ticketPricePaise( int age){
    if(age < 0){
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


void printMoney(int age){
    long long price = ticketPricePaise(age);
    if(age < 0){
        std::cout << "Age " << age << " Invalid" << std::endl;
    }

    std::cout << "Age " << age << " Valid and Price is : " << price <<std::endl;
}


int tryToChange(int n){
    return n = 9999;
}

int main(){
    int x = 4;
    std::cout << "The square of number  " << x << " : " << square(x) << std::endl;

    int adult = 24;
    int elderAge = 74;
    int childrenAge = 10;

    printMoney(adult);
    printMoney(elderAge);
    printMoney(childrenAge);

    std::cout << "Before Changing my value : " << x <<std::endl;

    tryToChange(x);

    std::cout << "The Value after caling tryToChange() function call " << x <<std::endl;
    return 0;
};


//To compile this run below cmd:
//      g++ -std=c++20 -Wall -Wextra -g code1_function_basics.cpp -o funtions
//      ./functions